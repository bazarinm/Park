#include "Creature.h"



Creature::Creature(unsigned _nutr, Coords _pos, const Park& _territory): 
	nutr(_nutr), pos(_pos), territory(_territory), is_dead(false), age(0)
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

Coords Creature::Convert(Coords relative, int FOV) const {
	Coords real = pos;
	real.x = real.x - FOV + relative.x;
	real.y = real.y - FOV + relative.y;
	return real;
}

bool Creature::InBound(Coords pos, int FOV) const {
	return (pos.x >= 0 && pos.y >= 0 && pos.x <= 2 * FOV && pos.y <= 2 * FOV);
}