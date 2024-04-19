#include "AlienMonster.h"

AlienMonster::AlienMonster(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, 5, t, pw, hl, attc) {
}

void AlienMonster::attack(ArmyUnit *soldier) {
    damage(soldier);
}

