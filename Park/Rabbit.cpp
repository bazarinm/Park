#include "Rabbit.h"
#include "Park.h"

Rabbit::Rabbit(Coords pos, const Park& territory) : 
	Animal(3, pos, territory, 4, RABBIT)
{
	++rabbit_count;
}

size_t Rabbit::rabbit_count = 0;

Rabbit::~Rabbit() {
	Death();
}

size_t Rabbit::getCount() {
	return rabbit_count;
}

//---

void Rabbit::Behave() {
	if (nutr == 0 || isOld())
		Death();
	else if (isHungry() && seekFood()) //hungry and found food nearby
		eat();
	else if (isReady() && seekPartner()) //ready and found partner nearby
		Procreate();
	else
		Idle();

	++age;
}

//---

void Rabbit::Idle() {
	--nutr;
	last_action = IDLE;
}

bool Rabbit::Procreate() {
	children.clear(); // VERY IMPORTANT!!!!
	bool procreate = false;
	
	move(); //reaching partner
	if ((closest_partner - pos).length() < 2) { //reached partner
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
				last_action = MOVE;
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
	if (!is_dead) {
		is_dead = true;
		--rabbit_count;
		last_action = DEATH;
	}
}

//---

bool Rabbit::isFood(Creatures creature) const {
	return creature == GRASS;
}

bool Rabbit::isPartner(Creatures creature) const {
	return creature == RABBIT;
}

bool Rabbit::isEnemy(Creatures creature) const {
	return creature == FOX;
}

//---

bool Rabbit::isHungry() const {
	return nutr <= 3;
}

bool Rabbit::isReady() const {
	return age % PERIOD == 0 && age >= READY_AGE;
}

bool Rabbit::isScared() const {
	return (closest_enemy - pos).length() <= 3;
}

bool Rabbit::isOld() const {
	return age > MAX_AGE;
}
