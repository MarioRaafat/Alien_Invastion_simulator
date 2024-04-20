#include "AlienMonster.h"

AlienMonster::AlienMonster(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, alien_monster, t, pw, hl, attc) {
}

void AlienMonster::attack(ArmyUnit *soldier) {
    damage(soldier);
}

