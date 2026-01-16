#pragma once
#include <vector>
#include "Cell.h"
#include <iostream>
#include "Firefighter.h"
#include "Fire.h"
#include "Water.h"

class Actor;

class World {
private:
    int width;
    int height; 

    //std::vector<Fire> fires;

public:
    std::vector<std::vector<Cell>> grid;
    vector<Actor*> liveActors;
    World(int w, int h);  // Constructor
    void initialiseGrid();
    void printGrid();
    void startRandomFires(int numOfFires);
    void addForest(int numOfTrees);
    void addWater(int numOfWater);
    void addFirefighters(int numOfFighters);
    bool trySpreadFire(int x, int y);
    void addActor(Actor* actor);
    Actor* findNearestFire(int startX, int startY);
    Actor* findNearestWater(int startX, int startY);
    void refillWater(Water& water, Firefighter& fighter);
    void extinguishFire(Fire& fire, Firefighter& fighter);
    int getWidth();
    int getHeight();
    int currentTurn = 0;
    void cleanupDeadActors();
    void update();
    int getCurrentTurn();
};