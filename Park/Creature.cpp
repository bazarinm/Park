#include "Creature.h"



Creature::Creature(unsigned _nutr, Coords _pos): nutr(_nutr), pos(_pos), is_dead(false)
{
}


//Creature::~Creature()
//{
//}

Coords Creature::GetPos() const {
	return pos;
}

Creatures Creature::GetType() const {
	return type;
}

bool Creature::GetStatus() const {
	return is_dead;
}

std::vector<Creature*> Creature::GetOffs() const {
	return offsprings;
}