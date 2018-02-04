#include "Park.h"

#include "Grass.h"
#include "Rabbit.h"
#include "Fox.h"
#include <iostream>

int main() {
	Park mypark;

	Rabbit* rab = new Rabbit({ 5, 5 }, mypark);
	Rabbit* rab1 = new Rabbit({ 4, 4 }, mypark);

	Grass* gra = new Grass({ 3, 7 }, mypark);
	//Grass* gra1 = new Grass({ 3, 3 }, mypark);
	//Grass* gra2 = new Grass({ 2, 2 }, mypark);
	mypark.Add(rab);
	mypark.Add(rab1);
	mypark.Add(gra);
	//mypark.Add(gra1);
	//mypark.Add(gra2);



	mypark.Simulation();
}