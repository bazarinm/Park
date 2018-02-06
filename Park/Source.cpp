#include "Park.h"

#include "Grass.h"
#include "Rabbit.h"
#include "Fox.h"
#include <iostream>

int main() {
	Park mypark;

	Creature* rab = new Rabbit({ 5, 5 }, mypark);
	Creature* rab1 = new Rabbit({ 6, 6 }, mypark);
	Creature* rab2 = new Rabbit({ 7, 4 }, mypark);

	//Creature* fox = new Fox({ 8, 6 }, mypark);
	//Creature* fox1 = new Fox({ 7, 4 }, mypark);

	Creature* gra = new Grass({ 3, 3 }, mypark);

	
	//Creature* rab3 = new Rabbit({ 25, 10 }, mypark);
	Creature* gra1 = new Grass({ 3, 1 }, mypark);
	//Creature* gra2 = new Grass({ 10, 10 }, mypark);
	mypark.Add(rab);
	mypark.Add(rab1);
	mypark.Add(gra);
	//mypark.Add(fox1);
	//mypark.Add(fox);
	mypark.Add(gra1);
	//mypark.Add(gra2);

	mypark.Add(rab2);
	//mypark.Add(rab3);

	mypark.Simulation();
}