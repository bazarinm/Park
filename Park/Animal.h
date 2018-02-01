#ifndef ANIMAL_H
#define ANIMAL_H

#include "Creature.h"

class Animal :
	public Creature
{
public:
	Animal(unsigned nutr, Coords pos);

private:
	virtual bool Eat() = 0;
	virtual bool Move(Coords) = 0;
};

#endif

