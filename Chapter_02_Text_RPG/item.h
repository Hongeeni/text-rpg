#ifndef _ITEM_H_
#define _ITME_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>

using namespace std;

struct Item {
	string name = "Fragment of The Soul";
	int numOfItems = 0;
	int price = 5;

	const void printInfo(void);
};

#endif
