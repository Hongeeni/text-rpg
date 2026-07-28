#ifndef _THIEF_H_
#define _THIEF_H_

#include "character.h"

class Thief : public Player {
private:
	int specialAttackCost = 13;

public:
	Thief(const string name, const int stats[]);

	//setter
	void setSpecialAttackCost(int cost);
	//getter
	const int getSpecialAttackCost(void);

	void getPumped(void);
	void attack(Monster* monster);

	~Thief(void);
};

#endif
