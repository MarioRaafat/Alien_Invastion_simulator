#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, 3, t, pw, hl, attc) {}

void EarthGunnery::attack(ArmyUnit* solider) {
    damage(solider);
}

bool EarthGunnery::operator>(const EarthGunnery &other) const {
    //Priority is based on power + health;
    return (power + health) > (other.power + other.health);
}
