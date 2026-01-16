#pragma once
#include "Actor.h"
#include "Cell.h"

class Water :
    public Actor
{
public: 
    Water(Cell& location);
    void takeTurn(World& world) override;
    int getCapacity();
    void setCapacity(int value);

private:
    int capacity = maxCapacity;
    int maxCapacity = 100;
};

