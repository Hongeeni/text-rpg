#ifndef _WARRIOR_H_
#define _WARRIOR_H_

#include "character.h"

class Warrior : public Player {
private:
	int specialAttackCost = 12;

public:
	Warrior(const string name, const int stats[]);

	//setter
	void setSpecialAttackCost(int cost);
	//getter
	const int getSpecialAttackCost(void);

	void getPumped(void);
	void attack(Monster* monster);

	~Warrior(void);
};

#endif
