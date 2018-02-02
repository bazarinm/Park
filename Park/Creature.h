#ifndef CREATURE_H
#define CREATURE_H

#include "Utility.h"

#include <vector>

class Park;

class Creature
{
public:
	Creature(unsigned nutr, Coords pos, const Park& territory, int FOV);

	virtual Action Behave() = 0;
	Coords GetPos() const;
	std::vector<Creature*> GetOffs() const;
	Creatures GetType() const;
	bool GetStatus() const;

	virtual void Death() = 0;
protected:
	const Park& territory;
	const int FOV;
	std::vector<std::vector<Creatures>> sight;
	unsigned age;
	Creatures type;
	unsigned nutr;
	Coords center;
	Coords pos;
	std::vector<Creature*> offsprings;
	bool is_dead;

	Coords closest_grass;
	Coords closest_rabbit;
	Coords closest_fox;

	bool grass_found;
	bool rabbit_found;
	bool fox_found;

	Coords ConvToReal(Coords) const;
	Coords ConvToRelat(Coords) const;
	bool InBound(Coords) const;
	void GetSight();
private:
	virtual void Idle() = 0;
	virtual bool Procreate() = 0;


	void See();

	Coords up(Coords) const;
	Coords down(Coords) const;
	Coords left(Coords) const;
	Coords right(Coords) const;
};

#endif

