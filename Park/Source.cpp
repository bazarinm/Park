#include "Park.h"

#include "Grass.h"
#include "Rabbit.h"
#include "Fox.h"
#include <iostream>

int main() {
	Park mypark;

	Creature* rab = new Rabbit({ 5, 5 }, mypark);
	Creature* rab1 = new Rabbit({ 6, 6 }, mypark);

	Creature* gra = new Grass({ 3, 3 }, mypark);

	mypark.Add(rab);
	mypark.Add(rab1);
	mypark.Add(gra);

	mypark.Simulation();
}