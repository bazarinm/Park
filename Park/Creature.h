#ifndef CREATURE_H
#define CREATURE_H

#include "Utility.h"

struct Coords { size_t x; size_t y; };

class Creature
{
public:
	Creature();

	virtual void Behave(const Park*) = 0;

protected:
	unsigned int nutrients;
	Coords coords;

private:
	
	virtual Creature* Procreate() = 0;
};

#endif

