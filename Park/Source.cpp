#include "Park.h"

#include "Grass.h"
#include "Rabbit.h"
#include "Fox.h"
#include <iostream>

int main() {
	Park mypark;

	Creature* rab = new Rabbit({ 31, 0 }, mypark);
	Creature* rab1 = new Rabbit({ 29, 2 }, mypark);

	Creature* gra = new Grass({ 28, 0 }, mypark);

	mypark.Add(rab);
	mypark.Add(rab1);
	mypark.Add(gra);

	mypark.Simulation();
}