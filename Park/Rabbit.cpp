#include "Rabbit.h"
#include "Park.h"

Rabbit::Rabbit(Coords pos, const Park& territory) : 
	Animal(3, pos, territory, RABBIT_FOV, RABBIT)
{
	++rabbit_count;
}

std::size_t Rabbit::rabbit_count = 0;

Rabbit::~Rabbit() {
	death();
}

std::size_t Rabbit::getCount() {
	return rabbit_count;
}

//---

void Rabbit::behave() {
	last_action = IDLE;

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


//bool Rabbit::move(Aim aim) {
//	bool move = false;
//
//	std::vector<Coords::Direction>* path;
//	if (aim == FOOD)
//		path = &route_to_food;
//	else if (aim == PARTNER)
//		path = &route_to_partner;
//	else if (aim == ENEMY)
//		path = &route_to_enemy;
//	else
//		return move;
//
//	for (unsigned i = 0; i < RABBIT_JUMP_LENGTH; ++i) {
//		if (!path->empty()) {
//			Coords::Direction step = path->back(); path->pop_back();
//
//			Coords next;
//			if (step == Coords::UP)
//				next = position.up();
//			else if (step == Coords::DOWN)
//				next = position.down();
//			else if (step == Coords::LEFT)
//				next = position.left();
//			else if (step == Coords::RIGHT)
//				next = position.right();
//
//			if (isVacant(territory[next])) {
//				position = next;
//				move = true;
//			}
//			else
//				break; //an obstacle is blocking movement or position near partner has been reached
//		}
//		else
//			break; //no route to follow
//	}
//
//	if (move) {
//		--nutrients;
//		last_action = MOVE;
//	}
//	return move;
//}


void Rabbit::idle() {
	--nutrients;
	last_action = IDLE;
}

bool Rabbit::move(Aim aim) {
	bool move = false;

	for (unsigned i = 0; i < RABBIT_JUMP_LENGTH; ++i) {
		if (!route.empty()) {
			Coords::Direction step = route.back(); route.pop_back();

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

bool Rabbit::procreate() {
	offsprings.clear(); // VERY IMPORTANT!!!!
	bool procreate = false;

	if (search(PARTNER)) {
		if (!inProximity(PARTNER))
			move(PARTNER);
		//else is not to be used, since periods would be out of sync otherwise
		if (inProximity(PARTNER)) { //near partner
			Coords spot = findSpot(position); //relative to territory
			if (spot.x != -1) { //!not found
				Rabbit* child = new Rabbit(spot, territory);
				offsprings.push_back(child);
				nutrients -= 2;
				procreate = true;
				last_action = PROCREATE;
			}
		}
	}

	return procreate;
}

bool Rabbit::eat() {
	bool eat = false;

	if (search(FOOD)) {
		if (!inProximity(FOOD))  //have not reached food
			move(FOOD); //go to food
		//else if is not recommended, rabbirs may starve
		if (inProximity(FOOD)) { //if reached food
			position = closest_aim;
			nutrients += 4;
			eat = true;
			last_action = EAT;
		}
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
	bool is_food = false;
	if (tile.animal == nullptr || tile.animal == this) //either no animal or itself standing on the tile
		is_food = tile.plant != nullptr && tile.plant->getSpecies() == GRASS;

	return is_food;
}

bool Rabbit::isPartner(Park::Tile tile) const {
	bool is_partner = false;
	if (tile.animal != nullptr && tile.animal != this) {
		const Creature* p = tile.animal;
		//const Animal* p = dynamic_cast<const Animal*>(tile.animal);
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
	bool is_ready = false;
	if (age == RABBIT_READY_AGE)
		is_ready = true;
	else if (age > RABBIT_READY_AGE && age % RABBIT_PERIOD == 0)
		is_ready = true;

	return is_ready;
}

bool Rabbit::isScared() const {
	//search(ENEMY);
	//return (closest_enemy - position).length() <= 3;
	return false; //temporary
}

bool Rabbit::isOld() const {
	return age > RABBIT_MAX_AGE;
}

bool Rabbit::inProximity(Aim aim) const {
	bool in_proximity = false;
	if (aim == FOOD)
		in_proximity = (closest_aim - position).length() == 0;
	else if (aim == PARTNER)
		in_proximity = (closest_aim - position).length() <= 1;

	return in_proximity;
}
