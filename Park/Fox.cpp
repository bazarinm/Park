#include "Fox.h"

Fox::Fox(const Park& _territory, Coords _position) :
	Animal(
		FOX, CARNIVORE, FOX_NUTRITION,
		FOX_FOV, FOX_MOVE_LENGTH,
		_territory, _position, FOX_START_NUTRIENTS)
{
	++fox_count;
}

std::size_t Fox::fox_count = 0;

Fox::~Fox() {
	death();
}

std::size_t Fox::getCount() {
	return fox_count;
}


//---

Fox* Fox::mate(Coords spot) {
	return new Fox(territory, spot);
}

bool Fox::death() {
	if (!is_dead) {
		is_dead = true;
		--fox_count;
	}
	last_action = DEATH;

	return is_dead;
}

//---

bool Fox::isFood(Park::Tile tile) const {
	return tile.animal != nullptr && tile.animal->getSpecies() == RABBIT;
}

bool Fox::isPartner(Park::Tile tile) const {
	bool is_partner = false;
	if (tile.animal != nullptr) {
		const Animal* p = dynamic_cast<const Animal*>(tile.animal);
		if (p->getSpecies() == species && p->isReady())
			is_partner = true;
	}
	return is_partner;
}

bool Fox::isEnemy(Park::Tile tile) const {
	return false; //foxes has no enemies!
}

//---

bool Fox::isHungry() const {
	return nutrients <= 4;
}

bool Fox::isReady() const {
	return age % FOX_PERIOD == 0 && age >= FOX_READY_AGE && !isHungry();
}

bool Fox::isScared() const {
	return false;
}

bool Fox::isOld() const {
	return age > FOX_MAX_AGE;
}

//---

bool Fox::inProximity(Aim aim) const {
	bool in_proximity = false;
	if (aim == FOOD)
		in_proximity = (closest_aim - position).length() <= 1;
	else if (aim == PARTNER)
		in_proximity = (closest_aim - position).length() <= 1;
	return in_proximity;
}