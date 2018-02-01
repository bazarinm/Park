#ifndef FOX_H
#define FOX_H

#include "Animal.h"
class Fox :
	public Animal
{
public:
	Fox(Coords pos, const Park& _territory);
	~Fox();

	//void Behave() override;
private:
	//void Eat() override;
	//void Move() override;
	//Fox* Procreate() override;
};

#endif

