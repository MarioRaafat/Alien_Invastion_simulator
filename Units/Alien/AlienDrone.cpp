#include "AlienDrone.h"
#include "../../Game.h"
#include "LinkedQueue.h"

AlienDrone::AlienDrone(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit{game, id, alien_drone, t, pw, hl, attc} {
}
void AlienDrone::attack() {
    LinkedQueue<ArmyUnit*> temp_enemy_units;
    int half_cap = attackCapacity >> 1;

    //check for cap - half cap bcs it has most prio bcs of the floor fun for example try if attacCap was 1
    for (int i = 0; i < attackCapacity - half_cap; ++i) {
        ArmyUnit* curr = game->pick_unit(earth_tank);
        if (curr) {
            temp_enemy_units.enqueue(curr);
        }
    }
    for (int i = 0; i < half_cap; ++i) {
        ArmyUnit* curr = game->pick_unit(earth_gunnery);
        if (curr) {
            temp_enemy_units.enqueue(curr);
        }
    }

    //interactive mode for the printing
    if (game->is_interactive()) {
        cout << "AD " << ID << " shots ";
        cout << temp_enemy_units;
    }

    while (!temp_enemy_units.isEmpty()) {
        ArmyUnit* curr{};

        temp_enemy_units.dequeue(curr);
        if (!curr->is_attacked()) {
            curr->setTa(game->get_time());
        }
        damage(curr);

        if (curr->isDead()) {
            game->add_to_killed_list(curr);
            curr->setTd(game->get_time());
        } else {
            game->add_unit(curr, curr->getTypeId());
        }
    }
}