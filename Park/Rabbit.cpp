#include "Rabbit.h"
#include "Park.h"

Rabbit::Rabbit(Coords pos, const Park& territory) : 
	Animal(6, pos, territory, 3)
{
}

void Rabbit::Behave() {
	if (isHungry() && seekFood()) //hungry and found food
		eat();
	else if (isReady() && seekPartner()) //ready and found partner
		Procreate();
	else
		Idle();
}

void Rabbit::Idle() {
	--nutr;
	last_action = IDLE;
}

bool Rabbit::Procreate() {
	bool procreate = false;
	
	move(); //reaching partner
	if ((closest_partner - pos).length() > 1) { //reached partner
		Coords spot = findSpot(pos); //relative to territory
		if (spot.x != -1) { //!not found
			Rabbit* child = new Rabbit(spot, territory);
			children.push_back(child);
			nutr -= 2;
			procreate = true;
			last_action = PROCREATE;
		}
	}

	return procreate;
}

bool Rabbit::eat() {
	bool eat = false;

	move(); //reaching food
	if (isFood(territory[pos])) { //reached food
		nutr += 4;
		eat = true;
		last_action = EAT;
	}

	return eat;
}

bool Rabbit::move() {
	bool move = false;

	for (unsigned i = 0; i < jump_length; ++i) {
		if (!route.empty()) {
			Coords::Direction step = route.back(); route.pop_back();
			Coords next;

			if (step == Coords::UP)
				next = pos.up();
			else if (step == Coords::DOWN)
				next = pos.down();
			else if (step == Coords::LEFT)
				next = pos.left();
			else if (step == Coords::RIGHT)
				next = pos.right();

			if (isVacant(territory[next])) {
				pos = next;
				--nutr;
				move = true;
			}
			else
				break; //an obstacle is blocking movement or position near partner has been reached
		}
		else
			break;
	}

	return move;
}

void Rabbit::Death() {
	is_dead = true;
}

bool Rabbit::isFood(Creatures creature) const {
	return creature == GRASS;
}

bool Rabbit::isPartner(Creatures creature) const {
	return creature == RABBIT;
}

bool Rabbit::isEnemy(Creatures creature) const {
	return creature == FOX;
}

bool Rabbit::isHungry() const {
	return nutr <= 3;
}

bool Rabbit::isReady() const {
	return age % 3 == 0 && age >= 3;
}

bool Rabbit::isScared() const {
	return (closest_enemy - pos).length() <= 3;
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
