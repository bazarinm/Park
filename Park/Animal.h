#ifndef ANIMAL_H
#define ANIMAL_H

#include "Creature.h"

#include "Park.h"
#include "Utility.h"
#include <vector>

class Animal :
	public Creature
{
public:
	enum Aim { FOOD, PARTNER, ENEMY };

	Animal(unsigned nutr, Coords pos, const Park& territory, int FOV, Species type);
	virtual ~Animal() = default;

	bool getSex() const;
	//virtual bool isReady() const = 0;

	virtual bool isFood(Park::Tile) const = 0;
	virtual bool isPartner(Park::Tile) const = 0;
	virtual bool isEnemy(Park::Tile) const = 0;
protected:
	bool sex;

	const int FOV;
	Coords closest_aim;
	std::vector<std::vector<int>> sight;
	std::vector<Coords::Direction> route;

	bool search(Aim);

	virtual bool eat() = 0;
	virtual bool move(Aim) = 0;

	virtual bool isHungry() const = 0;
	virtual bool isScared() const = 0;
	virtual bool isOld() const = 0;

	bool isVacant(Park::Tile tile) const override;
	virtual bool inProximity(Aim) const = 0;
	//void scan();
	//Coords closest_food;
	//Coords closest_partner;
	//Coords closest_enemy;
	//std::vector<Coords::Direction> route_to_food;
	//std::vector<Coords::Direction> route_to_partner;
	//std::vector<Coords::Direction> route_to_enemy;
	//void trace(Aim, std::size_t proximity);
private:
	bool inSight(Coords) const;
	bool isAim(Aim, Park::Tile) const;

	bool trace(std::size_t proximity);

	Coords toReal(Coords) const;
	Coords toRelative(Coords) const;
};

#endif

