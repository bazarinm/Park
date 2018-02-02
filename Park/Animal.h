#ifndef ANIMAL_H
#define ANIMAL_H

#include "Creature.h"

class Animal :
	public Creature
{
public:
	Animal(unsigned nutr, Coords pos, const Park& _territory, int FOV);
protected:
	bool sex;

	Coords closest_food;
	Coords closest_partner;
	Coords closest_enemy;

	void look();
private:
	virtual bool eat() = 0;
	virtual bool move(Coords) = 0;

	virtual bool isFood(Creatures) = 0;
	virtual bool isPartner(Creatures) = 0;
	virtual bool isEnemy(Creatures) = 0;
};

#endif

