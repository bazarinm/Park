#include "Creature.h"

#include "Park.h"
#include "Utility.h"

Creature::Creature(unsigned _nutr, Coords _pos, const Park& _territory, Genuses _genus, Species _type): 
	nutrients(_nutr), position(_pos), territory(_territory), genus(_genus), species(_type), is_dead(false), age(0)
{
	last_action = IDLE;
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
