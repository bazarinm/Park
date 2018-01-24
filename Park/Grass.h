#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"
#include <vector>
#include "Park.h"
class Grass :
	public Plant
{
public:
	Grass();
	~Grass();

	void Behave(const Park*) override;
private:
	std::vector<std::vector<Creatures>> Sight;
	static int FOV;
	Grass* Procreate() override;
	void Photosynthesis() override;
};

#endif

