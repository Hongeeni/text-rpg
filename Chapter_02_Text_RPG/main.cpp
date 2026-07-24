#include "potion.h"
#include "warrior.h"
#include "magician.h"
#include "thief.h"
#include "archer.h"

#include <cstdlib>
#include <ctime>

Monster slime("Slime", 12, 130, 100, 30, "Slime's Jelly", 7);
Monster herbGoat("Herb Goat", 30, 165, 135, 50, "Herb", 23);
Monster moonWolf("MoonWolf", 48, 190, 160, 75, "Mana Herb", 32);
Monster undine("Undine", 62, 230, 200, 93, "Holy Water", 41);
Monster golem("Golem", 83, 300, 210, 105, "Golem's Stone", 65);
vector<Monster> monsterType = { slime , herbGoat, moonWolf, undine, golem };

void setStatus(string* name, int (*stats)[]);
void printStatus(const string name, const int stats[]);
void restTent(Player* player, Inventory<Item>* playerInventory);
void selectJob(Player** player, const string name, const int stats[]);
void potionWorkshop(PotionRecipe potionRecipe);
void adventure(Player* player);

int main(void) {
	srand(static_cast<unsigned int>(time(NULL)));

	//Player Class
	Player* player = nullptr;

	//Player Default Settings
	{
		string name = "None";
		const int statsSize = 4;

		//stats[0] = HP, stats[1] = MP, stats[2] = ATK, stats[3] = DEF
		int stats[statsSize] = { 0 };

		setStatus(&name, &stats);
		printStatus(name, stats);

		//select < Job Selection > menu
		selectJob(&player, name, stats);
		player->getPumped();
		player->printPlayerStatus();
		system("pause");
		system("cls");
	}

	//start Game
	adventure(player);

	delete player;
	return 0;
}

// Functions
void setStatus(string* name, int (*stats)[]) {
	cout << "===========================================" << "\n	[Dungeon Escape Text RPG]\n" << "===========================================" << endl;
	cout << "Enter your hero's name: ";
	cin >> *name;
	cout << endl;
	cout << "(HP and MP input range : 100 ~ 250)\nEnter HP: ";
	cin >> (*stats)[0];
	cout << "Enter MP: ";
	cin >> (*stats)[1];
	cout << endl;
	cout << "(Attack and Defence input range : 50 ~ 150)\nEnter Attack: ";
	cin >> (*stats)[2];
	cout << "Enter Defence: ";
	cin >> (*stats)[3];
	cout << endl;

	// check HP and MP
	if (((*stats)[0] < 99 || (*stats)[1] < 99) || ((*stats)[0] > 251 || (*stats)[1] > 251)) {
		do {
			cout << "\nHP or MP is outside The input range. Try again." << endl;
			cout << "(HP and MP input range : 100 ~ 250)\nEnter HP: ";
			cin >> (*stats)[0];
			cout << "Enter MP: ";
			cin >> (*stats)[1];
			cout << endl;
		} while (((*stats)[0] < 99 || (*stats)[1] < 99) || ((*stats)[0] > 251 || (*stats)[1] > 251));
	}

	// check ATK and DEF
	if (((*stats)[2] < 49 || (*stats)[3] < 49) || ((*stats)[2] > 151 || (*stats)[3] > 151)) {
		do {
			cout << "Attack or Defense is outside The input range. Try again." << endl;
			cout << "(Attack and Defence input range : 50 ~ 150)\nEnter Attack: ";
			cin >> (*stats)[2];
			cout << "Enter Defence: ";
			cin >> (*stats)[3];
			cout << endl;
		} while (((*stats)[2] < 49 || (*stats)[3] < 49) || ((*stats)[2] > 151 || (*stats)[3] > 151));
	}
}

void printStatus(const string name, const int stats[]) {
	cout << "===========================================\n	" << name << "'s Stats\n" << "===========================================" << endl;
	cout << "HP: " << stats[0] << "		MP: " << stats[1] << endl;
	cout << "Attack: " << stats[2] << "	Defence: " << stats[3] << endl;
	cout << "===========================================" << endl;

	system("pause");
	system("cls");
}

