#include "Animal.h"

#include "Park.h"

Animal::Animal(unsigned nutr, Coords pos, const Park& territory, int FOV): 
	Creature(nutr, pos, territory, FOV)
{
}

void Animal::look() {
	for(int i = -FOV; i <= FOV; ++i)
		for (int j = -FOV; j <= FOV; ++j) {
			Coords dir = { i, j };
			if (isFood(territory[dir]) && (closest_food - pos) < (dir - pos))
				closest_food = dir;
			else if (isPartner(territory[dir]) && (closest_partner - pos) < (dir - pos))
				closest_partner = dir;
			if (isEnemy(territory[dir]) && (closest_enemy - pos) < (dir - pos))
				closest_enemy = dir;
		}
			
}

//Animal::~Animal()
//{
//}
