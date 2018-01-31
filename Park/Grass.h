#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"
#include "Park.h"
#include <vector>

class Grass :
	public Plant
{
public:
	Grass(Coords pos);
	~Grass();

	Action Behave(const Park*) override;

	void Death() override;
private:
	//std::vector<std::vector<Creatures>> Sight;
	int FOV;
	void Idle() override;

	void Procreate() override;
	void Photosynthesis() override;
};

#endif

