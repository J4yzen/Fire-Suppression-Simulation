#include "Water.h"
#include "World.h"

Water::Water(Cell& location): capacity(100) {
	location.setSymbol('W');
	location.setType("Water");
}

void Water::takeTurn(World& world) {
	if (capacity <= 0) {
		Die(); //Simple logic. If water reaches 0 set the object state to inactive through the Die() method.
	}
}

int Water::getCapacity() {

	return capacity;
}

void Water::setCapacity(int value) {

	capacity = value;

}

