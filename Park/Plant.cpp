#include "Plant.h"

Plant::Plant(
	Species _species,
	unsigned _nutrition, 
	const Park& _territory, 
	Coords _position,
	unsigned _nutrients
) :
	Creature(PLANT, _species, _nutrition, _territory, _position, _nutrients)
{
}

bool Plant::isVacant(Park::Tile tile) const {
	return tile.animal == nullptr && tile.plant == nullptr;
}

