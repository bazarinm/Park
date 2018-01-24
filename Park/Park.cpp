#include "Park.h"



Park::Park()
{
}

void Park::Simulation() {
	Creature* current_creature = creatures.front(); creatures.pop();
	//current_creature->Behave();


}

std::vector<std::vector<Creatures>> Park::GetSight(Coords coords, int FOV) const {
	std::vector<std::vector<Creatures>> sight(FOV * 2 + 1, std::vector<Creatures>(FOV*2 + 1));

	for (int i = (-1)*FOV; i < FOV; ++i) {
		for (int j = (-1)*FOV; j < FOV; ++j) {
			if (coords.x < WIDTH - i|| coords.y < HEIGHT - j)
				sight[coords.x + i][coords.y + j] = Creatures::BARRIER;
			else
				sight[coords.x + i][coords.y + j] = field[coords.x + i][coords.y + j];

		}
	}

	return sight;
}

//Park::~Park()
//{
//}
