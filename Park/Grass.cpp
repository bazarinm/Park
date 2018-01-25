#include "Grass.h"



Grass::Grass(Coords pos) : Plant(6, pos)
{
	type = GRASS;
}

Grass::~Grass()
{
}

int Grass::FOV = 1;

void Grass::Procreate() {
	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
			if (Sight[FOV + i][FOV + j] == Creatures::DIRT) {
				Grass* offspring = new Grass({ pos.x + i, pos.y + j });
				offsprings.push_back(offspring);
				nutr -= 3;
				return;
			}
}

void Grass::Photosynthesis() {
	++nutr;
}

void Grass::Death() {
	is_dead = true;
}

void Grass::Behave(const Park* park) {
	offsprings.clear();
	Sight = park->GetSight(pos, FOV);

	if (nutr != 0)
		Procreate();
	else
		Death();
}
