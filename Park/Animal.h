#ifndef ANIMAL_H
#define ANIMAL_H

#include "Creature.h"
class Animal :
	public Creature
{
public:
	Animal();

private:
	virtual void Eat() = 0;
	virtual void Move() = 0;
};

#endif

