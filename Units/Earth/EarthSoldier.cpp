#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit(game, id, earth_solider, t, pw, hl, attc) {}

void EarthSoldier::attack(ArmyUnit *solider) {
        damage(solider);
}