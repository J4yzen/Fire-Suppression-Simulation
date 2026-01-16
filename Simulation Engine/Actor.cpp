#include "Actor.h"
#include "World.h"
Actor::Actor() {


}

int Actor::getXcoord() {

	return x;
}

int Actor::getYcoord() {

	return y;
}


void Actor::setCoordinates(int xcoord, int ycoord) {

	x = xcoord;
	y = ycoord;
}

bool Actor::IsActive() {

	return active;

}

void Actor::Die() {

	active = false;
}
//Actor::takeTurn() {

//}