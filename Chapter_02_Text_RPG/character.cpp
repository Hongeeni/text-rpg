#include "character.h"

const bool compareByPrice(const Item& a, const Item& b) {
	return a.price < b.price;
}

Player::Player(const string name, const int stats[]) {
	this->name = name;
	this->currentHP = stats[0];	// currentHP
	this->currentMP = stats[1];	// currentMP
	this->stats[0] = stats[0];	// maxHP
	this->stats[1] = stats[1];	// maxMP
	this->stats[2] = stats[2];	// ATK
	this->stats[3] = stats[3];	// DEF

	this->inventory = new Inventory<Item>;
}

//setter
void Player::setName(string newName) {
	this->name = newName;
}
void Player::setJob(string newJob) {
	this->job = newJob;
}
void Player::setLv(int newLv) {
	this->level = newLv;
}
void Player::setCurrentHP(int newHP) {
	this->currentHP = newHP;
}
void Player::setCurrentMP(int newMP) {
	this->currentMP = newMP;
}
void Player::setDefAttackCost(int cost) {
	this->defAttackCost = cost;
}
void Player::setMaxHP(int newHP) {
	this->stats[0] = newHP;
}
void Player::setMaxMP(int newMP) {
	this->stats[1] = newMP;
}
void Player::setPower(int newPower) {
	this->stats[2] = newPower;
}
void Player::setDefence(int newDefence) {
	this->stats[3] = newDefence;
}

//getter
const string Player::getName(void) {
	return this->name;
}
const string Player::getJob(void) {
	return this->job;
}
const int Player::getLv(void) {
	return this->level;
}
const int Player::getCurrentHP(void) {
	return this->currentHP;
}
const int Player::getCurrentMP(void) {
	return this->currentMP;
}
const int Player::getDefAttackCost(void) {
	return this->defAttackCost;
}
const int Player::getMaxHP(void) {
	return this->stats[0];
}
const int Player::getMaxMP(void) {
	return this->stats[1];
}
const int Player::getPower(void) {
	return this->stats[2];
}
const int Player::getDefence(void) {
	return this->stats[3];
}

const void Player::printPlayerStatus(void) {
	cout << "===========================================" << endl;
	cout << "Name: " << this->name << " | Job: " << this->job << "\nLv." << this->level << " | Exp: " << this->exp << " / " << this->maxExp << endl;
	cout << "HP: " << this->currentHP << " / " << this->stats[0] << " | MP: " << this->currentMP << " / " << this->stats[1] << "\nAttack: " << this->stats[2] << " | Defence: " << this->stats[3] << endl;
	cout << "===========================================" << endl;

	cout << endl;
}
const void Player::printPlayerCondition(void) {
	cout << this->getName() << " HP: " << this->getCurrentHP() << "/" << this->getMaxHP() << " MP: " << this->getCurrentMP() << "/" << this->getMaxMP() << endl;
}

void Player::sortItems(void) {
	sort(this->inventory->pItems, this->inventory->pItems + this->inventory->getInventorySize(), compareByPrice);
}
void Player::useItem(void) {
	string userInput = "None";
	int inputItem = 0;

	do {
		this->sortItems();
		this->inventory->printInventory(this->getName());
		cout << "Choose Item Number: ";
		cin >> userInput;
		cout << endl;

		if (userInput > "0" && userInput <= "9") {
			inputItem = stoi(userInput) - 1;
		}
		else if (userInput == "10") {
			inputItem = 9;
		}
		else {
			cout << "Invalid input. Try again.\n" << endl;
			continue;
		}

		if (inputItem >= 0 && inputItem < this->inventory->getInventorySize()) {
			if (this->inventory->checkIndexItem(inputItem, "HP Potion")) {
				if (this->getCurrentHP() < this->getMaxHP()) {
					this->inventory->setInventoryItem("HP Potion", (this->inventory->getInventoryItem("HP Potion").numOfItems - 1));
					if ((this->getCurrentHP() + 20) < this->getMaxHP()) {
						this->setCurrentHP(this->getCurrentHP() + 20);
					}
					else {
						this->setCurrentHP(this->getMaxHP());
					}
					cout << "* HP increased by 20. (HP Potion used: " << this->inventory->getInventoryItem("HP Potion").numOfItems << " left)\n" << endl;
				}
				else {
					cout << "* Recovery is already complete.\n" << endl;
				}
			}
			else if (this->inventory->checkIndexItem(inputItem, "MP Potion")) {
				if (this->getCurrentMP() < this->getMaxMP()) {
					this->inventory->setInventoryItem("MP Potion", (this->inventory->getInventoryItem("MP Potion").numOfItems - 1));
					if ((this->getCurrentMP() + 20) < this->getMaxMP()) {
						this->setCurrentMP(this->getCurrentMP() + 20);
					}
					else {
						this->setCurrentMP(this->getMaxMP());
					}
					cout << "* MP increased by 20. (MP Potion used: " << this->inventory->getInventoryItem("MP Potion").numOfItems << " left)\n" << endl;
				}
				else {
					cout << "* Recovery is already complete.\n" << endl;
				}
			}
			else {
				cout << "That item is currently unavailable.\n" << endl;
				inputItem = 0;
			}
		}
		else {
			cout << "No items in that slot.\n" << endl;
			inputItem = 0;
		}
	} while (inputItem < 0 && inputItem >= 10);
}

void Player::gainExp(int expReward) {
	this->exp += expReward;

	if (this->exp >= this->maxExp) {
		cout << "	=> +" << expReward - (this->exp - this->maxExp) << " EXP! (EXP: " << this->maxExp << "/" << this->maxExp << ")\n\n	=> Level UP! (Lv." << this->level << " => Lv." << (this->level) + 1 << ")" << endl;
		cout << "	=> HP +" << this->stats[0] / 2 << ", MP +" << this->stats[1] / 2 << ", Attack +" << (this->stats[2]) / 4 << ", Defence +" << (this->stats[3]) / 4 << endl;

		for (int i = 0; i < 2; i++) {
			this->stats[i] += this->stats[i] / 4;
			this->stats[i + 2] += (this->stats[i + 2]) / 6;
		}
		this->currentHP = this->stats[0];
		this->currentMP = this->stats[1];
		this->exp = 0;
		this->maxExp = (maxExp * 4) / 3;
		this->level++;
	}
	else {
		cout << "	=> +" << expReward << " EXP! (EXP: " << this->exp << "/" << this->maxExp << ")" << endl;
	}
}