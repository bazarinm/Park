#ifndef PARK_H
#define PARK_H

#include "Utility.h"
#include "Settings.h"
#include <queue>
#include <array>

class Creature;
class Plant;
class Animal;

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
	std::queue<std::pair<Creature*, Coords>> creatures;
	Tile& operator[](Coords);
};

#endif