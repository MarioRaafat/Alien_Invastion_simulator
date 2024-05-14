#include "AlienSoldier.h"
#include "../../Game.h"
#include "LinkedQueue.h"

AlienSoldier::AlienSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit{game, id, alien_soldier, t, pw, hl, attc} {}

void AlienSoldier::attack() {
    LinkedQueue<ArmyUnit*> temp_alien_soldiers;
    int time_step = game->get_time();

    //size_t earthSoliderSize = game->getEarthArmy().soliders_count();

    for (int i = 0; i < getAttackCapacity(); i++) {
        ArmyUnit *curr = game->pick_unit(earth_soldier);
        if (curr) {
            temp_alien_soldiers.enqueue(curr);
        }
    }

    if (game->is_interactive()) {
        cout << "AS " << ID << " shots ";
        cout << temp_alien_soldiers;
    }

    while (!temp_alien_soldiers.isEmpty()) {
        ArmyUnit *curr;

        temp_alien_soldiers.dequeue(curr);
        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }
        damage(curr);

        if (curr->isDead()) {
            curr->setTd(time_step);
            game->add_to_killed_list(curr);
        }else if (curr->getHealth() >= double(curr->getOriginalHealth() * 0.2)){
            game->add_unit(curr, earth_soldier);
        }
        else {
            game->add_to_soldier_UML(static_cast<EarthSoldier*>(curr));
        }
    }

    // size_t curr_soliders_count = game->getEarthArmy().soliders_count();
    // if (earthSoliderSize != curr_soliders_count) {
    //     game->getEarthArmy().updateKilledSoldiers(earthSoliderSize - curr_soliders_count);
    // }
}
