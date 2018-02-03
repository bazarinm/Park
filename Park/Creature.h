#ifndef CREATURE_H
#define CREATURE_H

#include "Utility.h"

#include <vector>

class Park;

class Creature
{
public:
	Creature(unsigned nutr, Coords pos, const Park& territory);

	virtual void Behave() = 0;
	Action getAction() const;
	Coords GetPos() const;
	std::vector<Creature*> GetOffs() const;
	Creatures GetType() const;
	bool GetStatus() const;
protected:
	const Park& territory;
	Creatures type;

	Action last_action;
	unsigned age;
	unsigned nutr;
	Coords pos;
	std::vector<Creature*> children;
	bool is_dead;

	virtual bool isVacant(Creatures pos) const = 0;
	Coords findSpot(Coords pos) const;
	bool InBound(Coords pos) const;
private:
	virtual void Idle() = 0;
	virtual bool Procreate() = 0;
	virtual void Death() = 0;

};

#endif

