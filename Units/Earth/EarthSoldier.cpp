#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(int id, int t, int pw, int hl, int attc) : ArmyUnit(id, 1, t, pw, hl, attc) 
{}

void EarthSoldier::attack(ArmyUnit *solider) {
    damage(solider);
}