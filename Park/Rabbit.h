#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
class Rabbit :
	public Animal
{
public:
	Rabbit(Coords pos, const Park& territory);
	~Rabbit();

	Action Behave() override;

	void Death() override;

private:
	//int FOV;
	bool eat() override;
	void Idle() override;
	bool move(Coords) override;
	bool Procreate() override;

	//void See();

	//Coords closest_grass;
	//Coords closest_rabbit;
	//Coords closest_fox;

	//Coords up(Coords) const;
	//Coords down(Coords) const;
	//Coords left(Coords) const;
	//Coords right(Coords) const;
};

#endif

