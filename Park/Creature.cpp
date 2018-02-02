#include "Creature.h"
#include "Park.h"


Creature::Creature(unsigned _nutr, Coords _pos, const Park& _territory, int _FOV = 0): 
	nutr(_nutr), center(_pos), pos(_pos), territory(_territory), FOV(_FOV), is_dead(false), age(0)
{
	sight.resize(FOV * 2 + 1);
	for (size_t i = 0; i < sight.size(); ++i)
		sight[i].resize(FOV * 2 + 1);
}


//Creature::~Creature()
//{
//}

void Creature::GetSight() {
	size_t k = 0, l = 0;
	for (int i = -FOV; i <= FOV; ++i) {
		for (int j = -FOV; j <= FOV; ++j) {
			Coords look = { pos.x + i, pos.y + j };
			sight[k][l] = territory[look];
			++l;
		}
		++k;
		l = 0;
	}

	See();
}

Coords Creature::GetPos() const {
	return pos;
}

Creatures Creature::GetType() const {
	return type;
}

bool Creature::GetStatus() const {
	return is_dead;
}

std::vector<Creature*> Creature::GetOffs() const {
	return offsprings;
}

Coords Creature::ConvToReal(Coords relative) const {
	return center - FOV + relative;
}

Coords Creature::ConvToRelat(Coords real) const {
	return real + FOV - center;
}

bool Creature::InBound(Coords pos) const {
	return pos.x >= 0 && pos.y >= 0 && pos.x <= 2 * FOV && pos.y <= 2 * FOV;
}

void Creature::See() {
	std::queue<Coords> steps;
	steps.push({ FOV, FOV });

	grass_found = false;
	rabbit_found = false;
	fox_found = false;

	std::vector<std::vector<Creatures>> temp_sight = sight;
	while (!steps.empty()) {
		Coords step = steps.front(); steps.pop();
		temp_sight[step.x][step.y] = BARRIER;

		std::array<Coords, 4> next;
		next[0] = up(step);
		next[1] = down(step);
		next[2] = left(step);
		next[3] = right(step);

		for (Coords next_step : next) {
			if (!InBound(next_step))
				continue;
			if (temp_sight[next_step.x][next_step.y] != BARRIER) {
				if (!grass_found && temp_sight[next_step.x][next_step.y] == GRASS) {
					closest_grass = ConvToReal(next_step);
					grass_found = true;
				}
				else if (!rabbit_found && temp_sight[next_step.x][next_step.y] == RABBIT) {
					closest_rabbit = ConvToReal(next_step);
					rabbit_found = true;
				}
				else if (!fox_found && temp_sight[next_step.x][next_step.y] == FOX) {
					closest_fox = ConvToReal(next_step);
					fox_found = true;
				}

				temp_sight[next_step.x][next_step.y] = BARRIER;
				steps.push(next_step);
			}
		}

		if (grass_found && rabbit_found && fox_found)
			break;
	}
}

Coords Creature::up(Coords pos) const {
	--pos.x;
	return pos;
}
Coords Creature::down(Coords pos) const {
	++pos.x;
	return pos;
}
Coords Creature::left(Coords pos) const {
	--pos.y;
	return pos;
}
Coords Creature::right(Coords pos) const {
	++pos.y;
	return pos;
}