#include "Cell.h"

Cell::Cell() {
	char symbol = '.';
	string type = "grass";
	//types are grass, forest, ash, fire and water and firefighter


}

char Cell::getSymbol() {
	/*switch (type) {
		case ""
	} */
	return symbol;
}

string Cell::getType() {


	return type;
}

bool Cell::isOccupied() {

	if (symbol == 'W' || symbol == 'T' || symbol == 'F') {
		return true;
	}

	else {
		return false;
	}

}

bool Cell::isBurnable() {
	if (symbol == 'T' || '.') {
		return true;
	}
	else {
		return false;
	}
}

void Cell::setSymbol(char sym) {
	symbol = sym;
}

void Cell::setType(string typ) {
	type = typ;
}