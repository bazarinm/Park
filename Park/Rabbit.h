#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
#include "Park.h"



class Rabbit :
	public Animal
{
public:
	Rabbit(const Park& territory, Coords);
	~Rabbit();

	static std::size_t getCount();
private:
	static std::size_t rabbit_count;

	Rabbit* mate(Coords spot) final;
	bool death() final;

	//bool isHungry() const final;
	//bool isScared() const final;
	//bool isOld() const final;
	//bool isFood(Park::Tile) const final;
	//bool isPartner(Park::Tile) const final;
	//bool isEnemy(Park::Tile) const final;
	//bool inProximity(Aim) const final;
};

#endif

