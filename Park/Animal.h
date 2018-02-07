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
		Species, 
		Diet diet, Species food, unsigned nutrition,
		std::size_t FOV, unsigned move_length, 
		Species enemy,
		unsigned min_nutrients, 
		unsigned max_age,
		unsigned period, unsigned ready_age, 
		const Park& territory, Coords pos,
		unsigned nutrients
		);
	virtual ~Animal() = default;

	void behave() override;

	bool getSex() const;
	bool isReady() const;
	bool isFood(Park::Tile) const;

protected:
	const int FOV;
	Coords closest_aim;
	std::vector<std::vector<int>> sight;
	std::vector<Coords::Direction> route;
	bool search(Aim);

	const unsigned short move_length;
	bool move(Aim);

	const Diet diet;
	const Species food;
	virtual bool eat();

	bool sex;
	const unsigned period;
	const unsigned ready_age;
	bool procreate() override;
	virtual Animal* mate(Coords spot) = 0;

	bool idle() override;

	const unsigned min_nutrients;
	bool isHungry() const;
	
	//const unsigned min_enemy_distance;
	const Species enemy;
	bool isScared() const;

	const unsigned max_age;
	bool isOld() const;

	bool isVacant(Park::Tile tile) const override;

	bool isPartner(Park::Tile) const;
	bool isEnemy(Park::Tile) const;

	bool inProximity(Aim) const;
private:
	bool inSight(Coords) const;
	bool isAim(Aim, Park::Tile) const;

	bool trace(std::size_t proximity);

	Coords toReal(Coords) const;
	Coords toRelative(Coords) const;
};

#endif

