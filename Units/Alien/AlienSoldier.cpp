#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit(game, id, 4, t, pw, hl, attc) {
}

void AlienSoldier::attack(ArmyUnit* soldier) {
    damage(soldier);
}
