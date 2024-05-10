#include "ArmyUnit.h"
#include <iostream>
#include <math.h>


ArmyUnit::ArmyUnit(Game *game, int id, unit_type tyId, int t, int pw, int hl, int attC) :
        game(game), ID(id), typeIdentifier(tyId), Tj(t), power(pw), health(hl), attackCapacity(attC)
{
    setHealth(hl);
    original_health = hl;
    count_UML = 0;
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

int ArmyUnit::getOriginalHealth() {
    return original_health;
}

int ArmyUnit::getAttackCapacity() const {
    return attackCapacity;
}

int ArmyUnit::get_count_UML() {
    return count_UML;
}

void ArmyUnit::set_count_UML(int num) {
    count_UML = num;
}

void ArmyUnit::damage(ArmyUnit* enemy) {
    enemy->setHealth((enemy->getHealth() - (( (power * health) / 100) / sqrt(enemy->getHealth())) ) );
}

void ArmyUnit::print() const {
    std::string msg = "(" + std::to_string(getHealth()) + ")";
    std::cout << getID() << msg << ",";
}

bool ArmyUnit::isDead() const {
   return health <= 0;
}
