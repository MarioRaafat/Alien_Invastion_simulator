#include "ArmyUnit.h"
#include <iostream>
#include <math.h>


ArmyUnit::ArmyUnit(Game *game, int id, unit_type tyId, int t, int pw, int hl, int attC) :
        game(game), ID(id), typeIdentifier(tyId), Tj(t), power(pw), health(hl), attackCapacity(attC)
{
    setHealth(hl);
    original_health = health;
}

int ArmyUnit::getID() const {
    return ID;
}

unit_type ArmyUnit::getTypeId() const {
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

int ArmyUnit::getOriginalHealth() const{
    return original_health;
}

int ArmyUnit::getAttackCapacity() const {
    return attackCapacity;
}

void ArmyUnit::damage(ArmyUnit* enemy) {
    if (!enemy) {
        return;
    }

    if (enemy->getHealth() > 0) {
        enemy->setHealth((enemy->getHealth() - (( (power * health) / 100) / sqrt(enemy->getHealth())) ) );
    } else {
        enemy->setHealth(0);
    }
}

void ArmyUnit::print() const {
    std::string msg = "(" + std::to_string(getHealth()) + ',' + std::to_string(getOriginalHealth() ) + ")";
    std::cout << getID() << msg;
}

bool ArmyUnit::isDead() const {
   return health <= 0;
}

std::ostream &operator<<(std::ostream &os, const ArmyUnit &unit) {
    os <<  "(" << unit.getID() << "->" << unit.getHealth() << ")";
    return (os);
}

int ArmyUnit::getDBb() const {
    return (Td - Ta);
}

bool ArmyUnit::is_dimmised() const {
    return Td != -1;
}

bool ArmyUnit::is_attacked() const {
   return Ta != -1;
}

int ArmyUnit::getDd() const {
    return Td - Ta;
}

int ArmyUnit::getDf() const {
   return Ta - Tj;
}

int ArmyUnit::getTd() const {
    return Td;
}

int ArmyUnit::getTj() const {
   return Tj;
}

int ArmyUnit::getTa() const {
    return Ta;
}

void ArmyUnit::setTa(const int time) {
    Ta = time;
}

void ArmyUnit::setTd(int time) {
    Td = time;
}
