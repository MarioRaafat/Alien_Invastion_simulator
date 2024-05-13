#include "HealUnit.h"
#include "../../Game.h"
#include "LinkedQueue.h"

#include <cmath>

HealUnit::HealUnit(Game *game, int id, int t, int pw, int hl, int attC) :
        ArmyUnit(game, id, heal_unit, t, pw, hl, attC) {}



void HealUnit::attack(int time_step) {
//        damaged_unit->setHealth( (damaged_unit->getHealth() + ( (power * health) / 100) / sqrt(damaged_unit->getHealth()) ) );
}
