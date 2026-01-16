#pragma once

class World; // Trying to fix the circular dependancy by removing includes World.h and declaring it as a forward declaration

class Actor
{
public:
	Actor();
	bool IsActive();
	void setCoordinates(int x, int y);
	int getXcoord();
	int getYcoord();
	virtual void takeTurn(World& world) = 0;
	virtual void Die();

private:
	int x, y ;
	bool active = true;
};

