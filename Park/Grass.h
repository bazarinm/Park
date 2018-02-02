#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"
#include "Park.h"
#include <vector>

class Grass :
	public Plant
{
public:
	Grass(Coords pos, const Park& territory);
	~Grass();

	Action Behave() override;

	void Death() override;
private:
	//std::vector<std::vector<Creatures>> Sight;
	//int FOV;
	void Idle() override;

	bool Procreate() override;
	void Photosynthesis() override;
};

#endif

