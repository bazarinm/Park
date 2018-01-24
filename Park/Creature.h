#ifndef CREATURE_H
#define CREATURE_H

#include "Utility.h"

#include <vector>

class Park;

class Creature
{
public:
	Creature(unsigned nutr, Coords pos);

	virtual void Behave(const Park*) = 0;
	Coords GetPos() const;
	std::vector<Creature*> GetOffs() const;
	Creatures GetType() const;
protected:
	static const Creatures type;
	unsigned int nutr;
	Coords pos;
	std::vector<Creature*> offsprings;
private:
	
	virtual void Procreate() = 0;
};

#endif

