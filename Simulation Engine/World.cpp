#include "World.h"
using namespace std;
#include <vector>
#include "Cell.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <algorithm> // For random_shuffle (C++14) or shuffle (C++17)
#include "Fire.h"
#include "Water.h"
#include "Actor.h"
#include "Firefighter.h"
#include <climits>

/*
World::World() {
	width = 0;
	height = 0;
}

World::World(int w, int h) : width(w), height(h) {

}
int World::GetDimensions() {

	cout << "What width dimension would you like for the world?";
		cin >> width;
	cout << "What heigth dimension would you like for the world?!";
		cin >> height;

	return width, height;
}

void World::intialiseGrid() {
	vector<vector<Cell()>> grid;
	grid.resize(height); // creates an empty vector of 'height' amount of objects

	for (int y = 0; y < height; y++) {
	grid[y].resize(width); // for each element of said vector (another vector), change the size of it to width. This is how you have a width and height 2-d grid that I can visualise on the console.
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cout << grid[y][x].symbol;
		}
	}
}

*////

/*World::World(int w, int h)
	: width(w), height(h) {  // Initialize members FIRST
	initialiseGrid();  // THEN call initializeGrid
}

void World::initialiseGrid() {
	// Now width and height have valid values
	grid.resize(height);

	for (int y = 0; y < height; y++) {
		grid[y].resize(width);

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				cout << grid[y][x].symbol;
			}
		}
	}
}*/

#pragma once
#include <vector>
#include "Cell.h"
#include "World.h"
#include <iostream>
using namespace std;

World::World(int w, int h)
	: width(w), height(h) {
	srand(static_cast<unsigned int>(time(0)));
	initialiseGrid();
}

void World::initialiseGrid() {
	// Create the grid structure
	grid.resize(height);

	for (int y = 0; y < height; y++) {
		grid[y].resize(width);
	}

	cout << "Grid initialized: " << width << "x" << height << endl;
	printGrid();

	// REMOVE the printing from here - create a separate print function
	// The double loop was wrong here
}

void World::printGrid() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cout << grid[y][x].getSymbol() << " ";
		}
		cout << endl;
	}
}

void World::startRandomFires(int numOfFires) {

		int x;
		int y;
		int firesCreated = 0;

		
		while (firesCreated < numOfFires) {
			x = rand() % width;
			y = rand() % height;
			if (!grid[y][x].isOccupied()) {
				//Fire newFire(grid[y][x]);
				Fire* newFire = new Fire(grid[y][x]); //Swtiched from creating objects to storing them as pointers to facilitate polymorphism later on
				newFire->setCoordinates(x, y);
				cout << "Coordinates successfully set at: " << y << x;
				firesCreated++;
				addActor(newFire);
			}
		}
}

void World::addForest(int numOfTrees) {

	int x;
	int y;
	int treesCreated = 0;

	while (treesCreated < numOfTrees) {
		x = rand() % width;
		y = rand() % height;
		if (!grid[y][x].isOccupied()) {
			grid[y][x].setSymbol('T');
			grid[y][x].setType("Tree");
			treesCreated++;
		}
	}
	



}

void World::addWater(int numOfWater) {

	int x;
	int y;
	int waterCreated = 0;

	while(waterCreated < numOfWater) {
		x = rand() % width;
		y = rand() % height;
		if (!grid[y][x].isOccupied()) {
			Water* newWater = new Water(grid[y][x]);
			newWater->setCoordinates(x, y);
			waterCreated++;
			addActor(newWater);
		}

	}


}

void World::addFirefighters(int numOfFighters) {

	int x;
	int y;

	int fightersCreated = 0;

	while (fightersCreated < numOfFighters) {
		x = rand() % width;
		y = rand() % height;
		if (!grid[y][x].isOccupied()) {
			Firefighter* fighter = new Firefighter(grid[y][x]);
			fighter->setCoordinates(x, y);
			fightersCreated++;
			addActor(fighter);
		}

	}

}

/*bool World::trySpreadFire(int x, int y) {

	if (x < 0 || x > width || y <  0 || y > height) {
		return false;									//Checks the bounds of the grid to see if a fire can start in that direction.
	}

	if (grid[y][x].isBurnable()) { //Check if the cell attempting to be burnt is burnable.
		Fire* newFire = new Fire(grid[y][x]);
		newFire->setCoordinates(x, y);
		addActor(newFire);
		return true;
	}
	else { return false; }
	
}*/

bool World::trySpreadFire(int x, int y) {
	// FIXED: Use >= instead of >
	if (x < 0 || x >= width || y < 0 || y >= height) {
		cout << "DEBUG: trySpreadFire out of bounds: (" << x << "," << y
			<< ") grid is " << width << "x" << height << endl;
		return false;
	}

	if (grid[y][x].isBurnable() && !grid[y][x].isOccupied()) { // Added occupancy check
		Fire* newFire = new Fire(grid[y][x]);
		newFire->setCoordinates(x, y);
		addActor(newFire);

		// Update grid symbol
		grid[y][x].setSymbol('F');
		grid[y][x].setType("Fire");

		cout << "Fire spread to (" << x << "," << y << ")\n";
		return true;
	}
	else {
		return false;
	}
}

void World::addActor(Actor* actor) {

	liveActors.push_back(actor);
}

