#include "Grass.h"



Grass::Grass(Coords pos) : Plant(5, pos)
{
	
}

Grass::~Grass()
{
}

int Grass::FOV = 1;
const Creatures Grass::type = GRASS;


void Grass::Procreate() {
	for (int i = -1; i < 2; ++i)
		for (int j = -1; j < 2; ++j)
			if (Sight[1 + i][1 + j] == Creatures::DIRT) {
				Grass* offspring = new Grass({ pos.x + i, pos.y + j });
				offsprings.push_back(offspring);
				nutr -= 2;
				return;
			}
}

void Grass::Photosynthesis() {
	++nutr;
}

void Grass::Behave(const Park* park) {
	offsprings.clear();
	Sight = park->GetSight(pos, FOV);

	if (nutr >= 2)
		Procreate();
	else
		Photosynthesis();
}
