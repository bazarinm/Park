#ifndef ANIMAL_H
#define ANIMAL_H

#include "Creature.h"
#include "Park.h"

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

	Coords closest_food;
	Coords closest_partner;
	Coords closest_enemy;

	const int FOV;
	std::vector<std::vector<int>> sight;

	void scan();

	std::vector<Coords::Direction> route_to_food;
	std::vector<Coords::Direction> route_to_partner;
	std::vector<Coords::Direction> route_to_enemy;

	virtual bool eat() = 0;
	//virtual bool move() = 0;
	virtual bool move(Aim) = 0;

	virtual bool isHungry() const = 0;
	virtual bool isScared() const = 0;
	virtual bool isOld() const = 0;

	bool isVacant(Park::Tile tile) const override;
private:
	bool inSight(Coords) const;

	void trace(Aim, size_t proximity);

	Coords toReal(Coords) const;
	Coords toRelative(Coords) const;
};

#endif

