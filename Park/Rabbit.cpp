#include "Rabbit.h"
#include "Park.h"

Rabbit::Rabbit(Coords pos, const Park& territory) : 
	Animal(6, pos, territory, 5, RABBIT)
{
	++rabbit_count;
}

size_t Rabbit::rabbit_count = 0;

Rabbit::~Rabbit() {
	death();
}

size_t Rabbit::getCount() {
	return rabbit_count;
}

//---

void Rabbit::behave() {
	last_action = IDLE;
	scan();

	if (nutrients == 0 || isOld())
		death();
	else if (isHungry()) //hungry and found food nearby
		eat();
	else if (isReady()) //ready and found partner nearby
		procreate();
	else
		idle();

	++age;
}

//---

void Rabbit::idle() {
	--nutrients;
	last_action = IDLE;
}

bool Rabbit::move(Aim aim) {
	bool move = false;

	std::vector<Coords::Direction>* path;
	if (aim == FOOD)
		path = &route_to_food;
	else if (aim == PARTNER)
		path = &route_to_partner;
	else if (aim == ENEMY)
		path = &route_to_enemy;
	else
		return move;

	for (unsigned i = 0; i < JUMP_LENGTH; ++i) {
		if (!path->empty()) {
			Coords::Direction step = path->back(); path->pop_back();

			Coords next;
			if (step == Coords::UP)
				next = position.up();
			else if (step == Coords::DOWN)
				next = position.down();
			else if (step == Coords::LEFT)
				next = position.left();
			else if (step == Coords::RIGHT)
				next = position.right();

			if (isVacant(territory[next])) {
				position = next;
				--nutrients;
				last_action = MOVE;
				move = true;
			}
			else
				break; //an obstacle is blocking movement or position near partner has been reached
		}
		else
			break; //no route to follow
	}

	return move;
}

bool Rabbit::procreate() {
	offsprings.clear(); // VERY IMPORTANT!!!!
	bool procreate = false;
	
	if ((closest_partner - position).length() < 2) { //near partner
		Coords spot = findSpot(position); //relative to territory
		if (spot.x != -1) { //!not found
			Rabbit* child = new Rabbit(spot, territory);
			offsprings.push_back(child);
			nutrients -= 2;
			procreate = true;
			last_action = PROCREATE;
		}
	}
	else
		move(PARTNER); //go to partner

	return procreate;
}

bool Rabbit::eat() {
	bool eat = false;

	if (!isFood(territory[position]))  //have not reached food
		move(FOOD); //go to food
	
	if (isFood(territory[position])) { //if reached food
		nutrients += 4;
		eat = true;
		last_action = EAT;
	}

	return eat;
}

void Rabbit::death() {
	if (!is_dead) { 
		is_dead = true;
		--rabbit_count;
	}
	last_action = DEATH;
}

//---

bool Rabbit::isFood(Park::Tile tile) const {
	return tile.plant != nullptr && tile.plant->getSpecies() == GRASS;
}

bool Rabbit::isPartner(Park::Tile tile) const {
	bool is_partner = false;
	if (tile.animal != nullptr) {
		const Animal* p = static_cast<const Animal*>(tile.animal);
		//const Creature* p = tile.animal;
		//if (p != nullptr) 
			if (p->getSpecies() == species && p->isReady())
				is_partner = true;
	}
	return is_partner;
}

bool Rabbit::isEnemy(Park::Tile tile) const {
	return tile.animal != nullptr && tile.animal->getSpecies() == FOX;
}

//---

bool Rabbit::isHungry() const {
	return nutrients <= 3;
}

bool Rabbit::isReady() const {
	return age % PERIOD == 0 && age >= READY_AGE && !isHungry();
}

bool Rabbit::isScared() const {
	return (closest_enemy - position).length() <= 3;
}

bool Rabbit::isOld() const {
	return age > MAX_AGE;
}
