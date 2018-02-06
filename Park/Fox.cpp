#include "Fox.h"

Fox::Fox(Coords pos, const Park& territory) :
	Animal(8, pos, territory, 7, FOX)
{
	++fox_count;
}

size_t Fox::fox_count = 0;

Fox::~Fox() {
	death();
}

size_t Fox::getCount() {
	return fox_count;
}

//---

void Fox::behave() {
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

void Fox::idle() {
	--nutrients;
	last_action = IDLE;
}

bool Fox::move(Aim aim) {
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

	for (unsigned i = 0; i < MOVE_LENGTH; ++i) {
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

			if (isVacant(territory[next]) || (aim == FOOD && next == closest_food)) { // ?
				position = next;
				move = true;
			}
			else
				break; //an obstacle is blocking movement or position near partner has been reached
		}
		else
			break; //no route to follow
	}

	if (move) {
		--nutrients;
		last_action = MOVE;
	}
	return move;
}

bool Fox::procreate() {
	offsprings.clear(); // VERY IMPORTANT!!!!
	bool procreate = false;

	if ((closest_partner - position).length() > 1)
		move(PARTNER);

	if ((closest_partner - position).length() <= 1) { //near partner
		Coords spot = findSpot(position); //relative to territory
		if (spot.x != -1) { //!not found
			Fox* child = new Fox(spot, territory);
			offsprings.push_back(child);
			nutrients -= 1;
			procreate = true;
			last_action = PROCREATE;
		}
	}

	return procreate;
}

bool Fox::eat() {
	bool eat = false;

	if (!isFood(territory[position]))  //have not reached food
		move(FOOD); //go to food

	if (isFood(territory[position])) { //if reached food
		//position = closest_food;
		nutrients += 10;
		eat = true;
		last_action = EAT;
	}

	return eat;
}

void Fox::death() {
	if (!is_dead) {
		is_dead = true;
		--fox_count;
	}
	last_action = DEATH;
}

//---

bool Fox::isFood(Park::Tile tile) const {
	return tile.animal != nullptr && tile.animal->getSpecies() == RABBIT;
}

bool Fox::isPartner(Park::Tile tile) const {
	bool is_partner = false;
	if (tile.animal != nullptr) {
		const Animal* p = dynamic_cast<const Animal*>(tile.animal);
		//const Creature* p = tile.animal;
		//if (p != nullptr) 
		if (p->getSpecies() == species && p->isReady())
			is_partner = true;
	}
	return is_partner;
}

bool Fox::isEnemy(Park::Tile tile) const {
	return false; //foxes has no enemies!
}

//---

bool Fox::isHungry() const {
	return nutrients <= 4;
}

bool Fox::isReady() const {
	return age % PERIOD == 0 && age >= READY_AGE && !isHungry();
}

bool Fox::isScared() const {
	return (closest_enemy - position).length() <= 3;
}

bool Fox::isOld() const {
	return age > MAX_AGE;
}