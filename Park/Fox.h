#ifndef FOX_H
#define FOX_H

#include "Animal.h"
class Fox :
	public Animal
{
public:
	Fox(unsigned nutr, Coords pos);
	~Fox();

	//void Behave() override;
private:
	//void Eat() override;
	//void Move() override;
	//Fox* Procreate() override;
};

#endif

