#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
class Rabbit :
	public Animal
{
public:
	Rabbit(Coords pos);
	~Rabbit();

	Action Behave(const Park*) override;

	void Death() override;

private:
	int FOV;
	void Eat() override;
	void Idle() override;
	void Move(Coords) override;
	void Procreate() override;

	void See();

	Coords closest_grass;
	Coords closest_rabbit;
	Coords closest_fox;

	Coords up(Coords) const;
	Coords down(Coords) const;
	Coords left(Coords) const;
	Coords right(Coords) const;
};

#endif

