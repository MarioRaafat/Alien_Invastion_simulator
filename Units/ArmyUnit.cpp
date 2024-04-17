#include "ArmyUnit.h"

ArmyUnit::ArmyUnit(int id, int tyId, int t, int pw, int hl, int attC) :
	ID(id), typeIdentifier(tyId), Tj(t), power(pw), health(hl), attackCapacity(attC)
{}

int ArmyUnit::getID()
{
	return ID;
}

int ArmyUnit::getTypeId()
{
	return typeIdentifier;
}

int ArmyUnit::getPower() {
	return power;
}

void ArmyUnit::setHealth(int hl) {
	health = hl;
}

int ArmyUnit::getHealth() {
	return health;
}

int ArmyUnit::getAttackCapacity() {
	return attackCapacity;
}

void ArmyUnit::damage(ArmyUnit* enemy) {
	enemy->setHealth(enemy->getHealth() - ((power * health / 100) / sqrt(enemy->getHealth())));
}


