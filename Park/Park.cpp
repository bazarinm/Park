#include "Park.h"
#include "Grass.h"
#include "Rabbit.h"
#include "Fox.h"
#include <iostream>
#include <typeinfo>
#include <Windows.h>

Park::Park()
{
	for (std::size_t i = 0; i < HEIGHT; ++i)
		for (std::size_t j = 0; j < WIDTH; ++j)
			field[i][j] = { nullptr, nullptr, nullptr };
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
		field[pos.x][pos.y].rabbit = c;
	}
	else if (type == FOX) {
		field[pos.x][pos.y].fox = c;
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
		field[pos.x][pos.y].rabbit = nullptr;
	}
	else if (type == FOX) {
		field[pos.x][pos.y].fox = nullptr;
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

Tile Park::operator[](Coords pos) const {
	return field[pos.x][pos.y];
}

Tile& Park::operator[](Coords pos) {
	return field[pos.x][pos.y];
}

void Park::Move(Creature* c, Creatures type, Coords old_pos) {
	Coords pos = c->GetPos();

	if (pos != old_pos) {
		Creatures type = GetType(c);

		if (type == RABBIT) {
			field[old_pos.x][old_pos.y].rabbit = nullptr;

			field[pos.x][pos.y].rabbit = c;
		}
		if (type == FOX) {
			field[old_pos.x][old_pos.y].fox = nullptr;

			field[pos.x][pos.y].fox = c;
		}
	}
}

void Park::Eat(Creature* c, Creatures type) {
	Coords pos = c->GetPos();

	if (type == RABBIT) 
		field[pos.x][pos.y].grass = nullptr;
	else if (type == FOX) 
		field[pos.x][pos.y].rabbit = nullptr;
}

bool Park::isEaten(Creature* c, Creatures type) {
	Coords pos = c->GetPos();

	return ((type == GRASS && field[pos.x][pos.y].grass == nullptr) ||
			(type == RABBIT && field[pos.x][pos.y].rabbit == nullptr) ||
			(type == FOX && field[pos.x][pos.y].fox == nullptr));
}

void Park::Simulation() {
	Draw();

	while (!creatures.empty()) {
		std::size_t length = creatures.size();
		for (std::size_t i = 0; i < length; ++i) {
			Creature* current_creature = creatures.front(); creatures.pop();
			Coords old_pos = current_creature->GetPos();
			Creatures type = GetType(current_creature);

			Action act = current_creature->Behave();

			Move(current_creature, type, old_pos);

			if (!isEaten(current_creature, type)) {
				if (act == PROCREATE) {
					std::vector<Creature*> offsprings = current_creature->GetOffs();

					for (Creature* creature : offsprings) 
						Add(creature);
				}
				else if (act == EAT) 
					Eat(current_creature, type);
				else if (act == DEATH)
					Remove(current_creature);

				if (act != DEATH) {
					creatures.push(current_creature);
				}
			}

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
				if (tile.fox != nullptr)
					sight[k][l] = FOX;
				else if (tile.rabbit != nullptr)
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
		std::cout << std::endl;

		for (size_t j = 0; j < WIDTH; ++j) {
			Tile tile = field[i][j];
			if (tile.fox != nullptr)
				std::cout << 'F';
			else if (tile.rabbit != nullptr)
				std::cout << 'R';
			else if (tile.grass != nullptr)
				std::cout << (char)176;
			else
				std::cout << '.';
		}
	}
	Sleep(500);
	system("cls");
	//std::cout << std::endl << std::endl;
}
