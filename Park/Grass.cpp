#include "Grass.h"



Grass::Grass(Coords pos, const Park& territory): 
	Plant(6, pos, territory, GRASS)
{
	++grass_count;
}

size_t Grass::grass_count = 0;

Grass::~Grass()
{
	Death();
}

size_t Grass::getCount() {
	return grass_count;
}

bool Grass::Procreate() {
	children.clear(); // VERY IMPORTANT!!!!
	bool procreate = false;

	std::array<Coords, 4> spots;
	for (unsigned i = 0; i < 4; ++i)
		spots[i] = { -1, -1 };

	std::array<Coords, 4> directions;
	directions[Coords::UP] = pos.up();
	directions[Coords::DOWN] = pos.down();
	directions[Coords::LEFT] = pos.left();
	directions[Coords::RIGHT] = pos.right();

	unsigned dir = 0;
	for (Coords direction : directions) {
		if (isVacant(territory[direction])) {
			spots[dir] = direction;
			++dir;
		}
	}
	
	for (Coords spot : spots) 
		if (spot.x != -1) { //!not_found
			Grass* offspring = new Grass(spot, territory);
			children.push_back(offspring);
			procreate = true;
			last_action = PROCREATE;
		}

	return procreate;
}

void Grass::Idle() {
	++age;
}

void Grass::Photosynthesis() {
	++nutr;
}

void Grass::Death() {
	if (!is_dead) {
		is_dead = true;
		--grass_count;
		last_action = DEATH;
	}
}

void Grass::Behave() {
	
	if (age <= 4)
		Procreate();
	else
		Death();
}
