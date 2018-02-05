#ifndef PLANT_H
#define PLANT_H

#include "Creature.h"
#include "Park.h"

class Plant :
	public Creature
{
public:
	Plant(unsigned nutr, Coords pos, const Park& _territory, Species type);
	virtual ~Plant() = default;
protected:
	bool isVacant(Park::Tile pos) const override;
private:
	virtual void Photosynthesis() = 0;
};

#endif

