#ifndef ANIMAL_H
#define ANIMAL_H

#include "Creature.h"

class Animal :
	public Creature
{
public:
	Animal(unsigned nutr, Coords pos, const Park& territory, int FOV, Creatures type);
	//~Animal();

protected:
	Coords closest_food;
	Coords closest_partner;
	Coords closest_enemy;

	const int FOV;
	std::vector<std::vector<int>> sight;
	std::vector<Coords::Direction> route;

	bool seekFood();
	bool seekPartner();
	bool seekEnemy();

	bool isVacant(Creatures tile) const override; 
private:
	bool sex;

	bool inSight(Coords) const;

	virtual bool eat() = 0;
	virtual bool move() = 0;

	virtual bool isHungry() const = 0;
	virtual bool isReady() const = 0;
	virtual bool isScared() const = 0;
	virtual bool isOld() const = 0;

	virtual bool isFood(Creatures) const = 0;
	virtual bool isPartner(Creatures) const = 0;
	virtual bool isEnemy(Creatures) const = 0;

	void trace(Coords);

	Coords toReal(Coords) const;
	Coords toRelative(Coords) const;
};

#endif

