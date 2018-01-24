#include "Grass.h"



Grass::Grass()
{
	nutrients = 5;
}


Grass::~Grass()
{
}

int Grass::FOV = 1;

Grass* Grass::Procreate() {

}

void Grass::Behave(const Park* park) {
	Sight = park->GetSight(coords, FOV);
	if (nutrients > 5)
		Procreate();
	else
		Photosynthesis();
}
