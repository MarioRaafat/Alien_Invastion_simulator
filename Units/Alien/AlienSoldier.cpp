#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit(game, id, alien_soldier, t, pw, hl, attc) {
}

void AlienSoldier::attack(ArmyUnit* soldier) {
    damage(soldier);
}
