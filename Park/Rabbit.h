#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
#include "Park.h"

class Rabbit :
	public Animal
{
public:
	const unsigned JUMP_LENGTH = 2;
	const unsigned MAX_AGE = 11;
	const unsigned PERIOD = 2;
	const unsigned READY_AGE = 2;

	Rabbit(Coords pos, const Park& territory);
	~Rabbit();

	void behave() final;

	static size_t getCount();
private:
	static size_t rabbit_count;

	bool eat() final;
	void idle() final;
	bool move(Aim) final;
	void death() final;
	bool procreate() final;

	bool isHungry() const final;
	bool isReady() const final;
	bool isScared() const final;
	bool isOld() const final;

	bool isFood(Park::Tile) const final;
	bool isPartner(Park::Tile) const final;
	bool isEnemy(Park::Tile) const final;
};

#endif

