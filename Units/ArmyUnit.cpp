#include "ArmyUnit.h"
#include <iostream>

ArmyUnit::ArmyUnit(Game *game, int id, unit_type tyId, int t, int pw, int hl, int attC) :
        game(game), ID(id), typeIdentifier(tyId), Tj(t), power(pw), health(hl), attackCapacity(attC) {
    setHealth(hl);
}

int ArmyUnit::getID() const {
    return ID;
}

int ArmyUnit::getTypeId() const {
    return typeIdentifier;
}

int ArmyUnit::getPower() const {
    return power;
}

void ArmyUnit::setHealth(int hl) {
    if (hl < 0) {
        health = 0;
    } else {
        health = hl;
    }
}

int ArmyUnit::getHealth() const {
    return health;
}

int ArmyUnit::getAttackCapacity() const {
    return attackCapacity;
}

void ArmyUnit::damage(ArmyUnit* enemy) {
    enemy->setHealth(enemy->getHealth() - ((power * health / 100) / static_cast<int>(enemy->getHealth())));
}

void ArmyUnit::print() const {
    std::cout << "ID: " << ID << ", Type: " << typeIdentifier << ", Time: " << Tj;
    std::cout << ", Power: " << power << ", Health: " << health << ", Attack Capacity: ";
    std::cout << attackCapacity << std::endl;
}

bool ArmyUnit::isDead() const {
   return health <= 0;
}
