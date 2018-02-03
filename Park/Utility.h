#ifndef UTILITY_H
#define UTILITY_H

#include <queue>
#include <array>
#include <vector>

enum Creatures { BARRIER, DIRT, GRASS, RABBIT, FOX };

enum Action { MOVE, EAT, PROCREATE, IDLE, PHOTOSYNTH, DEATH };

struct Coords { 
	enum Direction { UP, DOWN, LEFT, RIGHT };

	int x; int y; 

	float length() const { return sqrt(x^2 + y^2); }

	bool operator==(Coords& r) { return x == r.x && y == r.y; } 
	bool operator!=(Coords& r) { return !(*this == r); }

	Coords operator+(const Coords& r) const { return { x + r.x, y + r.y }; }
	Coords operator-(const Coords& r) const { return { x - r.x, y - r.y }; }
	Coords operator+(int r) const { return { x + r, y + r }; }
	Coords operator-(int r) const { return { x - r, y - r }; }
	void operator+=(const Coords& r) { *this = *this + r; }
	bool operator<(const Coords& r) { return x ^ 2 + y ^ 2 < (r.x) ^ 2 + (r.y) ^ 2; }
	bool operator>(const Coords& r) { return !operator<(r); }
	bool operator==(const Coords& r) { return x == r.x && y == r.y; }
	bool operator!=(const Coords& r) { return !operator==(r); }

	Coords up() const { return { x + 1, y }; }
	Coords down() const { return { x - 1, y }; }
	Coords left() const { return { x, y - 1 }; }
	Coords right() const { return { x, y + 1 }; }
};

template<class T>
struct Matrix {
	std::vector<std::vector<T>> mat;

	T& operator[](Coords pos) { return mat[pos.x][pos.y]; }
	T operator[](Coords pos) const { return mat[pos.x][pos.y]; }
};

#endif 