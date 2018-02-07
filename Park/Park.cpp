#include "Park.h"
#include "Grass.h"
#include "Rabbit.h"
#include "Fox.h"
#include <iostream>
#include <random>
#include <Windows.h>

Coords randomize(int, int);

Park::Park()
{
	for (std::size_t i = 0; i < HEIGHT; ++i)
		for (std::size_t j = 0; j < WIDTH; ++j)
			field[i][j] = { nullptr, nullptr };

	for(int i = 0; i < 10; ++i)
		Add(generate(GRASS));

	for (int i = 0; i < 30; ++i) {
		Add(generate(RABBIT));
		//Add(generate(FOX));
	}

	for (int i = 0; i < 70; ++i) {
		//Add(generate(RABBIT));
		Add(generate(FOX));
	}
}

Coords randomize(int height, int width) {
	static std::random_device sd;
	static std::mt19937_64 gen(sd());
	static std::uniform_int_distribution<> h(0, height - 1);
	static std::uniform_int_distribution<> w(0, width - 1);

	return { h(gen), w(gen) };
}

Creature* Park::generate(Species s) {
	Creature* c = nullptr;
	switch (s) {
	case RABBIT: c = new Rabbit(*this, randomize(HEIGHT, WIDTH)); break;
	case FOX: c = new Fox(*this, randomize(HEIGHT, WIDTH)); break;
	case GRASS: c = new Grass(*this, randomize(HEIGHT, WIDTH)); break;
	}

	return c;
}

Park::~Park()
{
	while (!creatures.empty()) {
		delete creatures.front();
		creatures.pop();
	}
}

void Park::Add(Creature* c) {
	Coords pos = c->getPos();
	Genuses genus = c->getGenus();

	if (genus == PLANT
		&& field[pos.x][pos.y].plant == nullptr) {
		field[pos.x][pos.y].plant = c;
		creatures.push(c);
	}
	else 
	if (genus == ANIMAL
		&& field[pos.x][pos.y].animal == nullptr) {
		field[pos.x][pos.y].animal = c;
		creatures.push(c);
	}
	else 
		delete c;
}

void Park::Remove(Creature* c) {
	Coords pos = c->getPos();
	Genuses genus = c->getGenus();

	if (genus == PLANT)
		field[pos.x][pos.y].plant = nullptr;
	else if (genus == ANIMAL)
		field[pos.x][pos.y].animal = nullptr;

	delete c;
}

bool Park::inBound(Coords pos) const {
	return pos.x >= 0 && pos.x < HEIGHT && pos.y >= 0 && pos.y < WIDTH;
}

Park::Tile Park::operator[](Coords pos) const {
	return field[pos.x][pos.y];
}

Park::Tile& Park::operator[](Coords pos) {
	return field[pos.x][pos.y];
}

void Park::Move(Creature* c, Coords old_pos) {
	Coords pos = c->getPos();
	Genuses genus = c->getGenus();

	if (genus == ANIMAL && pos != old_pos) {
		field[old_pos.x][old_pos.y].animal = nullptr;
		field[pos.x][pos.y].animal = c;
	}
}

void Park::Eat(Creature* c) {
	Coords pos = c->getPos();
	Genuses genus = c->getGenus();

	if (genus == ANIMAL) {
		Species type = c->getSpecies();
		if (type == RABBIT) {
			//delete field[pos.x][pos.y].plant;
			field[pos.x][pos.y].plant = nullptr;
		}
		else if (type == FOX) {
			field[pos.x][pos.y].animal = nullptr;
		}

		field[pos.x][pos.y].animal = c;
	}
}

bool Park::isEaten(Creature* c) {
	Coords pos = c->getPos();
	Species type = c->getSpecies();

	return ((type == GRASS && field[pos.x][pos.y].plant == nullptr) ||
			(type == RABBIT && field[pos.x][pos.y].animal == nullptr) ||
			(type == FOX && field[pos.x][pos.y].animal == nullptr));
}

void Park::Simulation() {
	Draw();

	std::size_t cycle_count = 0;
	while (Rabbit::getCount() != 0 && Fox::getCount() != 0 && Grass::getCount() != 0) {
		std::size_t length = creatures.size();
		for (std::size_t i = 0; i < length; ++i) {
			Creature* current_creature = creatures.front(); creatures.pop();

			if (isEaten(current_creature)) {
				Remove(current_creature);
				continue;
			}

			Coords old_pos = current_creature->getPos();
			current_creature->behave();
			Action last_action = current_creature->getAction();

			Move(current_creature, old_pos);

			if (last_action == PROCREATE) {
				std::vector<Creature*> offsprings = current_creature->getOffsprings();
				for (Creature* creature : offsprings) 
					Add(creature);
			}
			else if (last_action == EAT)
				Eat(current_creature);
				
			if (last_action == DEATH)
				Remove(current_creature);
			else 
				creatures.push(current_creature);

			//Draw();
	
		}
		++cycle_count;
		Draw();
		std::cout << cycle_count << " cycles     " << std::endl;
	}
}

void Park::Draw() const {

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);

	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)0, (SHORT)0 };
	SetConsoleCursorPosition(hOut, coord);
	//Sleep(200);
	for (std::size_t i = 0; i < HEIGHT; ++i) {
		std::cout << std::endl;

		for (size_t j = 0; j < WIDTH; ++j) {
			Tile tile = field[i][j];
			if (tile.animal != nullptr) {
				Species type = tile.animal->getSpecies();
				if (type == RABBIT)
					std::cout << "R";
				else if (type == FOX)
					std::cout << "F";
			}
			else if (tile.plant != nullptr)
				std::cout << (char)176;
			else
				std::cout << ".";
		}
	}
	std::cout << std::endl << std::endl;
	std::cout << Rabbit::getCount() << " Rabbits       " << std::endl;
	std::cout << Fox::getCount() << " Foxes       " << std::endl;
	std::cout << Grass::getCount() << " Grass          " << std::endl;
}
