#include "Animal.h"

#include "Park.h"

Animal::Animal(unsigned nutr, Coords pos, const Park& territory, int _FOV, Species type):
	FOV(_FOV),
	Creature(nutr, pos, territory, ANIMAL, type)
{
}

bool Animal::getSex() const {
	return sex;
}

void Animal::scan() {
	sight = std::vector<std::vector<int>>(2 * FOV + 1, std::vector<int>(2 * FOV + 1, 0));

	sight[FOV][FOV] = 1; 
	std::queue<Coords> steps;
	steps.push(position);

	bool food_found = false, 
		 partner_found = false, 
		 enemy_found = false,
		 all_found = false;

	size_t food_proximity, partner_proximity, enemy_proximity;

	while (!steps.empty() && !all_found) {
		Coords step = steps.front(); steps.pop(); //relative to territory
		Coords relative_step = toRelative(step); //relative to sight

		std::array<Coords, 4> next_steps;
		next_steps[Coords::UP] = step.up();
		next_steps[Coords::DOWN] = step.down();
		next_steps[Coords::LEFT] = step.left();
		next_steps[Coords::RIGHT] = step.right();

		for (Coords next_step : next_steps) { //relative to territory
			Coords relative_next = toRelative(next_step); //relative to sight

			if (!territory.inBound(next_step) || !inSight(relative_next) || next_step == position)
				continue;

			if (!food_found && isFood(territory[next_step])) {
				food_proximity = sight[relative_step.x][relative_step.y] + 1;
				closest_food = next_step;
				food_found = true;
			}
			else if (!partner_found && isPartner(territory[next_step])) {
				partner_proximity = sight[relative_step.x][relative_step.y] + 1;
				closest_partner = next_step;
				partner_found = true;
			}
			else if (!enemy_found && isEnemy(territory[next_step])) {
				enemy_proximity = sight[relative_step.x][relative_step.y] + 1;
				closest_enemy = next_step;
				enemy_found = true;
			}
			
			if (isVacant(territory[next_step]) && sight[relative_next.x][relative_next.y] == 0) {
				sight[relative_next.x][relative_next.y] = sight[relative_step.x][relative_step.y] + 1;
				steps.push(next_step);
			}

			all_found = food_found && partner_found && enemy_found;

			if (all_found)
				break;
		}
	}

	if (food_found)
		trace(FOOD, food_proximity);
	if (partner_found)
		trace(PARTNER, partner_proximity);
	if (enemy_found)
		trace(ENEMY, enemy_proximity);
	return;
}

void Animal::trace(Aim aim, size_t proximity) {
	Coords destination;
	std::vector<Coords::Direction>* path = nullptr;
	if (aim == FOOD) {
		destination = closest_food;
		path = &route_to_food;
	}
	else if (aim == PARTNER) {
		destination = closest_partner;
		path = &route_to_partner;
	}
	else if (aim == ENEMY) {
		destination = closest_enemy;
		path = &route_to_enemy;
	}
	else
		return;

	path->clear(); // VERY IMPORTANT!

	Coords step = toRelative(destination);
	size_t step_n = proximity;

	while (step_n != 1) {
		std::array<Coords, 4> steps;
		steps[Coords::UP] = step.up();
		steps[Coords::DOWN] = step.down();
		steps[Coords::LEFT] = step.left();
		steps[Coords::RIGHT] = step.right();

		unsigned dir = 0;
		for (Coords next : steps) {
			if (!territory.inBound(toReal(next)) || !inSight(next)) {
				++dir;
				continue;
			}

			if (sight[next.x][next.y] == step_n - 1) {
				if (dir == Coords::UP)
					path->push_back(Coords::DOWN);
				else if (dir == Coords::DOWN)
					path->push_back(Coords::UP);
				else if (dir == Coords::LEFT)
					path->push_back(Coords::RIGHT);
				else if (dir == Coords::RIGHT)
					path->push_back(Coords::LEFT);

				step = next;
				break;
			}

			++dir;
		}
		--step_n;
	}
}



bool Animal::inSight(Coords pos) const {
	return pos.x >= 0 && pos.y >= 0 && pos.x < 2 * FOV+1 && pos.y < 2 * FOV + 1;
}

bool Animal::isVacant(Park::Tile tile) const {
	return tile.animal == nullptr;
}



Coords Animal::toReal(Coords relative) const {
	return position - FOV + relative;
}

Coords Animal::toRelative(Coords real) const {
	return real + FOV - position;
}