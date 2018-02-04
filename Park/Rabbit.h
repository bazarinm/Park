#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
#include "Park.h"

class Rabbit :
	public Animal
{
public:
	const unsigned _FOV = 7;
	const unsigned JUMP_LENGTH = 2;
	const unsigned MAX_AGE = 10;
	const unsigned PERIOD = 3;
	const unsigned READY_AGE = 3;

	Rabbit(Coords pos, const Park& territory);
	~Rabbit();

	void Behave() override;

	const unsigned jump_length = 2;

	static size_t getCount();
private:
	static size_t rabbit_count;

	bool eat() override;
	void Idle() override;
	bool move() override;
	void Death() override;
	bool Procreate() override;

	bool isHungry() const override;
	bool isReady() const override;
	bool isScared() const override;
	bool isOld() const override;

	bool isFood(Park::Tile) const override;
	bool isPartner(Park::Tile) const override;
	bool isEnemy(Park::Tile) const override;
};

#endif

