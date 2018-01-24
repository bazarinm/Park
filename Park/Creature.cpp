#include "Creature.h"



Creature::Creature(unsigned _nutr, Coords _pos): nutr(_nutr), pos(_pos)
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

std::vector<Creature*> Creature::GetOffs() const {
	return offsprings;
}