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

	Coords operator+(const Coords& r) const { return { x + r.x, y + r.y }; }
	Coords operator-(const Coords& r) const { return { x - r.x, y - r.y }; }
	Coords operator+(int r) const { return { x + r, y + r }; }
	Coords operator-(int r) const { return { x - r, y - r }; }
	void operator+=(const Coords& r) { *this = *this + r; }
	bool operator<(const Coords& r) { return x ^ 2 + y ^ 2 < (r.x) ^ 2 + (r.y) ^ 2; }
	bool operator>(const Coords& r) { return !operator<(r); }

	Coords up(Coords pos) const { --pos.x; return pos; }
	Coords down(Coords pos) const { ++pos.x; return pos; }
	Coords left(Coords pos) const { --pos.y; return pos; }
	Coords right(Coords pos) const { ++pos.y; return pos; }
};

#endif 