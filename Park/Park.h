#ifndef PARK_H
#define PARK_H

#include "Grass.h"
#include "Fox.h"
#include "Rabbit.h"
#include "Utility.h"
#include <queue>
#include <array>

//enum Creatures { BARRIER, DIRT, GRASS, RABBIT, FOX};
const size_t WIDTH = 10;
const size_t HEIGHT = 10;
using Field = std::array<std::array<Creatures, WIDTH>, HEIGHT>;

class Park
{
public:
	Park();
	
	void Simulation();
	std::vector<std::vector<Creatures>> GetSight(Coords coords, int FOV) const;
private:
	Field field;
	std::queue<Creature*> creatures;
};

#endif