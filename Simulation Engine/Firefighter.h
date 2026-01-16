#pragma once
#include "Actor.h"
#include "Cell.h"


class Firefighter :
    public Actor
{
public:
    Firefighter(Cell& Location);
    void takeTurn(World& world) override;
    void moveToward(World& world, int TargetX, int TargetY);
    void setCapacity(int value);
    int getCapacity();
    int getMaxCapacity();

private:
    int speed = 1;
    int capacity = maxCapacity;
    int maxCapacity = 100;
};