void restTent(Player* player, Inventory<Item>* playerInventory) {
	string userInput = "None";
	int inputMenu = 0;

	do {
		cout << "* You received " << playerInventory->getInventoryItem("HP Potion").numOfItems << " HP Potions and " << playerInventory->getInventoryItem("MP Potion").numOfItems << " MP Potions." << endl;
		cout << "============================================" << endl;
		cout << "	< Rest tent >" << endl;
		cout << "1. HP Recovery	2. MP Recovery\n3. Status	0. Go back" << endl;
		cout << "============================================" << endl;
		cout << "Choose: ";
		cin >> userInput;
		cout << endl;

		if (userInput >= "0" && userInput < "4") {
			inputMenu = stoi(userInput);
		}
		else {
			cout << "Invalid input. Try again.\n" << endl;
			inputMenu = 9;

			system("pause");
			system("cls");
			continue;
		}

		switch (inputMenu) {
		case 0:
			cout << "Get ready for The next battle!\n" << endl;
			system("pause");
			system("cls");
			break;
		case 1:
			if (playerInventory->getInventoryItem("HP Potion").numOfItems > 0) {
				if (player->getCurrentHP() < player->getMaxHP()) {
					playerInventory->setInventoryItem("HP Potion", (playerInventory->getInventoryItem("HP Potion").numOfItems - 1));
					if ((player->getCurrentHP() + 20) < player->getMaxHP()) {
						player->setCurrentHP(player->getCurrentHP() + 20);
					}
					else {
						player->setCurrentHP(player->getMaxHP());
					}
					cout << "* HP increased by 20. (HP Potion used: " << playerInventory->getInventoryItem("HP Potion").numOfItems << " left)\n" << endl;
				}
				else {
					cout << "* Recovery is already complete.\n" << endl;
				}
			}
			else {
				cout << "* You don't have an HP Potion.\n" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 2:
			if (playerInventory->getInventoryItem("MP Potion").numOfItems > 0) {
				if (player->getCurrentMP() < player->getMaxMP()) {
					playerInventory->setInventoryItem("MP Potion", (playerInventory->getInventoryItem("MP Potion").numOfItems - 1));
					if ((player->getCurrentMP() + 20) < player->getMaxMP()) {
						player->setCurrentMP(player->getCurrentMP() + 20);
					}
					else {
						player->setCurrentMP(player->getMaxMP());
					}
					cout << "* MP increased by 20. (MP Potion used: " << playerInventory->getInventoryItem("MP Potion").numOfItems << " left)\n" << endl;
				}
				else {
					cout << "* Recovery is already complete.\n" << endl;
				}
			}
			else {
				cout << "* You don't have an MP Potion.\n" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 3:
			player->printPlayerStatus();
			system("pause");
			system("cls");
			break;
		}
	} while (inputMenu != 0);
}

void selectJob(Player** player, const string name, const int stats[]) {
	bool isSelect = false;
	string userInput = "None";
	int inputMenu = 0;

	while (!isSelect) {
		cout << "============================================\n	< Job Selection >\n" << name << ", choose your job!" << endl;
		cout << "1. Warrior   2. Mage   3. Rogue   4. Archer" << endl;
		cout << "============================================" << endl;
		cout << "Choose: ";
		cin >> userInput;
		cout << endl;

		if (userInput >= "0" && userInput <= "9") {
			inputMenu = stoi(userInput);
		}
		else {
			cout << "Invalid input. Try again.\n" << endl;
			system("pause");
			system("cls");
			continue;
		}

		switch (inputMenu) {
		case 1:
			*player = new Warrior(name, stats);
			isSelect = true;
			break;
		case 2:
			*player = new Magician(name, stats);
			isSelect = true;
			break;
		case 3:
			*player = new Thief(name, stats);
			isSelect = true;
			break;
		case 4:
			*player = new Archer(name, stats);
			isSelect = true;
			break;
		default:
			cout << "Invalid input. Try again.\n" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

void potionWorkshop(PotionRecipe potionRecipe) {
	int inputMenu = 0;
	string userInput = "None";
	string lowerByUserInput = "None";

	do {
		cout << "============================================\n	< Potion Workshop >\n============================================" << endl;
		cout << "1. Show all recipes\n2. Search by potion name\n3. Search by ingredient\n4. Making Potion\n0. Go back" << endl;
		cout << "============================================" << endl;
		cout << "Choose: ";
		cin >> userInput;
		cout << endl;

		if (userInput >= "0" && userInput < "5") {
			inputMenu = stoi(userInput);
		}
		else {
			cout << "Invalid input. Try again.\n" << endl;
			inputMenu = 9;

			system("pause");
			system("cls");
			continue;
		}

		switch (inputMenu) {
		case 0:
			system("cls");
			break;
		case 1:
			potionRecipe.printAllRecipes();
			break;
		case 2:
			cout << "Search potion name: ";
			cin >> userInput;
			cout << endl;

			lowerByUserInput = userInput;
			for (int i = 0; i < lowerByUserInput.size(); i++) {
				lowerByUserInput[i] = tolower(lowerByUserInput[i]);
			}
			potionRecipe.searchByName(lowerByUserInput);
			break;
		case 3:
			cout << "Search potion Ingredient: ";
			cin >> userInput;
			cout << endl;

			lowerByUserInput = userInput;
			for (int i = 0; i < lowerByUserInput.size(); i++) {
				lowerByUserInput[i] = tolower(lowerByUserInput[i]);
			}
			potionRecipe.searchByIngredient(lowerByUserInput);
			break;
		case 4:
			break;
		}
	} while (inputMenu != 0);
}

void adventure(Player* player) {
	//PotionRecipe Class
	PotionRecipe potionRecipe;

	string userInput = "None";
	int inputMenu = 0;

	do {
		Monster monster;

		int randomMonsterIndex = rand() % monsterType.size();
		monster = monsterType[randomMonsterIndex];

		cout << "============================================\n	< Select Action >" << endl;
		cout << "1. Adventure!	2. Rest	3. Status" << endl;
		cout << "4. Inventory	5. Potion Shop	0. Exit Game" << endl;
		cout << "============================================" << endl;
		cout << "Choose: ";
		cin >> userInput;

		if (userInput >= "0" && userInput < "6") {
			inputMenu = stoi(userInput);
			system("cls");
		}
		else {
			cout << "Invalid input. Try again.\n" << endl;
			inputMenu = 9;

			system("pause");
			system("cls");
			continue;
		}
		switch (inputMenu) {
		case 0:
			cout << "\n\nThe hero returned home after finishing the adventure.\n\nExiting the game." << endl << endl;
			break;
		case 1:
			player->attack(&monster);

			if (player->getCurrentHP() <= 0) {
				cout << "* Your HP is very low. You need to rest." << endl;
				cout << "============================================\n	< Select Action >" << endl;
				cout << "1. Rest			0. Exit Game" << endl;
				cout << "============================================\n" << endl;
				cout << "Choose: ";
				cin >> userInput;
				system("cls");

				if (userInput >= "0" && userInput < "2") {
					inputMenu = stoi(userInput);
				}
				else {
					do {
						cout << "* Your HP is very low. You need to rest." << endl;
						cout << "============================================\n	< Select Action >" << endl;
						cout << "1. Rest			0. Exit Game" << endl;
						cout << "============================================" << endl;
						cout << "Invalid input. Try again.\n" << endl;
						cout << "Choose: ";
						cin >> userInput;
						system("cls");
					} while (userInput < "0" || userInput > "1");
					inputMenu = stoi(userInput);
				}

				switch (inputMenu) {
				case 0:
					cout << "\n\nThe hero returned home after finishing the adventure.\n\nExiting the game." << endl << endl;
					break;
				case 1:
					restTent(player, player->inventory);
					break;
				}
			}
			break;
		case 2:
			restTent(player, player->inventory);
			break;
		case 3:
			player->printPlayerStatus();
			system("pause");
			system("cls");
			break;
		case 4:
			player->sortItems();
			player->inventory->printInventory(player->getName());
			system("pause");
			system("cls");
			break;
		case 5:
			potionWorkshop(potionRecipe);
			break;
		}
	} while (inputMenu != 0);
}