#ifndef CREATURE_H
#define CREATURE_H

#include "Utility.h"

#include <vector>

class Park;

class Creature
{
public:
	Creature(unsigned nutr, Coords pos, const Park& territory);

	virtual Action Behave() = 0;
	Coords GetPos() const;
	std::vector<Creature*> GetOffs() const;
	Creatures GetType() const;
	bool GetStatus() const;

	virtual void Death() = 0;
protected:
	const Park& territory;
	std::vector<std::vector<Creatures>> sight;
	unsigned age;
	Creatures type;
	unsigned nutr;
	Coords rel_pos;
	Coords pos;
	std::vector<Creature*> offsprings;
	bool is_dead;

	Coords Convert(Coords, int FOV) const;
	bool InBound(Coords, int FOV) const;
private:
	virtual void Idle() = 0;

	virtual bool Procreate() = 0;
};

#endif

