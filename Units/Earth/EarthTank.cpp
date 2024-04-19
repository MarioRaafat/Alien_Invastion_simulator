#include "EarthTank.h"

EarthTank::EarthTank(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, 2, t, pw, hl, attc) {
}

void EarthTank::attack(ArmyUnit* solider) {
    damage(solider);
}