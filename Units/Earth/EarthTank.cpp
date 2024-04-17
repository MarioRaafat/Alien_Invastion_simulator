#include "EarthTank.h"

EarthTank::EarthTank(int id, int t, int pw, int hl, int attc) : ArmyUnit(id, 1, t, pw, hl, attc) 
{}

void EarthTank::attack(ArmyUnit* solider) {
    damage(solider);
}