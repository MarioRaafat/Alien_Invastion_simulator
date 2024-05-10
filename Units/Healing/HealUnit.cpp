//
// Created by mario on 5/10/2024.
//

#include "HealUnit.h"

#include <cmath>

HealUnit::HealUnit(Game *game, int id, int t, int pw, int hl, int attC) :
        ArmyUnit(game, id, heal_unit, t, pw, hl, attC) {}



void HealUnit::attack(ArmyUnit *damaged_unit) {
        damaged_unit->setHealth( (damaged_unit->getHealth() + ( (power * health) / 100) / sqrt(damaged_unit->getHealth()) ) );
}
