#ifndef CREATURE_H
#define CREATURE_H

#include "Utility.h"

#include <vector>

class Park;

class Creature
{
public:
	Creature(unsigned nutr, Coords pos);

	virtual Action Behave(const Park*) = 0;
	Coords GetPos() const;
	std::vector<Creature*> GetOffs() const;
	Creatures GetType() const;
	bool GetStatus() const;

	virtual void Death() = 0;
protected:
	std::vector<std::vector<Creatures>> sight;
	unsigned age;
	Creatures type;
	unsigned nutr;
	Coords pos;
	std::vector<Creature*> offsprings;
	bool is_dead;

	Coords Convert(Coords, int FOV) const;
	bool InBound(Coords, int FOV) const;
private:
	virtual void Idle() = 0;

	virtual void Procreate() = 0;
};

#endif

