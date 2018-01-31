#include "Park.h"
#include "Grass.h"
#include "Rabbit.h"
#include "Fox.h"
#include <iostream>
#include <typeinfo>

Park::Park()
{
	for (std::size_t i = 0; i < HEIGHT; ++i)
		for (std::size_t j = 0; j < WIDTH; ++j)
			field[i][j] = { nullptr, {}, {} };
}

//Park::~Park()
//{
//}

void Park::Add(Creature* c) {
	Coords pos = c->GetPos();
	Creatures type = GetType(c);

	if (type == GRASS) {
		field[pos.x][pos.y].grass = c;
	}
	else if (type == RABBIT) {
		field[pos.x][pos.y].rabbits.push_back(c);
	}
	else if (type == FOX) {
		field[pos.x][pos.y].foxes.push_back(c);
	}

	creatures.push(c);
}

void Park::Remove(Creature* c) {
	Coords pos = c->GetPos();
	Creatures type = GetType(c);

	if (type == GRASS) {
		field[pos.x][pos.y].grass = nullptr;
	}
	else if (type == RABBIT) {
		field[pos.x][pos.y].rabbits.pop_back();
	}
	else if (type == FOX) {
		field[pos.x][pos.y].foxes.pop_back();
	}
}

Creatures Park::GetType(Creature* c) const {
	Creatures type;
	
	if (typeid(*c) == typeid(Grass)) 
		type = GRASS;
	else if (typeid(*c) == typeid(Rabbit))
		type = RABBIT;
	else if (typeid(*c) == typeid(Fox))
		type = FOX;

	return type;
}

void Park::Simulation() {
	Draw();
	Action act;
	while (1) {
		std::size_t length = creatures.size();
		for (std::size_t i = 0; i < length; ++i) {
			Creature* current_creature = creatures.front(); creatures.pop();

			Coords old_pos = current_creature->GetPos();

			act = current_creature->Behave(this);

			if (act == PROCREATE) {
				Creatures type = GetType(current_creature);
				Coords pos = current_creature->GetPos();

				if (type == RABBIT) {
					field[old_pos.x][old_pos.y].rabbits.pop_back();

					field[pos.x][pos.y].rabbits.push_back(current_creature);
				}
				if (type == FOX) {
					field[old_pos.x][old_pos.y].foxes.pop_back();

					field[pos.x][pos.y].foxes.push_back(current_creature);
				}

				std::vector<Creature*> offsprings = current_creature->GetOffs();
				for (Creature* creature : offsprings) {
					Add(creature);
				}
			}

			else if (act == EAT) {
				Creatures type = GetType(current_creature);
				Coords pos = current_creature->GetPos();

				if (type == RABBIT) {
					field[old_pos.x][old_pos.y].rabbits.pop_back();

					field[pos.x][pos.y].grass->Death();
					field[pos.x][pos.y].grass = nullptr;
					field[pos.x][pos.y].rabbits.push_back(current_creature);
				}
				if (type == FOX) {
					field[old_pos.x][old_pos.y].foxes.pop_back();

					field[pos.x][pos.y].rabbits.back()->Death();
					field[pos.x][pos.y].rabbits.pop_back();
					field[pos.x][pos.y].foxes.push_back(current_creature);
				}
			}

			else if (act == DEATH) {
				Remove(current_creature);
			}

			if (act != DEATH) {
				creatures.push(current_creature);
			}

			Draw();

		}
		Draw();
	}

}

std::vector<std::vector<Creatures>> Park::GetSight(Coords pos, int FOV) const {
	std::vector<std::vector<Creatures>> sight(FOV * 2 + 1, std::vector<Creatures>(FOV * 2 + 1, BARRIER));

	size_t k = 0, l = 0;
	for (int i = (-1)*FOV; i < FOV + 1; ++i) {
		if (pos.x + i > HEIGHT - 1 || pos.x + i < 0) {
			l = 0;
			++k;
			continue;
		}
		for (int j = (-1)*FOV; j < FOV + 1; ++j) {
			if (pos.y + j > WIDTH - 1|| pos.y + j < 0) {
				++l;
				continue;
			}
			else {
				Tile tile = field[pos.x + i][pos.y + j];
				if (tile.foxes.size() > 0)
					sight[k][l] = FOX;
				else if (tile.rabbits.size() > 0)
					sight[k][l] = RABBIT;
				else if (tile.grass != nullptr)
					sight[k][l] = GRASS;
				else
					sight[k][l] = DIRT;
			}
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
			Tile tile = field[i][j];
			if (tile.foxes.size() > 0)
				std::cout << 'F';
			else if (tile.rabbits.size() > 0)
				std::cout << 'R';
			else if (tile.grass != nullptr)
				std::cout << (char)176;
			else
				std::cout << '.';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}
