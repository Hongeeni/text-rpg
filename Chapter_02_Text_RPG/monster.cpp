#include "monster.h"

Monster::Monster(string inputName, int inputExp, int inputHP, int inputPower, int inputDefence, string inputDropItemName, int inputDropItemPrice)
	: name(inputName), expReward(inputExp), maxHP(inputHP), currentHP(inputHP), power(inputPower), defence(inputDefence), dropItemName(inputDropItemName), dropItemPrice(inputDropItemPrice) {}

//setter
void Monster::setName(string newName) {
	this->name = newName;
}
void Monster::setExp(int newExp) {
	this->expReward = newExp;
}
void Monster::setMaxHP(int newMaxHP) {
	this->maxHP = newMaxHP;
}
void Monster::setCurrentHP(int newCurrentHP) {
	this->currentHP = newCurrentHP;
}
void Monster::setPower(int newPower) {
	this->power = newPower;
}
void Monster::setDefence(int newDefence) {
	this->defence = newDefence;
}
void Monster::setDropItemName(string newDropItemName) {
	this->dropItemName = newDropItemName;
}
void Monster::setDropItemPrice(int newDropItemPrice) {
	this->dropItemPrice = newDropItemPrice;
}

//getter
const string Monster::getName(void) {
	return name;
}
const int Monster::getExp(void) {
	return expReward;
}
const int Monster::getMaxHP(void) {
	return maxHP;
}
const int Monster::getCurrentHP(void) {
	return currentHP;
}
const int Monster::getPower(void) {
	return power;
}
const int Monster::getDefence(void) {
	return defence;
}
const string Monster::getDropItemName(void) {
	return dropItemName;
}
const int Monster::getDropItemPrice(void) {
	return dropItemPrice;
}

const void Monster::printMonsterCondition(void) {
	cout << this->getName() << " HP: " << this->getCurrentHP() << "/" << this->getMaxHP() << endl;
}

Monster::~Monster() {}