#include "Grass.h"

#include <iostream>

Grass::Grass(Coords pos, const Park& territory): 
	Plant(6, pos, territory, GRASS)
{
	++grass_count;
}

size_t Grass::grass_count = 0;

Grass::~Grass()
{
	//std::cout << "test";
	death();
}

size_t Grass::getCount() {
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
			Grass* offspring = new Grass(spot, territory);
			offsprings.push_back(offspring);
			procreate = true;
			last_action = PROCREATE;
		}

	return procreate;
}

void Grass::idle() {
	++age;
}

void Grass::photosynthesis() {
	++nutrients;
}

void Grass::death() {
	if (!is_dead) {
		is_dead = true;
		--grass_count;
		last_action = DEATH;
	}
}

void Grass::behave() {
	
	if (age <= 10)
		procreate();
	else
		death();

	//++age;
}
