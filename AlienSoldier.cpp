#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(int id, int t, int pw, int hl, int attc) :
    ArmyUnit(id, 4, t, pw, hl, attc) {
}

void AlienSoldier::attack(ArmyUnit* soldier) {
    damage(soldier);
}
