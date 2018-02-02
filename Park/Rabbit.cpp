#include "Rabbit.h"
#include "Park.h"

Rabbit::Rabbit(Coords pos, const Park& territory) : 
	Animal(6, pos, territory, 3)
{

}


Rabbit::~Rabbit()
{
}

Action Rabbit::Behave() {
	Action act = IDLE;
	GetSight();

	if (!is_dead) {
		if (age >= 11 || nutr == 0) {
			Death();
			act = DEATH;
		}
		else if (nutr <= 2 && grass_found) {
			eat();
			act = EAT;
		}
		else if (nutr >= 4 && age % 2 == 0 && age != 0 && rabbit_found) {
			Procreate();
			act = PROCREATE;
		}
		else { Idle(); act = IDLE; };

		++age;
	}
	else
		act = DEATH;

	center = pos;

	return act;
}

void Rabbit::Idle() {
	--nutr;
}

bool Rabbit::Procreate() {
	move(closest_rabbit);

	Coords direction = ConvToRelat(pos);
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			direction += {i, j};
			if (InBound(direction))
				if (sight[direction.x][direction.y] == GRASS || sight[direction.x][direction.y] == DIRT) {
					Rabbit* offspring = new Rabbit(ConvToReal(direction), territory);
					nutr -= 3;
					offsprings.push_back(offspring);
					return true;
				}
		}
	}

	return false;
}

bool Rabbit::eat() {
	pos = closest_grass;
	nutr += 4;
	return true;
}

bool Rabbit::move(Coords direction) {
	direction = ConvToRelat(direction);
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			direction += {i, j};
			if (InBound(direction))
				if (sight[direction.x][direction.y] == GRASS || sight[direction.x][direction.y] == DIRT) {
					pos = ConvToReal(direction);
					--nutr;
					return true;
				}
		}
	}

	return false;
}

void Rabbit::Death() {
	is_dead = true;
}

//void Rabbit::See() {
//	std::queue<Coords> steps;
//	steps.push({ FOV, FOV });
//
//	bool grass_found = false;
//	bool rabbit_found = false;
//	bool fox_found = false;
//
//	closest_grass = { -1, -1 };
//	closest_rabbit = { -1, -1 };
//	closest_fox = { -1, -1 };
//
//	Coords step;
//
//	std::vector<std::vector<Creatures>> temp = sight;
//	while (!steps.empty()) {
//		step = steps.front(), steps.pop();
//		temp[step.x][step.y] = BARRIER;
//
//		std::array<Coords, 4> next;
//		next[0] = up(step);
//		next[1] = down(step);
//		next[2] = left(step);
//		next[3] = right(step);
//
//		for (Coords next_step : next) {
//			if (!InBound(next_step, FOV))
//				continue;
//			if (temp[next_step.x][next_step.y] != BARRIER) {
//				steps.push(next_step);
//
//				if (temp[next_step.x][next_step.y] == GRASS && !grass_found) {
//					closest_grass = next_step;
//					grass_found = true;
//				}
//				else if (temp[next_step.x][next_step.y] == RABBIT && !rabbit_found) {
//					closest_rabbit = next_step;
//					rabbit_found = true;
//				}
//				else if (temp[next_step.x][next_step.y] == FOX && !fox_found) {
//					closest_fox = next_step;
//					fox_found = true;
//				}
//
//				temp[next_step.x][next_step.y] = BARRIER;
//			}
//		}
//
//		if (grass_found && rabbit_found && fox_found)
//			break;
//	}
//}

//Coords Rabbit::up(Coords pos) const {
//	--pos.x;
//	return pos;
//}
//Coords Rabbit::down(Coords pos) const {
//	++pos.x;
//	return pos;
//}
//Coords Rabbit::left(Coords pos) const {
//	--pos.y;
//	return pos;
//}
//Coords Rabbit::right(Coords pos) const {
//	++pos.y;
//	return pos;
//}
