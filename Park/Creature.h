#ifndef CREATURE_H
#define CREATURE_H

#include "Utility.h"
#include "Park.h"
#include <vector>

class Creature
{
public:
	Creature(unsigned nutr, Coords pos, const Park& territory, Genus genus, Species type);
	virtual ~Creature() = default;

	virtual void Behave() = 0;
	Action getAction() const;
	Coords GetPos() const;
	std::vector<Creature*> GetOffs() const;
	Species getType() const;
	Genus getGenus() const;
	bool GetStatus() const;
protected:
	const Park& territory;
	const Genus genus;
	const Species type;

	Action last_action;
	unsigned age;
	unsigned nutr;
	Coords pos;
	std::vector<Creature*> children;
	bool is_dead;

	virtual bool isVacant(Park::Tile tile) const = 0;
	Coords findSpot(Coords pos) const;
private:
	virtual void Idle() = 0;
	virtual bool Procreate() = 0;
	virtual void Death() = 0;

};

#endif

