#ifndef _ARCHER_H_
#define _ARCHER_H_

#include "character.h"

class Archer : public Player {
private:
	int specialAttackCost = 13;

public:
	Archer(const string name, const int stats[]);

	//setter
	void setSpecialAttackCost(int cost);
	//getter
	const int getSpecialAttackCost(void);

	void getPumped(void);
	void attack(Monster* monster);

	~Archer(void);
};

#endif
