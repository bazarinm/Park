#include "Park.h"
#include "Grass.h"
#include <iostream>

Park::Park()
{
	for (size_t i = 0; i < HEIGHT; ++i)
		for (size_t j = 0; j < WIDTH; ++j)
			field[i][j] = Creatures::DIRT;

	Grass* g = new Grass({ 3, 7 });
	field[3][7] = GRASS;
	creatures.push(g);
}

//Park::~Park()
//{
//}

void Park::Simulation() {
	Draw();

	while (!creatures.empty()) {
		Creature* current_creature = creatures.front();
		current_creature->Behave(this);

		std::vector<Creature*> offsprings = current_creature->GetOffs();
		for (Creature* creature : offsprings) {
			Coords c_pos = creature->GetPos();
			field[c_pos.x][c_pos.y] = creature->GetType();
			creatures.push(creature);
		}

		Draw();
	}

}

std::vector<std::vector<Creatures>> Park::GetSight(Coords pos, int FOV) const {
	std::vector<std::vector<Creatures>> sight(FOV * 2 + 1, std::vector<Creatures>(FOV * 2 + 1));

	size_t k = 0, l = 0;
	for (int i = (-1)*FOV; i < FOV + 1; ++i) {
		for (int j = (-1)*FOV; j < FOV + 1; ++j) {
			if (pos.x > HEIGHT - i || pos.y > WIDTH - j
				|| pos.x  < (-1)*i || pos.y < (-1)*j)
				sight[k][l] = Creatures::BARRIER;
			else
				sight[k][l] = field[pos.x + i][pos.y + j];
			++l;
		}
		l = 0;
		++k;
	}

	return sight;
}

void Park::Draw() const {
	for (size_t i = 0; i < HEIGHT; ++i) {
		for (size_t j = 0; j < WIDTH; ++j) {
			if (field[i][j] == DIRT)
				std::cout << 'D';
			else if (field[i][j] == GRASS)
				std::cout << 'G';
			else if (field[i][j] == RABBIT)
				std::cout << 'R';
			else if (field[i][j] == FOX)
				std::cout << 'F';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}
