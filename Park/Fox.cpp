#include "Fox.h"

#include "Settings.h"

Fox::Fox(const Park& _territory, Coords _position) :
	Animal(
		FOX,
		CARNIVORE, RABBIT, FOX_NUTRITION,
		FOX_FOV, FOX_MOVE_LENGTH,
		FOX,
		FOX_MIN_NUTRIENTS,
		FOX_MAX_AGE,
		FOX_PERIOD, FOX_READY_AGE,
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
