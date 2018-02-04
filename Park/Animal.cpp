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

bool Animal::seekFood() {
	sight = std::vector<std::vector<int>>(2 * FOV + 1, std::vector<int>(2 * FOV + 1, -2));
	
	sight[FOV][FOV] = 0;
	std::queue<Coords> steps;
	steps.push(pos);

	bool found = false;
	while (!steps.empty() && !found) {
		Coords step = steps.front(); steps.pop(); //relative to territory
		Coords relat_step = toRelative(step); //relative to sight

		std::array<Coords, 4> next;
		next[Coords::UP] = step.up();
		next[Coords::DOWN] = step.down();
		next[Coords::LEFT] = step.left();
		next[Coords::RIGHT] = step.right();

		for (Coords next_step : next) { //relative to territory
			Coords relat_next = toRelative(next_step); //relative to sight
			if (!inSight(relat_next) || !territory.inBound(next_step) || next_step == pos)
				continue;

			if (isFood(territory[next_step])) {
				sight[relat_next.x][relat_next.y] = sight[relat_step.x][relat_step.y] + 1;
				closest_food = next_step; //relative to territory
				found = true;
			}
			else if (isVacant(territory[next_step]))
				if (sight[relat_next.x][relat_next.y] == -2) {
					sight[relat_next.x][relat_next.y] = sight[relat_step.x][relat_step.y] + 1;
					steps.push(next_step);
				}

			if (found)
				break;
		}
	}

	if (found)
		trace(closest_food);
	return found;
}

void Animal::trace(Coords real_dest) {
	route.clear();
	Coords step = toRelative(real_dest);
	size_t step_n = sight[step.x][step.y];

	while (step_n != 0) {
		std::array<Coords, 4> steps;
		steps[Coords::UP] = step.up();
		steps[Coords::DOWN] = step.down();
		steps[Coords::LEFT] = step.left();
		steps[Coords::RIGHT] = step.right();

		unsigned dir = 0;
		for (Coords next : steps) {
			if (inSight(next)) {
				if (sight[next.x][next.y] == step_n - 1) {
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
			}

			++dir;
		}
		--step_n;
	}
}

bool Animal::seekPartner() {
	sight = std::vector<std::vector<int>>(2 * FOV + 1, std::vector<int>(2 * FOV + 1, -2));

	sight[FOV][FOV] = 0;
	std::queue<Coords> steps;
	steps.push(pos);

	bool found = false;
	while (!steps.empty() && !found) {
		Coords step = steps.front(); steps.pop(); //relative to territory
		Coords relat_step = toRelative(step); //relative to sight

		std::array<Coords, 4> next;
		next[Coords::UP] = step.up();
		next[Coords::DOWN] = step.down();
		next[Coords::LEFT] = step.left();
		next[Coords::RIGHT] = step.right();

		for (Coords next_step : next) { //relative to territory
			Coords relat_next = toRelative(next_step); //relative to sight

			if (!inSight(relat_next) || !territory.inBound(next_step) || next_step == pos)
				continue;

			if (isPartner(territory[next_step])) {
				sight[relat_next.x][relat_next.y] = sight[relat_step.x][relat_step.y] + 1;
				closest_partner = next_step; //relative to territory
				found = true;
			}
			else if (isVacant(territory[next_step])) 
				if (sight[relat_next.x][relat_next.y] == -2) {
					sight[relat_next.x][relat_next.y] = sight[relat_step.x][relat_step.y] + 1;
					steps.push(next_step);
				}

			if (found)
				break;
		}
	}

	if (found)
		trace(closest_partner);
	return found;
}

bool Animal::seekEnemy() {
	sight = std::vector<std::vector<int>>(2 * FOV + 1, std::vector<int>(2 * FOV + 1));

	std::queue<Coords> steps;
	steps.push(pos);

	bool found = false;
	while (!steps.empty() && !found) {
		Coords step = steps.front(); steps.pop(); //relative to territory
		Coords relat_step = toRelative(step); //relative to sight

		std::array<Coords, 4> next;
		next[Coords::UP] = step.up();
		next[Coords::DOWN] = step.down();
		next[Coords::LEFT] = step.left();
		next[Coords::RIGHT] = step.right();

		for (Coords next_step : next) { //relative to territory
			Coords relat_next = toRelative(next_step); //relative to sight
			if (!inSight(relat_step))
				continue;

			if (sight[relat_next.x][relat_next.y] == 0 && next_step != pos) {
				if (isFood(territory[next_step])) {
					closest_food = next_step; //relative to territory
					found = true;
				}
				else if (isVacant(territory[next_step]))
					sight[relat_next.x][relat_next.y] = sight[relat_step.x][relat_step.y] + 1;

				steps.push(next_step);
			}
		}
	}

	trace(closest_enemy);
	return found;
}


bool Animal::inSight(Coords pos) const {
	return pos.x >= 0 && pos.y >= 0 && pos.x < 2*FOV+1 && pos.y < 2*FOV+1;
}

bool Animal::isVacant(Park::Tile tile) const {
	return tile.animal == nullptr;
}

Coords Animal::toReal(Coords relative) const {
	return pos - FOV + relative;
}

Coords Animal::toRelative(Coords real) const {
	return real + FOV - pos;
}