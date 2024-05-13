#include "AlienDrone.h"
#include "../../Game.h"
#include "LinkedQueue.h"

AlienDrone::AlienDrone(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, alien_drone, t, pw, hl, attc) {
}

void AlienDrone::attack(int time_step) {
}