#include "Grass.h"

#include <iostream>

Grass::Grass(const Park& territory, Coords position): 
	Plant(GRASS, GRASS_NUTRITION, territory, position, GRASS_START_NUTRIENTS)
{
	++grass_count;
}

std::size_t Grass::grass_count = 0;

Grass::~Grass()
{
	death();
}

std::size_t Grass::getCount() {
	return grass_count;
}

bool Grass::procreate() {
	offsprings.clear(); // VERY IMPORTANT!!!!
	bool procreate = false;

	std::array<Coords, 4> spots;
	for (unsigned i = 0; i < 4; ++i)
		spots[i] = { -1, -1 };

	std::array<Coords, 4> directions;
	directions[Coords::UP] = position.up();
	directions[Coords::DOWN] = position.down();
	directions[Coords::LEFT] = position.left();
	directions[Coords::RIGHT] = position.right();

	unsigned dir = 0;
	for (Coords direction : directions) {
		if (territory.inBound(direction) && isVacant(territory[direction])) {
			spots[dir] = direction;
			++dir;
		}
	}
	
	for (Coords spot : spots) 
		if (spot.x != -1) { //!not_found
			Grass* offspring = new Grass(territory, spot);
			offsprings.push_back(offspring);
			procreate = true;
			last_action = PROCREATE;
		}

	return procreate;
}

bool Grass::idle() {
	++age;
	last_action = IDLE;
	return true;
}

void Grass::photosynthesis() {
	++nutrients;
}

bool Grass::death() {
	if (!is_dead) {
		is_dead = true;
		--grass_count;
		last_action = DEATH;
	}

	return is_dead;
}

void Grass::behave() {
	last_action = IDLE;

	if (isReady())
		procreate();
	else
		idle();

	++age;
}

bool Grass::isReady() const {
	return age % 1 == 0;
}
