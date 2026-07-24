#ifndef _MAGICIAN_H_
#define _MAGICIAN_H_

#include "character.h"

class Magician : public Player {
private:
	int specialAttackCost = 12;

public:
	Magician(const string name, const int stats[]);

	//setter
	void setSpecialAttackCost(int cost);
	//getter
	const int getSpecialAttackCost(void);

	void getPumped(void);
	void attack(Monster* monster);

	~Magician(void);
};

#endif
