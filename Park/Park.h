#ifndef PARK_H
#define PARK_H

#include "Creature.h"
#include "Utility.h"
//#include "Fox.h"
//#include "Grass.h"
//#include "Rabbit.h"

struct Tile { Creature* grass; std::vector<Creature*> rabbits; std::vector<Creature*> foxes; };

#include <queue>
#include <array>

const int WIDTH = 10;
const int HEIGHT = 10;
using Field = std::array<std::array<Tile, WIDTH>, HEIGHT>;

class Park
{
public:
	Park();
	
	void Simulation();
	std::vector<std::vector<Creatures>> GetSight(Coords coords, int FOV) const;
	Creatures GetType(Creature*) const;
	void Draw() const;
	void Add(Creature*);
	void Remove(Creature*);
private:
	Field field;
	std::queue<Creature*> creatures;
};

#endif