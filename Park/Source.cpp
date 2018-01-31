#include "Park.h"

#include "Grass.h"
#include "Rabbit.h"
#include "Fox.h"

int main() {
	Park mypark;

	Rabbit* rab = new Rabbit({ 5, 5 });
	Rabbit* rab1 = new Rabbit({ 4, 4 });

	Grass* gra = new Grass({ 3, 7 });
	mypark.Add(rab);
	mypark.Add(rab1);
	mypark.Add(gra);

	mypark.Simulation();
}