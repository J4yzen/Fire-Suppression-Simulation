#include "Firefighter.h"
#include "World.h"

Firefighter::Firefighter(Cell& location) : capacity(40) {
    location.setSymbol('U');
    location.setType("Firefighter");
}

void Firefighter::takeTurn(World& world) {
    int currentX = getXcoord();
    int currentY = getYcoord();

    cout << "Firefighter at (" << currentX << "," << currentY
        << ") water: " << capacity << "/" << maxCapacity << endl;

    // 1. Check water - if low, go refill
    if (capacity < 30) {
        Actor* waterActor = world.findNearestWater(currentX, currentY);
        if (waterActor) {
            Water* water = dynamic_cast<Water*>(waterActor);

            if (water) {
                moveToward(world, water->getXcoord(), water->getYcoord());

                // Check if reached water
                if (getXcoord() == water->getXcoord() && getYcoord() == water->getYcoord()) {
                    world.refillWater(*water, *this);
                    cout << "Refilled water! Now at: " << capacity << "/" << maxCapacity << "\n";
                }
            }
            else {
                cout << "Error: Nearest water is not a Water object!\n";
            }
            return;
        }
        else {
            cout << "No water sources found!\n";
        }
    }

    // 2. Find and fight fire
    Actor* fireActor = world.findNearestFire(currentX, currentY);
    if (fireActor) {
        int fireX = fireActor->getXcoord();
        int fireY = fireActor->getYcoord();

        cout << "Targeting fire at (" << fireX << "," << fireY << ")\n";

        // Check if adjacent to fire (including diagonals)
        bool isAdjacent = (abs(currentX - fireX) <= 1 && abs(currentY - fireY) <= 1);

        if (isAdjacent) {
            // Try to cast to Fire*
            Fire* fire = dynamic_cast<Fire*>(fireActor);

            if (fire && fire->IsActive()) {
                // Check if we have enough water
                if (capacity >= 20) {
                    cout << "Extinguishing fire at (" << fireX << "," << fireY << ")!\n";

                    // Use water
                    capacity -= 20;

                    // Reduce fire's fuel
                    int currentFuel = fire->getFuel();
                    fire->setFuel(currentFuel - 20);

                    cout << "Used 20 water. Remaining: " << capacity
                        << ". Fire fuel: " << fire->getFuel() << "/100\n";

                    // Check if fire is extinguished
                    if (fire->getFuel() <= 0) {
                        cout << "Fire at (" << fireX << "," << fireY << ") EXTINGUISHED!\n";

                        // Mark fire as dead
                        fire->Die();

                        // Clear the grid cell
                        world.grid[fireY][fireX].setSymbol('.');
                        world.grid[fireY][fireX].setType("Empty");
                    }
                }
                else {
                    cout << "Not enough water to fight! Need refill.\n";
                }
            }
        }
        else {
            // Move toward fire
            moveToward(world, fireX, fireY);
        }
    }
    else {
        cout << "No fires to fight!\n";
        // Optional: Add idle behavior here
    }
}

void Firefighter::moveToward(World& world, int targetX, int targetY) {
    int currentX = getXcoord();
    int currentY = getYcoord();

    cout << "Moving from (" << currentX << "," << currentY
        << ") toward (" << targetX << "," << targetY << ")\n";

    // Simple movement: move 1 step toward target
    int newX = currentX;
    int newY = currentY;

    if (targetX > currentX) newX++;
    else if (targetX < currentX) newX--;
    else if (targetY > currentY) newY++;
    else if (targetY < currentY) newY--;

    // Check bounds
    if (newX >= 0 && newX < world.getWidth() &&
        newY >= 0 && newY < world.getHeight()) {

        // Clear old position on grid
        world.grid[currentY][currentX].setSymbol('.');
        world.grid[currentY][currentX].setType("Empty");

        // Set new position on grid
        world.grid[newY][newX].setSymbol('U');
        world.grid[newY][newX].setType("Firefighter");

        // Update actor coordinates
        setCoordinates(newX, newY);

        cout << "MOVED to (" << newX << "," << newY << ")\n";
    }
    else {
        cout << "Cannot move - out of bounds\n";
    }
}

int Firefighter::getCapacity() {
    return capacity;
}

int Firefighter::getMaxCapacity() {
    return maxCapacity;
}

void Firefighter::setCapacity(int value) {
    capacity = value;
    // Ensure capacity doesn't exceed max
    if (capacity > maxCapacity) {
        capacity = maxCapacity;
    }
    // Ensure capacity doesn't go below 0
    if (capacity < 0) {
        capacity = 0;
    }
}