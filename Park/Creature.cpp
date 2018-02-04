#include "Creature.h"
#include "Park.h"


Creature::Creature(unsigned _nutr, Coords _pos, const Park& _territory, Genus _genus, Species _type): 
	nutr(_nutr), pos(_pos), territory(_territory), genus(_genus), type(_type), is_dead(false), age(0)
{
	
}

Action Creature::getAction() const {
	return last_action;
}

Coords Creature::GetPos() const {
	return pos;
}

Species Creature::getType() const {
	return type;
}

Genus Creature::getGenus() const {
	return genus;
}

bool Creature::GetStatus() const {
	return is_dead;
}

std::vector<Creature*> Creature::GetOffs() const {
	return children;
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

//bool Creature::InBound(Coords pos) const {
//	return pos.x >= 0 && pos.y >= 0 && pos.x <= 2 * FOV && pos.y <= 2 * FOV;
//}
