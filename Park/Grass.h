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
	static std::size_t getCount();
	bool isReady() const final;
private:
	static std::size_t grass_count;

	void idle() final;
	void death() final;
	bool procreate() final;
	void photosynthesis() final;

};

#endif

