#ifndef FOX_H
#define FOX_H

#include "Animal.h"

#include "Park.h"
#include "Utility.h"

const unsigned FOX_FOV = 7;
const unsigned FOX_MOVE_LENGTH = 3;
const unsigned FOX_MAX_AGE = 20;
const unsigned FOX_PERIOD = 2;
const unsigned FOX_READY_AGE = 4;
const unsigned FOX_REACH = 1;

class Fox :
	public Animal
{
public:
	Fox(Coords pos, const Park& territory);
	~Fox();

	void behave() final;

	static std::size_t getCount();
private:
	static std::size_t fox_count;

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

