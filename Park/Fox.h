#ifndef FOX_H
#define FOX_H

#include "Animal.h"

class Fox :
	public Animal
{
public:
	const unsigned MOVE_LENGTH = 3;
	const unsigned MAX_AGE = 20;
	const unsigned PERIOD = 2;
	const unsigned READY_AGE = 4;

	Fox(Coords pos, const Park& territory);
	~Fox();

	void behave() final;

	static size_t getCount();
private:
	static size_t fox_count;

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

