#ifndef PLANT_H
#define PLANT_H

#include "Creature.h"
class Plant :
	public Creature
{
public:
	Plant(unsigned nutr, Coords pos, const Park& _territory, Creatures type);
protected:
	bool isVacant(Creatures pos) const override;
private:
	virtual void Photosynthesis() = 0;
};

#endif

