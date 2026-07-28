#include "potion.h"

Potion::Potion(void) {
	recipeList = {
	{ "HP Potion", { "Herb", "Holy Water" } },
	{ "MP Potion", { "Mana Herb", "Holy Water" } }
	};
}

void Potion::setRecipeList(string potionName, vector<string> potionIngredient) {
	this->recipeList[potionName] = potionIngredient;
}
const map<string, vector<string>> Potion::getRecipeList(void) {
	return this->recipeList;
}

const void Potion::printRecipe(string potionName) {
	cout << potionName << " ( " << this->recipeList[potionName][0] << ", " << this->recipeList[potionName][1] << " )" << endl;
}
const void Potion::printAllRecipes(void) {
	cout << "=========== < All recipes > ===========" << endl;
	for (auto recipe = this->recipeList.begin(); recipe != this->recipeList.end(); recipe++) {
		cout << "=> ";
		this->printRecipe((*recipe).first);
	}
	cout << endl;
	system("pause");
	system("cls");
}

const void Potion::searchByName(string potionName) {
	bool isFound = false;
	string tempName = "None";

	for (auto recipe = this->recipeList.begin(); recipe != this->recipeList.end(); recipe++) {
		tempName = (*recipe).first;
		remove(tempName.begin(), tempName.end(), ' ');
		tempName.pop_back();

		for (int i = 0; i < tempName.size(); i++) {
			tempName[i] = tolower(tempName[i]);
		}
		if (potionName == tempName) {
			isFound = true;
			cout << "=> ";
			this->printRecipe((*recipe).first);
			cout << endl;
			break;
		}
	}
	if (!isFound) {
		cout << "Potion can't be found.\n" << endl;
	}
	system("pause");
	system("cls");
}
const void Potion::searchByIngredient(string potionIngredient) {
	bool isSpacing = false;
	bool isFound = false;

	for (auto recipe = this->recipeList.begin(); recipe != this->recipeList.end(); recipe++) {
		vector<string> tempIngredient = (*recipe).second;
		for (int x = 0; x < tempIngredient.size(); x++) {
			for (int y = 0; y < tempIngredient[x].size(); y++) {
				if ((tempIngredient[x])[y] != ' ') {
					(tempIngredient[x])[y] = tolower((tempIngredient[x])[y]);
				}
				else {
					isSpacing = true;
				}
			}
			if (isSpacing) {
				remove(tempIngredient[x].begin(), tempIngredient[x].end(), ' ');
				tempIngredient[x].pop_back();
			}
		}
		if (potionIngredient == tempIngredient[0] || potionIngredient == tempIngredient[1]) {
			isFound = true;
			cout << "=> ";
			this->printRecipe((*recipe).first);
			cout << endl;
		}
	}
	if (!isFound) {
		cout << "Potion can't be found.\n" << endl;
	}

	system("pause");
	system("cls");
}