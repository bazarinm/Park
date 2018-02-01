#ifndef PLANT_H
#define PLANT_H

#include "Creature.h"
class Plant :
	public Creature
{
public:
	Plant(unsigned nutr, Coords pos, const Park& _territory);
private:
	virtual void Photosynthesis() = 0;
};

#endif

