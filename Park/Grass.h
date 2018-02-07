#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"
#include <vector>

class Park;

const unsigned GRASS_NUTRITION = 4;
const unsigned GRASS_START_NUTRIENTS = 1;

class Grass :
	public Plant
{
public:
	Grass(const Park& territory, Coords pos);
	~Grass();

	void behave() final;
	static std::size_t getCount();
	bool isReady() const final;
private:
	static std::size_t grass_count;

	bool idle() final;
	bool death() final;
	bool procreate() final;
	void photosynthesis() final;
};

#endif

