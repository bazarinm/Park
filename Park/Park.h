#ifndef PARK_H
#define PARK_H

//#include "Grass.h"
//#include "Fox.h"
//#include "Rabbit.h"
#include "Creature.h"
#include "Utility.h"

#include <queue>
#include <array>

const size_t WIDTH = 10;
const size_t HEIGHT = 10;
using Field = std::array<std::array<Creatures, WIDTH>, HEIGHT>;

class Park
{
public:
	Park();
	
	void Simulation();
	std::vector<std::vector<Creatures>> GetSight(Coords coords, int FOV) const;
	void Draw() const;
private:
	Field field;
	std::queue<Creature*> creatures;
};

#endif