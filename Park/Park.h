#ifndef PARK_H
#define PARK_H

#include "Utility.h"
#include <queue>
#include <array>

class Creature;
class Plant;
class Animal;

const int WIDTH = 64;
const int HEIGHT = 32;

class Park
{
public:
	struct Tile {
		Tile() : plant(nullptr), animal(nullptr) {};
		Tile(Creature* a, Creature* b) : plant(a), animal(b) {};

		const Creature* plant; 
		const Creature* animal; 
	};

	using Field = std::array<std::array<Tile, WIDTH>, HEIGHT>;

	Park();
	~Park();
	
	void Simulation();

	void Draw() const;

	void Add(Creature*);
	void Remove(Creature*);
	Creature* generate(Species);

	Tile operator[](Coords) const;
	bool inBound(Coords) const;
private:
	Field field;

	void Move(Creature*, Coords old_pos);
	void Eat(Creature*);
	bool isEaten(Creature*);
	std::queue<Creature*> creatures;
	Tile& operator[](Coords);
};

#endif