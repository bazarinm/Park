#include "Creature.h"

#include "Park.h"
#include "Utility.h"
#include <array>

Creature::Creature(
	Genuses _genus,
	Species _species,
	unsigned _nutrition,
	const Park& _territory,
	Coords _pos,
	unsigned _nutrients
) : 
	genus(_genus),
	species(_species),
	nutrition(_nutrition),

	territory(_territory),
	position(_pos),

	nutrients(_nutrients),
	is_dead(false), 
	age(0)
{
	last_action = IDLE;
}

Creature::Creature(
	Genuses _genus,
	Species _species,
	unsigned _nutrition,
	const Park& _territory
) :
	genus(_genus),
	species(_species),
	nutrition(_nutrition),

	territory(_territory),

	is_dead(false)
{
	last_action = IDLE;
}



unsigned Creature::getNutrition() const {
	return nutrition;
}

Action Creature::getAction() const {
	return last_action;
}

Coords Creature::getPos() const {
	return position;
}

Species Creature::getSpecies() const {
	return species;
}

Genuses Creature::getGenus() const {
	return genus;
}

bool Creature::isDead() const {
	return is_dead;
}

std::vector<Creature*> Creature::getOffsprings() const {
	return offsprings;
}

Coords Creature::findSpot(Coords center) const {
	Coords spot = { -1, -1 };

	std::array<Coords, 4> directions;
	directions[Coords::UP] = center.up();
	directions[Coords::DOWN] = center.down();
	directions[Coords::LEFT] = center.left();
	directions[Coords::RIGHT] = center.right();

	for (Coords direction : directions) {
		if (territory.inBound(direction) && isVacant(territory[direction])) {
			spot = direction;
			break;
		}
	}

	return spot;
}
