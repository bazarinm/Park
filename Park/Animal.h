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
	enum Diet { CARNIVORE, HERBIVORE };
	enum Aim { FOOD, PARTNER, ENEMY };

	Animal(
		Species, Diet diet, Species food, unsigned nutrition,
		std::size_t FOV, unsigned move_length, 
		const Park& territory, Coords pos,
		unsigned nutrients
		);
	virtual ~Animal() = default;

	void behave() override;

	bool getSex() const;

	virtual bool isFood(Park::Tile) const;
	virtual bool isPartner(Park::Tile) const;
	virtual bool isEnemy(Park::Tile) const;
protected:
	const int FOV;
	Coords closest_aim;
	std::vector<std::vector<int>> sight;
	std::vector<Coords::Direction> route;
	bool search(Aim);

	const unsigned short move_length;
	virtual bool move(Aim);

	const Diet diet;
	const Species food;
	virtual bool eat();

	bool sex;
	bool procreate() override;
	virtual Animal* mate(Coords spot) = 0;

	bool idle() override;

	const unsigned min_nutrients;
	bool isHungry() const;
	
	//const unsigned min_enemy_distance;
	virtual bool isScared();

	const unsigned max_age;
	virtual bool isOld();

	bool isVacant(Park::Tile tile) const override;
	virtual bool inProximity(Aim) const = 0;
private:
	bool inSight(Coords) const;
	bool isAim(Aim, Park::Tile) const;

	bool trace(std::size_t proximity);

	Coords toReal(Coords) const;
	Coords toRelative(Coords) const;
};

#endif

