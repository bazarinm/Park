#ifndef CREATURE_H
#define CREATURE_H

#include "Utility.h"
#include "Park.h"
#include <vector>

class Creature
{
public:
	Creature(unsigned nutr, Coords pos, const Park& territory, Genuses genus, Species type);
	virtual ~Creature() = default;

	virtual void behave() = 0;

	Action getAction() const;
	Coords getPos() const;
	std::vector<Creature*> getOffsprings() const;
	Species getSpecies() const;
	Genuses getGenus() const;
	bool isDead() const;
	virtual bool isReady() const = 0;
protected:
	const Park& territory;
	const Genuses genus;
	const Species species;

	Action last_action;
	unsigned age;
	unsigned nutrients;
	Coords position;
	std::vector<Creature*> offsprings;
	bool is_dead;

	virtual bool isVacant(Park::Tile tile) const = 0;
	Coords findSpot(Coords pos) const;

	virtual void idle() = 0;
	virtual bool procreate() = 0;
	virtual void death() = 0;
private:
	//
};

#endif

