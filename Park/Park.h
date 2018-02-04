#ifndef PARK_H
#define PARK_H

#include "Utility.h"
#include <queue>
#include <array>

class Creature;
class Plant;
class Animal;

const int WIDTH = 10;
const int HEIGHT = 10;

class Park
{
public:
	struct Tile { Plant* plant; Animal* animal; };
	using Field = std::array<std::array<Tile, WIDTH>, HEIGHT>;

	Park();
	
	void Simulation();
	//std::vector<std::vector<Creatures>> GetSight(Coords coords, int FOV) const;
	//Creatures GetType(Creature*) const;
	void Draw() const;
	void Add(Creature*);
	void Remove(Creature*);
	Tile operator[](Coords) const;
	bool inBound(Coords) const;
private:
	Field field;
	void Move(Creature* c, Coords old_pos);
	void Eat(Creature* c);
	bool isEaten(Creature* c);
	std::queue<Creature*> creatures;
	Tile& operator[](Coords);
};

#endif