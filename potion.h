#ifndef _POTION_H_
#define _POTION_H_

#include "item.h"

class Potion {
protected:
	map<string, vector<string>> recipeList = {};

public:
	Potion(void);

	void setRecipeList(string potionName, vector<string> potionIngredient);
	const map<string, vector<string>> getRecipeList(void);

	const void printRecipe(string potionName);
	const void printAllRecipes(void);

	const void searchByName(string potionName);
	const void searchByIngredient(string potionIngredient);
};

#endif
