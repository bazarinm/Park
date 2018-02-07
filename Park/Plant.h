#ifndef PLANT_H
#define PLANT_H

#include "Creature.h"
#include "Park.h"

class Plant :
	public Creature
{
public:
	Plant(Species species, unsigned nutrition, const Park& _territory, Coords pos, unsigned nutrients);
	virtual ~Plant() = default;

protected:
	bool isVacant(Park::Tile pos) const final;
private:
	virtual void photosynthesis() = 0;
};

#endif

