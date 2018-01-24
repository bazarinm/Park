#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
class Rabbit :
	public Animal
{
public:
	Rabbit(unsigned nutr, Coords pos);
	~Rabbit();

	//void Behave() override;
private:
	//void Eat() override;
	//void Move() override;
	//Rabbit* Procreate() override;
};

#endif

