#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "monster.h"

template <typename T>
class Inventory {
protected:
	int capacity = 5;		//Inventory capacity.
	int inventorySize = 0;	//Maximum index in use.

public:
	T* pItems = nullptr;
	Item* temp = nullptr;

	Inventory(void) {
		this->pItems = new T[this->capacity];
		addPotions();
	}

	//setter
	void setCapacity(int newCapacity) {
		this->capacity = newCapacity;
	}

	//getter
	const int getCapacity(void) {
		return this->capacity;
	}
	const int getInventorySize(void) {
		return this->inventorySize;
	}

	//functional
	void resizeInventory(int newCapacity) {
		T* pTemp = this->pItems;
		this->pItems = nullptr;
		this->capacity = newCapacity;
		this->pItems = new T[this->capacity];
		for (int i = 0; i < this->inventorySize; i++) {
			pItems[i] = pTemp[i];
		}
		delete[] pTemp;
		cout << "	=> Inventory expanded!\n	=> Inventory Capacity: " << this->capacity << endl;
	}

	void addInventoryItem(T item) {
		if (this->inventorySize < this->capacity) {
			this->pItems[this->inventorySize] = item;
			this->inventorySize += 1;
		}
	}
	void removeInventoryItem(T* item) {
		int destroyIndex = this->inventorySize;
		for (int i = 0; i < this->inventorySize; i++) {
			if (&(this->pItems[i]) == item) {
				destroyIndex = i;
				break;
			}
		}
		if (destroyIndex != this->inventorySize) {
			for (int i = destroyIndex; i < this->inventorySize - 1; i++) {
				this->pItems[i] = this->pItems[i + 1];
			}
			this->inventorySize--;
		}
		else {
			cout << "* Couldn't find the item to delete.\nProceed with the game without organizing inventory.\n" << endl;
		}
	}
	void setInventoryItem(T item, int setNumOfItem) {
		bool isItem = false;
		Item acquiredItem = item;
		for (int i = 0; i < this->inventorySize; i++) {
			this->temp = &(this->pItems[i]);
			if (this->temp->name == acquiredItem.name) {
				this->temp->numOfItems = setNumOfItem;
				isItem = true;
				break;
			}
		}
		this->temp = nullptr;
		if (!isItem && setNumOfItem > 0) {
			this->addInventoryItem(item);
		}
	}
	void setInventoryItem(string itemName, int setNumOfItem, int setPrice) {
		bool isItem = false;
		for (int i = 0; i < this->inventorySize; i++) {
			this->temp = &(this->pItems[i]);
			if (this->temp->name == itemName) {
				this->temp->numOfItems = setNumOfItem;
				isItem = true;
				break;
			}
		}
		this->temp = nullptr;
		if (!isItem && setNumOfItem > 0) {
			Item item = { itemName, 1, setPrice };
			this->addInventoryItem(item);
		}
	}

	const bool checkIndexItem(int itemIndex, string itemName) {
		this->temp = &(this->pItems[itemIndex]);
		if (this->temp->name == itemName) {
			this->temp = nullptr;
			return true;
		}
		else {
			this->temp = nullptr;
			return false;
		}
		this->temp = nullptr;
		return false;
	}
	const T getInventoryItem(string itemName) {
		for (int i = 0; i < this->inventorySize; i++) {
			this->temp = &(this->pItems[i]);
			if (this->temp->name == itemName) {
				this->temp = nullptr;
				return this->pItems[i];
			}
		}
		this->temp = nullptr;
		Item nullItem;
		return nullItem;
	}
	const void printInventory(string playerName) {
		for (int i = 0; i < this->inventorySize; i++) {
			this->temp = &(this->pItems[i]);
			if (this->temp->numOfItems == 0) {
				this->removeInventoryItem(this->temp);
			}
		}
		cout << "===========================================\n	[ " << playerName << "'s Inventory " << this->inventorySize << "/" << this->capacity << " ]\n===========================================" << endl;
		for (int i = 0; i < this->inventorySize; i++) {
			this->temp = &(this->pItems[i]);
			cout << (i + 1) << ". ";
			this->temp->printInfo();
		}
		cout << "===========================================\n" << endl;

		this->temp = nullptr;
	}

	void addPotions(int defaultPotions = 5) {
		Item hpPotion = { "HP Potion", defaultPotions, 50 };
		Item mpPotion = { "MP Potion", defaultPotions, 50 };
		this->addInventoryItem(hpPotion);
		this->addInventoryItem(mpPotion);
	}

	~Inventory() {
		delete[] pItems;
		cout << "Inventory destroy successful." << endl;
	}
};

#endif
