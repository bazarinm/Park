#ifndef FOX_H
#define FOX_H

#include "Animal.h"

#include "Park.h"
#include "Utility.h"

class Fox :
	public Animal
{
public:
	Fox(const Park& territory, Coords);
	~Fox();

	static std::size_t getCount();
private:
	static std::size_t fox_count;

	Fox* mate(Coords spot) final;
	bool death() final;

	//bool isHungry() const final;
	//bool isReady() const final;
	//bool isScared() const final;
	//bool isOld() const final;
	//bool isFood(Park::Tile) const final;
	//bool isPartner(Park::Tile) const final;
	//bool isEnemy(Park::Tile) const final;
	//bool inProximity(Aim) const final;
};

#endif