Actor* World::findNearestFire(int startX, int startY) {
	//Iterate through list of liveActors, try dynamic typecasting to get each x and y coors. Check manhattan distance between start points and new points. Smallest distance gets its actor returned.
	
	Actor* nearest = nullptr;
	int minDistance = INT_MAX;
	
	for (Actor* actor : liveActors) {
		Fire* fire = dynamic_cast<Fire*>(actor);
		if (fire != nullptr && fire->IsActive()) {

			int distance = abs(fire->getXcoord() - startX) + abs(fire->getYcoord() - startY);
		
			if (distance < minDistance) {
				minDistance = distance;
				nearest = actor;
			}
		}

	}

	return nearest;

}

Actor* World::findNearestWater(int startX, int startY) {
	//Iterate through list of liveActors, try dynamic typecasting to get each x and y coors. Check manhattan distance between start points and new points. Smallest distance gets its actor returned.

	Actor* nearest = nullptr;
	int minDistance = INT_MAX;

	for (Actor* actor : liveActors) {
		Water* water = dynamic_cast<Water*>(actor);
		if (water != nullptr && water->IsActive()) {

			int distance = abs(water->getXcoord() - startX) + abs(water->getYcoord() - startY);

			if (distance < minDistance) {
				minDistance = distance;
				nearest = actor;
			}
		}

	}

	return nearest;

}

int World::getHeight() {

	return height;
}

int World::getWidth() {

	return width;
}

void World::refillWater(Water& water, Firefighter& fighter) {
	
	int currentWater = water.getCapacity(); //Water left in the water pool
	int waterNeeded = fighter.getMaxCapacity() - fighter.getCapacity(); //Water the firefighter needs to refill to max
	int currentFirefighterWater = fighter.getCapacity();

	if (waterNeeded <= currentWater) {

		fighter.setCapacity(currentFirefighterWater + waterNeeded); //increase the firefighter's water by the water needed
		water.setCapacity(currentWater - waterNeeded); //reduce the water pool's water by the water needed by the firefighter
	}

	else {  //

		fighter.setCapacity(currentWater + water.getCapacity()); //increase the firefighter's water by the water left in the pool
		water.setCapacity(0); //reduce water to 0 which in turn makes it inactive
	}



	/*

	int waterX = water.getXcoord();
	int waterY = water.getYcoord();

	cout << "Looking for firefighter at water location ("
		<< waterX << "," << waterY << ")\n";

	// Find any firefighter at the water location
	for (Actor* actor : liveActors) {
		Firefighter* fighter = dynamic_cast<Firefighter*>(actor);
		if (fighter) {
			cout << "Found firefighter at (" << fighter->getXcoord()
				<< "," << fighter->getYcoord() << ")\n";

			if (fighter->getXcoord() == waterX &&
				fighter->getYcoord() == waterY) {

				fighter->setCapacity(fighter->getMaxCapacity());
				cout << "SUCCESS: Firefighter refilled to "
					<< fighter->getCapacity() << " units\n";
				return;
			}
		}
	}

	cout << "ERROR: No firefighter at water location to refill!\n"; */
}

void World::extinguishFire(Fire& fire, Firefighter& fighter) {
	// 1. Use water from firefighter
	fighter.setCapacity(fighter.getCapacity() - 20);

	// 2. Reduce fire's fuel
	int currentFuel = fire.getFuel();
	fire.setFuel(currentFuel - 20);

	cout << "Firefighter used 20 water units. Remaining: "
		<< fighter.getCapacity() << "\n";
	cout << "Fire fuel reduced from " << currentFuel
		<< " to " << fire.getFuel() << "\n";

	// 3. Check if fire is extinguished
	if (fire.getFuel() <= 0) {
		cout << "Fire at (" << fire.getXcoord() << ","
			<< fire.getYcoord() << ") has been extinguished!\n";

		// Remove fire from the grid
		grid[fire.getYcoord()][fire.getXcoord()].setSymbol('.');
		grid[fire.getYcoord()][fire.getXcoord()].setType("Empty");

		// Mark fire as inactive
		fire.Die();

		// Optional: Remove from liveActors
		// You'd need to add cleanup logic elsewhere
	}
}

void World::cleanupDeadActors() {
	// First, clear dead actors from the grid
	for (Actor* actor : liveActors) {
		if (actor && !actor->IsActive()) {
			int x = actor->getXcoord();
			int y = actor->getYcoord();

			// Clear the cell on the grid
			if (x >= 0 && x < width && y >= 0 && y < height) {
				grid[y][x].setSymbol('.');
				grid[y][x].setType("Empty");
			}
		}
	}

	// Now remove dead actors from the vector and delete them
	vector<Actor*> stillAlive;

	for (Actor* actor : liveActors) {
		if (actor && actor->IsActive()) {
			stillAlive.push_back(actor);  // Keep active actors
		}
		else if (actor) {
			delete actor;  // Free memory of dead actors
			actor = nullptr;
		}
	}

	// Replace the old vector with the cleaned one
	liveActors = stillAlive;

	// Optional debug output
	// cout << "Cleaned up dead actors. Remaining: " << liveActors.size() << endl;
}

void World::update() {
	currentTurn++;
	cout << "\n=== TURN " << currentTurn << " ===" << endl;

	// 1. Process all active actors (use a copy to avoid iteration issues)
	vector<Actor*> currentActors = liveActors;

	for (Actor* actor : currentActors) {
		if (actor && actor->IsActive()) {
			actor->takeTurn(*this);
		}
	}

	// 2. Clean up dead actors (including grid cleanup)
	cleanupDeadActors();

	// Optional: Add fire spread or other world events here
}

int World::getCurrentTurn() {

	return currentTurn;

}