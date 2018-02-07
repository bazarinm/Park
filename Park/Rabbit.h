#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
#include "Park.h"

const unsigned RABBIT_NUTRITION = 6;
const unsigned RABBIT_START_NUTRIENTS = 5;
const unsigned RABBIT_FOV = 4;
const unsigned RABBIT_JUMP_LENGTH = 2;
const unsigned RABBIT_MAX_AGE = 10;
const unsigned RABBIT_PERIOD = 2;
const unsigned RABBIT_READY_AGE = 3;
const unsigned RABBIT_REACH = 1;

class Rabbit :
	public Animal
{
public:
	Rabbit(const Park& territory, Coords);
	~Rabbit();

	//void behave() final;

	static std::size_t getCount();
	bool isReady() const final;
private:
	static std::size_t rabbit_count;

	Rabbit* mate(Coords spot) final;
	bool death() final;

	bool isHungry() const final;
	bool isScared() const final;
	bool isOld() const final;

	bool isFood(Park::Tile) const final;
	bool isPartner(Park::Tile) const final;
	bool isEnemy(Park::Tile) const final;

	bool inProximity(Aim) const final;
};

#endif

