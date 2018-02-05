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

	void behave() final;
	static size_t getCount();
private:
	static size_t grass_count;

	void idle() final;
	void death() final;
	bool procreate() final;
	void photosynthesis() final;
};

#endif

