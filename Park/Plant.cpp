#include "Plant.h"



Plant::Plant(unsigned nutr, Coords pos, const Park& territory, Species type): 
	Creature(nutr, pos, territory, PLANT, type)
{
}

bool Plant::isVacant(Park::Tile tile) const {
	return tile.animal == nullptr && tile.plant == nullptr;
}

//Plant::~Plant()
//{
//}
