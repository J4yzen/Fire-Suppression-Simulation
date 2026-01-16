#include "Fire.h"
#include "Cell.h"
#include "World.h"

Fire::Fire(Cell& location) {
	string cellType = location.getType();

	if (cellType == "grass" || cellType == "Fire") {
		fuel = 20;
		intensity = 1;
		location.setSymbol('F');
		location.setType("Fire");
	}
	else if (cellType == "Tree") {
		fuel = 40;
		intensity = 3;
		location.setSymbol('F');
		location.setType("Fire");
	}
	else {
		cout << "\nError: Tried burning " << cellType
			<< " at debug point" << endl;
	}
}

void Fire::takeTurn(World& world) { 

	cout << "DEBUG: Fire at (" << getXcoord() << "," << getYcoord() << ") fuel=" << fuel << endl;

	fuel--;

	if (fuel <= 0) {
		Die(); //Set Active to false. Will then let world handle cleaning up dead actors.
		cout << "DEBUG: Fire dying!" << endl;
		return;
	}
	int range = rand() % 100;
	int probability = 20 * intensity;

	int direction = rand() % 4;

	int newX = getXcoord();
	int newY = getYcoord();

	if (range < probability) {
		switch (direction) {
		case 0:
			//Fire newFire(world.grid[getYcoord()][getXcoord() + 1]); // Realised quite late that is a horrible idea that relies on grid being public
			newX++;
			world.trySpreadFire(newX, newY);
			break;														// and breaks encapsulation rules. I feel rather silly now.
		case 1:
			newX--;
			world.trySpreadFire(newX, newY);
			//Fire newFire(world.grid[getYcoord()][getXcoord() - 1]); // left 
			break;
		case 2:
			newY--;
			world.trySpreadFire(newX, newY);
			//Fire newFire(world.grid[getYcoord() + 1][getXcoord()]); // up
			break;
		case 3:
			newY++;
			world.trySpreadFire(newX, newY);
			//Fire newFire(world.grid[getYcoord() - 1][getXcoord()]); // down
			break;
		default:
			cout << "/n" << "Fire could not be spread unfortunately";
			break;
		}
			
	}
	}

void Fire::setFuel(int value) {

	fuel = value;

}

int Fire::getFuel() {

	return fuel;

}