#ifndef PARK_H
#define PARK_H

#include "Creature.h"
#include "Utility.h"
//#include "Fox.h"
//#include "Grass.h"
//#include "Rabbit.h"

struct Tile { Creature* grass; Creature* rabbit; Creature* fox; };

#include <queue>
#include <array>

const int WIDTH = 30;
const int HEIGHT = 30;
using Field = std::array<std::array<Tile, WIDTH>, HEIGHT>;

class Park
{
public:
	Park();
	
	void Simulation();
	std::vector<std::vector<Creatures>> GetSight(Coords coords, int FOV) const;
	Creatures GetType(Creature*) const;
	void Draw() const;
	void Add(Creature*, Creatures type);
	void Remove(Creature*, Creatures type);
	Creatures operator[](Coords) const;
private:
	Field field;
	void Move(Creature* c,Creatures type, Coords old_pos);
	void Eat(Creature* c, Creatures type);
	bool isEaten(Creature* c, Creatures type);
	std::queue<Creature*> creatures;
	Tile& operator[](Coords);
	bool inBound(Coords) const;
};

#endif