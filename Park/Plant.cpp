#include "Plant.h"



Plant::Plant(unsigned nutr, Coords pos, const Park& territory, Creatures type): 
	Creature(nutr, pos, territory, type)
{
}

bool Plant::isVacant(Creatures pos) const {
	return pos == DIRT;
}

//Plant::~Plant()
//{
//}
