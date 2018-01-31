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

	void Behave(const Park*) override;

private:
	std::vector<std::vector<Creatures>> Sight;
	static int FOV;
	void Death() override;
	void Procreate() override;
	void Photosynthesis() override;
};

#endif

