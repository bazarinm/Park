#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
class Rabbit :
	public Animal
{
public:
	const unsigned JUMP_LENGTH = 2;
	const unsigned MAX_AGE = 10;
	const unsigned PERIOD = 3;
	const unsigned READY_AGE = 3;

	Rabbit(Coords pos, const Park& territory);
	~Rabbit();

	void Behave() override;

	void Death() override;

	const unsigned jump_length = 2;
private:
	//int FOV;
	bool eat() override;
	void Idle() override;
	bool move() override;
	bool Procreate() override;

	bool isHungry() const override;
	bool isReady() const override;
	bool isScared() const override;

	bool isFood(Creatures) const override;
	bool isPartner(Creatures) const override;
	bool isEnemy(Creatures) const override;
};

#endif

