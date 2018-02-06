#ifndef ANIMAL_H
#define ANIMAL_H

#include "Creature.h"
#include "Park.h"

#include <vector>

class Animal :
	public Creature
{
public:
	enum Aim { FOOD, PARTNER, ENEMY };

	Animal(unsigned nutr, Coords pos, const Park& territory, int FOV, Species type);
	virtual ~Animal() = default;

	bool getSex() const;
	virtual bool isReady() const = 0;

	virtual bool isFood(Park::Tile) const = 0;
	virtual bool isPartner(Park::Tile) const = 0;
	virtual bool isEnemy(Park::Tile) const = 0;
protected:
	bool sex;

	void scan();
	const int FOV;
	Coords closest_food;
	Coords closest_partner;
	Coords closest_enemy;
	std::vector<std::vector<int>> sight;
	std::vector<Coords::Direction> route_to_food;
	std::vector<Coords::Direction> route_to_partner;
	std::vector<Coords::Direction> route_to_enemy;

	//alternative
	bool search(Aim);
	bool trace(std::size_t proximity);
	bool isAim(Aim, Park::Tile) const;
	Coords closest_aim;
	std::vector<Coords::Direction> route;


	virtual bool eat() = 0;
	//virtual bool move() = 0;
	virtual bool move(Aim) = 0;

	virtual bool isHungry() const = 0;
	virtual bool isScared() const = 0;
	virtual bool isOld() const = 0;

	bool isVacant(Park::Tile tile) const override;
	virtual bool inProximity(Aim) const = 0;
private:
	bool inSight(Coords) const;

	void trace(Aim, std::size_t proximity);

	Coords toReal(Coords) const;
	Coords toRelative(Coords) const;
};

#endif

