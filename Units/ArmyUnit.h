#ifndef ARMYUNIT_H
#define ARMYUNIT_H

#include "math.h"

class ArmyUnit
{

protected:

	int ID,
		typeIdentifier, // 1 for ES , 2 for ET , 3 for EG ...etc
		Tj, // time joining
		power,
		health,
		attackCapacity;

public:

	ArmyUnit(int id, int tyId, int t, int pw, int hl, int attC);

	// setters and getters ...

	int getID();
	int getTypeId();
	int getPower();
	void setHealth(int hl);
	int getHealth();
	int getAttackCapacity();

	void damage(ArmyUnit* enemy);
	virtual void attack(ArmyUnit* enemy) = 0;

};

#endif