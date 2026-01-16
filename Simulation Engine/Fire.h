#pragma once
#include "Fire.h"
#include "Cell.h"
#include "Actor.h"

class Fire: public Actor
{
public:
	Fire(Cell& location);
	void takeTurn(World& world) override;
	int getFuel();
	void setFuel(int value);

private:
	int fuel;
	int intensity;
};

