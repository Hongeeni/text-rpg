#include "item.h"

//struct Item
const void Item::printInfo(void) {
	cout << this->name << " (" << this->price << "G)" << " x" << this->numOfItems << endl;
}