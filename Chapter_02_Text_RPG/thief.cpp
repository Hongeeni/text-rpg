#include "thief.h"

Thief::Thief(const string name, const int stats[]) : Player(name, stats) {
	cout << "* You became a Rogue! (Attack +30)" << endl;
	this->job = "Rogue";
	this->stats[2] += 30;
}

void Thief::setSpecialAttackCost(int cost) {
	this->specialAttackCost = cost;
}
const int Thief::getSpecialAttackCost(void) {
	return this->specialAttackCost;
}

void Thief::getPumped(void) {
	cout << "* Stabs dagger!" << endl;
}

void Thief::attack(Monster* monster) {
	bool isPlayerTurn = rand() % 2;

	string userInput = "None";
	int inputMenu = 0;
	int tempHP = 0;

	system("cls");
	do {
		cout << "===========================================" << endl;
		cout << "[ Battle! ] " << this->getName() << "(" << this->getJob() << ") VS " << monster->getName() << endl;
		cout << endl;
		this->printPlayerCondition();
		monster->printMonsterCondition();
		cout << "===========================================\n" << endl;
		if (isPlayerTurn) {
			int randomNum = (rand() % 2);
			int playerATK = (this->getPower() - monster->getDefence());
			cout << "-------------- Player's Turn --------------" << endl;
			cout << "1. Attack the monster\n2. Hide and attack from behind.\n3. Use item." << endl;
			cout << "-------------------------------------------" << endl;
			cout << "Choose: ";
			cin >> userInput;
			system("cls");
			if (userInput > "0" && userInput < "4") {
				inputMenu = stoi(userInput);
			}
			else {
				do {
					cout << "===========================================" << endl;
					cout << "[ Battle! ] " << this->getName() << "(" << this->getJob() << ") VS " << monster->getName() << endl;
					cout << endl;
					this->printPlayerCondition();
					monster->printMonsterCondition();
					cout << "===========================================\n" << endl;
					cout << "-------------- Player's Turn --------------" << endl;
					cout << "1. Attack the monster\n2. Hide and attack from behind.\n3. Use item." << endl;
					cout << "-------------------------------------------" << endl;
					cout << "Invalid input. Try again.\n\nChoose: ";
					cin >> userInput;
					system("cls");
				} while (userInput < "1" || userInput > "3");
				inputMenu = stoi(userInput);
			}
			cout << "===========================================" << endl;
			cout << "[ Battle! ] " << this->getName() << "(" << this->getJob() << ") VS " << monster->getName() << endl;
			cout << endl;
			this->printPlayerCondition();
			monster->printMonsterCondition();
			cout << "===========================================\n" << endl;
			switch (inputMenu) {
			case 1:
				if (playerATK < 2) {
					playerATK = 1;
				}
				cout << "-------------- Player's Turn --------------" << endl;
				this->getPumped();
				cout << playerATK << " damage to " << monster->getName() << " !" << endl;
				tempHP = monster->getCurrentHP();
				monster->setCurrentHP(monster->getCurrentHP() - playerATK);
				this->setCurrentMP(this->getCurrentMP() - this->getDefAttackCost());
				if (monster->getCurrentHP() > 0) {
					cout << monster->getName() << " HP: " << tempHP << " => " << monster->getCurrentHP() << endl;
				}
				else {
					Item item = { monster->getDropItemName(), 1, monster->getDropItemPrice() };

					cout << monster->getName() << " HP: " << tempHP << " => " << monster->getCurrentHP() << " (Dead)\n" << endl;
					cout << "* Victory!" << endl;
					this->gainExp(monster->getExp());
					cout << "\n	=> Got: " << item.name << "!" << endl;

					if (this->inventory->getInventorySize() < this->inventory->getCapacity()) {
						this->inventory->setInventoryItem(item, (this->inventory->getInventoryItem(item.name).numOfItems + 1));
						cout << "	=> Saved to inventory." << endl;
					}
					else {
						cout << "	=> Inventory is full.\n	=> Expanding the inventory.\n" << endl;
						this->inventory->resizeInventory(this->inventory->getCapacity() + 5);
						this->inventory->setInventoryItem(item, (this->inventory->getInventoryItem(item.name).numOfItems + 1));
						cout << "	=> Saved to inventory." << endl;
					}
				}
				isPlayerTurn = !isPlayerTurn;
				break;
			case 2:
				if (playerATK < 2) {
					playerATK = 1;
				}
				cout << "* Disappeared into the bushes.\n" << endl;
				this->setCurrentMP(this->getCurrentMP() - this->getSpecialAttackCost());
				if (randomNum) {
					cout << "-------------- Monster's Turn --------------" << endl;
					cout << "The " << monster->getName() << " didn't find you.\n" << endl;
					cout << "* Attack successful!" << endl;
					cout << "-------------- Player's Turn --------------" << endl;
					this->getPumped();
					cout << (playerATK * 3) / 2 << " damage to " << monster->getName() << " !" << endl;

					tempHP = monster->getCurrentHP();
					monster->setCurrentHP(monster->getCurrentHP() - ((playerATK * 3) / 2));

					if (monster->getCurrentHP() > 0) {
						cout << monster->getName() << " HP: " << tempHP << " => " << monster->getCurrentHP() << endl;
					}
					else {
						Item item = { monster->getDropItemName(), 1, monster->getDropItemPrice() };

						cout << monster->getName() << " HP: " << tempHP << " => " << monster->getCurrentHP() << " (Dead)\n" << endl;
						cout << "* Victory!" << endl;
						this->gainExp(monster->getExp());
						cout << "\n	=> Got: " << item.name << "!" << endl;

						if (this->inventory->getInventorySize() < this->inventory->getCapacity()) {
							this->inventory->setInventoryItem(item, (this->inventory->getInventoryItem(item.name).numOfItems + 1));
							cout << "	=> Saved to inventory." << endl;
						}
						else {
							cout << "	=> Inventory is full.\n	=> Expanding the inventory.\n" << endl;
							this->inventory->resizeInventory(this->inventory->getCapacity() + 5);
							this->inventory->setInventoryItem(item, (this->inventory->getInventoryItem(item.name).numOfItems + 1));
							cout << "	=> Saved to inventory." << endl;
						}
					}
				}
				else {
					int monsterATK = 0;
					cout << "* Attack failed." << endl;
					cout << "-------------- Monster's Turn --------------" << endl;
					cout << "The " << monster->getName() << " lunged!" << endl;

					if (monster->getPower() - this->getDefence() <= 0) {
						monsterATK = 1;
					}
					else {
						monsterATK = monster->getPower() - this->getDefence();
					}
					cout << monsterATK << " damage to " << this->getName() << " !" << endl;

					tempHP = this->getCurrentHP();
					this->setCurrentHP(this->getCurrentHP() - monsterATK);

					if (this->getCurrentHP() > 0) {
						cout << this->getName() << " HP: " << tempHP << " => " << this->getCurrentHP() << endl;
					}
					else {
						cout << this->getName() << " HP: " << tempHP << " => " << this->getCurrentHP() << " (Dead)\n" << endl;
						cout << "* The End..." << endl;

						this->setCurrentHP(0);
					}
				}
				break;
			case 3:
				this->useItem();
				break;
			}
		}
		else {
			cout << "-------------- Monster's Turn --------------" << endl;
			cout << "The " << monster->getName() << " lunged!" << endl;

			int monsterATK = 0;
			if (monster->getPower() - this->getDefence() <= 0) {
				monsterATK = 1;
			}
			else {
				monsterATK = monster->getPower() - this->getDefence();
			}
			cout << monsterATK << " damage to " << this->getName() << " !" << endl;

			tempHP = this->getCurrentHP();
			this->setCurrentHP(this->getCurrentHP() - monsterATK);

			if (this->getCurrentHP() > 0) {
				cout << this->getName() << " HP: " << tempHP << " => " << this->getCurrentHP() << endl;
			}
			else {
				cout << this->getName() << " HP: " << tempHP << " => " << this->getCurrentHP() << " (Dead)\n" << endl;
				cout << "* The End..." << endl;

				this->setCurrentHP(0);
			}

			isPlayerTurn = !isPlayerTurn;
		}
		cout << endl;
		system("pause");
		system("cls");
	} while (this->getCurrentHP() > 0 && monster->getCurrentHP() > 0);
}

Thief::~Thief(void) {
	cout << "Thank you for playing!" << endl;
}