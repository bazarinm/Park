#include "Animal.h"

#include "Utility.h"
#include "Park.h"
#include <vector>
#include <array>
#include <queue>

Animal::Animal(
	Species _species, 
	Diet _diet,
	unsigned _nutrition,
	std::size_t _FOV, 
	unsigned _move_length,
	const Park& _territory, 
	Coords _position,
	unsigned _nutrients 
):
	Creature(ANIMAL, _species, _nutrition, _territory, _position, _nutrients),

	diet(_diet),
	FOV(_FOV),
	move_length(_move_length)
{
}



void Animal::behave() {
	last_action = IDLE;

	if (nutrients == 0 || isOld())
		death();
	else if (isHungry()) //hungry and found food nearby
		eat();
	else if (isReady()) //ready and found partner nearby
		procreate();
	else
		idle();

	++age;
}

bool Animal::move(Aim aim) {
	bool move = false;

	for (unsigned i = 0; i < move_length; ++i) {
		if (!route.empty()) {
			Coords::Direction step = route.back(); route.pop_back();

			Coords next;
			if (step == Coords::UP)
				next = position.up();
			else if (step == Coords::DOWN)
				next = position.down();
			else if (step == Coords::LEFT)
				next = position.left();
			else if (step == Coords::RIGHT)
				next = position.right();

			if (isVacant(territory[next])) {
				position = next;
				move = true;
			}
			else
				break; //an obstacle is blocking movement or position near partner has been reached
		}
		else
			break; //no route to follow
	}

	if (move) {
		--nutrients;
		last_action = MOVE;
	}
	return move;
}

bool Animal::eat() {
	bool eat = false;

	if (search(FOOD)) {
		if (!inProximity(FOOD))  //have not reached food
			move(FOOD); //go to food
						//else if is not recommended, rabbirs may starve
		if (inProximity(FOOD)) { //if reached food
			position = closest_aim;

			if (diet == HERBIVORE)
				nutrients += territory[position].plant->getNutrition();
			else if (diet == CARNIVORE)
				nutrients += territory[position].animal->getNutrition();

			eat = true;
			last_action = EAT;
		}
	}

	return eat;
}

bool Animal::procreate() {
	offsprings.clear(); // VERY IMPORTANT!!!!
	bool procreate = false;

	if (search(PARTNER)) {
		if (!inProximity(PARTNER))
			move(PARTNER);
		//else is not to be used, since periods would be out of sync otherwise
		if (inProximity(PARTNER)) { //near partner
			Coords spot = findSpot(position); //relative to territory
			if (territory.inBound(spot)) { //!not found
				Animal* child = mate(spot);
				offsprings.push_back(child);
				nutrients -= 2;
				procreate = true;
				last_action = PROCREATE;
			}
		}
	}

	return procreate;
}

bool Animal::idle() {
	--nutrients;
	last_action = IDLE;
	return true;
}



bool Animal::search(Aim aim) {
	route.clear(); //IMPORTANT
	sight = std::vector<std::vector<int>>(2 * FOV + 1, std::vector<int>(2 * FOV + 1, 0));
	//closest_aim = position;
	sight[FOV][FOV] = 1;

	std::queue<Coords> steps;
	steps.push(position);

	bool aim_found = false;
	std::size_t aim_proximity;

	if (isAim(aim, territory[position])) { //checks its position first;
		aim_proximity = 1;
		closest_aim = position;
		aim_found = true;
	}

	while (!aim_found && !steps.empty()) {
		Coords step = steps.front(); steps.pop(); //relative to territory
		Coords relative_step = toRelative(step); //relative to sight

		std::array<Coords, 4> next_steps;
		next_steps[Coords::UP] = step.up();
		next_steps[Coords::DOWN] = step.down();
		next_steps[Coords::LEFT] = step.left();
		next_steps[Coords::RIGHT] = step.right();

		for (Coords next_step : next_steps) { //relative to territory
			Coords relative_next = toRelative(next_step); //relative to sight

			if (!territory.inBound(next_step) 
				|| !inSight(relative_next) 
				|| sight[relative_next.x][relative_next.y] != 0)
				continue;

			if (!aim_found && isAim(aim, territory[next_step])) {
				aim_proximity = sight[relative_step.x][relative_step.y] + 1;
				closest_aim = next_step;
				aim_found = true;
			}

			if (isVacant(territory[next_step])) {
				sight[relative_next.x][relative_next.y] = sight[relative_step.x][relative_step.y] + 1;
				steps.push(next_step);
			}

			if (aim_found)
				break;
		}
	}

	if (aim_found)
		aim_found = trace(aim_proximity);
	return aim_found;
}

bool Animal::trace(std::size_t proximity) {
	//route.clear();
	Coords destination = closest_aim;

	Coords step = toRelative(destination);
	std::size_t step_n = proximity;

	while (step_n != 1) {
		std::array<Coords, 4> steps;
		steps[Coords::UP] = step.up();
		steps[Coords::DOWN] = step.down();
		steps[Coords::LEFT] = step.left();
		steps[Coords::RIGHT] = step.right();

		unsigned short dir = 0;
		for (Coords next : steps) {
			/*if (!territory.inBound(toReal(next)) || !inSight(next)) {
				++dir;
				continue;
			}*/
			if (territory.inBound(toReal(next))
				&& inSight(next)
				&& sight[next.x][next.y] == step_n - 1) {

				if (dir == Coords::UP)
					route.push_back(Coords::DOWN);
				else if (dir == Coords::DOWN)
					route.push_back(Coords::UP);
				else if (dir == Coords::LEFT)
					route.push_back(Coords::RIGHT);
				else if (dir == Coords::RIGHT)
					route.push_back(Coords::LEFT);

				step = next;
				break;
			}
			++dir;
		}
		--step_n;
	}

	return toReal(step) == position; //traced back to itself
}



bool Animal::getSex() const {
	return sex;
}



bool Animal::inSight(Coords pos) const {
	return pos.x >= 0 && pos.y >= 0 && pos.x < 2 * FOV + 1 && pos.y < 2 * FOV + 1;
}

bool Animal::isVacant(Park::Tile tile) const {
	return tile.animal == nullptr;
}

bool Animal::isAim(Aim aim, Park::Tile tile) const {
	bool is_aim = false;
	if (aim == FOOD)
		is_aim = isFood(tile);
	else if (aim == PARTNER)
		is_aim = isPartner(tile);
	else if (aim == ENEMY)
		is_aim = isEnemy(tile);

	return is_aim;
}



Coords Animal::toReal(Coords relative) const {
	return position - FOV + relative;
}

Coords Animal::toRelative(Coords real) const {
	return real + FOV - position;
}