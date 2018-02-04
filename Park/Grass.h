#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"
#include <vector>

class Park;

class Grass :
	public Plant
{
public:
	Grass(Coords pos, const Park& territory);
	~Grass();

	void Behave() override;
	static size_t getCount();

private:
	static size_t grass_count;
	void Idle() override;
	void Death() override;
	bool Procreate() override;
	void Photosynthesis() override;
};

#endif

