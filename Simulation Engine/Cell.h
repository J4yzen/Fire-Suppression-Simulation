#pragma once
#include <iostream> 
using namespace std;
#include <string>
//#include "Actor.h"

class Cell
{
	
public:
	Cell();
	char getSymbol();
	void setSymbol(char sym);
	string getType();
	void setType(string typ);
	//char symbol = '.';
	//string type = "grass";
	//Actor* occupant;
	bool isOccupied();
	bool isBurnable();

private:
	char symbol = '.';
	string type = "grass";
	

};

