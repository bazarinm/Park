#include "Rabbit.h"

#include "Settings.h"

Rabbit::Rabbit(const Park& _territory, Coords _position) :
	Animal(
		RABBIT, 
		HERBIVORE, GRASS, RABBIT_NUTRITION, 
		RABBIT_FOV, RABBIT_JUMP_LENGTH,
		FOX,
		RABBIT_MIN_NUTRIENTS, 
		RABBIT_MAX_AGE,
		RABBIT_PERIOD, RABBIT_READY_AGE,
		_territory, _position, RABBIT_START_NUTRIENTS)
{
	++rabbit_count;
}

std::size_t Rabbit::rabbit_count = 0;

Rabbit::~Rabbit() {
	death();
}



std::size_t Rabbit::getCount() {
	return rabbit_count;
}



Rabbit* Rabbit::mate(Coords spot) {
	return new Rabbit(territory, spot);
}

bool Rabbit::death() {
	if (!is_dead) { 
		is_dead = true;
		--rabbit_count;
	}
	last_action = DEATH;
	return is_dead;
}
