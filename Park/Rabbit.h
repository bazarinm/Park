#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
#include "Park.h"

const unsigned RABBIT_FOV = 5;
const unsigned RABBIT_JUMP_LENGTH = 2;
const unsigned RABBIT_MAX_AGE = 11;
const unsigned RABBIT_PERIOD = 2;
const unsigned RABBIT_READY_AGE = 3;
const unsigned RABBIT_REACH = 1;

class Rabbit :
	public Animal
{
public:
	Rabbit(Coords pos, const Park& territory);
	~Rabbit();

	void behave() final;

	static std::size_t getCount();
private:
	static std::size_t rabbit_count;

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

	bool inProximity(Aim) const final;
};

#endif

