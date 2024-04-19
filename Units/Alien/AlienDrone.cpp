#include "AlienDrone.h"

AlienDrone::AlienDrone(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, 6, t, pw, hl, attc) {
}

void AlienDrone::attack(ArmyUnit* unit) {
    damage(unit);
}