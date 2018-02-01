#ifndef UTILITY_H
#define UTILITY_H

#include <queue>
#include <array>


enum Creatures { BARRIER, DIRT, GRASS, RABBIT, FOX };

enum Action { MOVE, EAT, PROCREATE, IDLE, PHOTOSYNTH, DEATH };

struct Coords { 
	int x; int y; 
	bool operator==(Coords& r) { return x == r.x && y == r.y; } 
	bool operator!=(Coords& r) { return !(*this == r); }
};

#endif 