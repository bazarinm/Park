#include "Grass.h"



Grass::Grass(Coords pos) : Plant(6, pos), FOV(1)
{
	type = GRASS;
}

Grass::~Grass()
{
}


void Grass::Procreate() {
	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
			if (sight[FOV + i][FOV + j] == Creatures::DIRT) {
				Grass* offspring = new Grass({ pos.x + i, pos.y + j });
				offsprings.push_back(offspring);
				nutr -= 3;
				return;
			}
}

void Grass::Idle() {
	++age;
	return;
}

void Grass::Photosynthesis() {
	++nutr;
}

void Grass::Death() {
	is_dead = true;
}

Action Grass::Behave(const Park* park) {
	Action act = IDLE;
	
	if (!is_dead) {
		offsprings.clear();
		sight = park->GetSight(pos, FOV);

		if (nutr != 0) {
			Procreate();
			act = PROCREATE;
		}
		else {
			Death();
			act = DEATH;
		}
	}
	else
		act = DEATH;

	return act;
}
