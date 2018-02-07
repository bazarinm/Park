#include "Rabbit.h"
#include "Park.h"

Rabbit::Rabbit(const Park& _territory, Coords _position) :
	Animal(
		RABBIT, HERBIVORE, RABBIT_NUTRITION, 
		RABBIT_FOV, RABBIT_JUMP_LENGTH,
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



bool Rabbit::isFood(Park::Tile tile) const {
	bool is_food = false;
	if (tile.animal == nullptr || tile.animal == this) //either no animal or itself standing on the tile
		is_food = tile.plant != nullptr && tile.plant->getSpecies() == GRASS;

	return is_food;
}

bool Rabbit::isPartner(Park::Tile tile) const {
	bool is_partner = false;
	if (tile.animal != nullptr && tile.animal != this) {
		const Creature* p = tile.animal;
		//const Animal* p = dynamic_cast<const Animal*>(tile.animal);
			if (p->getSpecies() == species && p->isReady())
				is_partner = true;
	}

	return is_partner;
}

bool Rabbit::isEnemy(Park::Tile tile) const {
	return tile.animal != nullptr && tile.animal->getSpecies() == FOX;
}

//---

bool Rabbit::isHungry() const {
	return nutrients <= 3;
}

bool Rabbit::isReady() const {
	bool is_ready = false;
	if (age == RABBIT_READY_AGE)
		is_ready = true;
	else if (age > RABBIT_READY_AGE && age % RABBIT_PERIOD == 0)
		is_ready = true;

	return is_ready;
}

bool Rabbit::isScared() const {
	//search(ENEMY);
	//return (closest_enemy - position).length() <= 3;
	return false; //temporary
}

bool Rabbit::isOld() const {
	return age > RABBIT_MAX_AGE;
}

bool Rabbit::inProximity(Aim aim) const {
	bool in_proximity = false;
	if (aim == FOOD)
		in_proximity = (closest_aim - position).length() == 0;
	else if (aim == PARTNER)
		in_proximity = (closest_aim - position).length() <= 1;

	return in_proximity;
}
