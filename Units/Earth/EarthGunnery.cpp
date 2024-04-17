#include "EarthSoldier.h"

EarthGunnery::EarthGunnery(int id, int t, int pw, int hl, int attc) : ArmyUnit(id, 1, t, pw, hl, attc) 
{}

void EarthGunnery::attack(ArmyUnit* solider) {
    damage(solider);
}