#include "Rabbit.h"
#include "Park.h"

Rabbit::Rabbit(Coords pos) : Animal(6, pos), FOV(3)
{

}


Rabbit::~Rabbit()
{
}

Action Rabbit::Behave(const Park* park) {
	Action act = IDLE;
	sight = park->GetSight(pos, FOV);
	See();

	if (!is_dead) {
		if (age > 7 || nutr == 0) {
			Death();
			act = DEATH;
		}
		else if (nutr <= 3 && closest_grass.x != -1) {
			//Move(closest_grass);
			Eat();
			act = EAT;
		}
		else if (nutr >= 6 && age % 3 == 0 && closest_rabbit.x != -1) {
			Procreate();
			act = PROCREATE;
		}
		else { Idle(); act = IDLE; };
		//else if 

		++age;
	}
	else
		act = DEATH;

	return act;
}

void Rabbit::Idle() {
	--nutr;
}

void Rabbit::Procreate() {
	Move(closest_rabbit);
	Rabbit* offspring = new Rabbit(pos);
	offsprings.push_back(offspring);
	nutr -= 3;
}

void Rabbit::Eat() {
	Move(closest_grass);
	nutr += 3;
}

void Rabbit::Move(Coords direction) {
	pos = direction;
	--nutr;
}

void Rabbit::Death() {
	is_dead = true;
}

void Rabbit::See() {
	std::queue<Coords> steps;
	steps.push({ FOV, FOV });

	bool grass_found = false;
	bool rabbit_found = false;
	bool fox_found = false;

	closest_grass = { -1, -1 };
	closest_rabbit = { -1, -1 };
	closest_fox = { -1, -1 };

	Coords step;
	while (!steps.empty()) {
		step = steps.front(), steps.pop();
		sight[step.x][step.y] = BARRIER;

		std::array<Coords, 4> next;
		next[0] = up(step);
		next[1] = down(step);
		next[2] = left(step);
		next[3] = right(step);

		for (Coords next_step : next) {
			if (!InBound(next_step, FOV))
				continue;
			if (sight[next_step.x][next_step.y] != BARRIER) {
				steps.push(next_step);

				if (sight[next_step.x][next_step.y] == GRASS && !grass_found) {
					closest_grass = Convert(next_step, FOV);
					grass_found = true;
				}
				else if (sight[next_step.x][next_step.y] == RABBIT && !rabbit_found) {
					closest_rabbit = Convert(next_step, FOV);
					rabbit_found = true;
				}
				else if (sight[next_step.x][next_step.y] == FOX && !fox_found) {
					closest_fox = Convert(next_step, FOV);
					fox_found = true;
				}

				sight[next_step.x][next_step.y] = BARRIER;
			}
		}

		if (grass_found && rabbit_found && fox_found)
			break;
	}
}

Coords Rabbit::up(Coords pos) const {
	--pos.x;
	return pos;
}
Coords Rabbit::down(Coords pos) const {
	++pos.x;
	return pos;
}
Coords Rabbit::left(Coords pos) const {
	--pos.y;
	return pos;
}
Coords Rabbit::right(Coords pos) const {
	++pos.y;
	return pos;
}
