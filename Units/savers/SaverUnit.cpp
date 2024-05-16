//
// Created by mario on 5/15/2024.
//

#include "SaverUnit.h"
#include "../../Game.h"

SaverUnit::SaverUnit(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit {game, id, saver_unit, t, pw, hl, attc} {}

void SaverUnit::attack() {
                
    LinkedQueue<ArmyUnit *> temp;
    int time_step = game->get_time();

    for (int i = 0; i < attackCapacity; i++) {
        ArmyUnit *curr;
        curr = game->pick_unit(alien_soldier);

        if (curr) {
            temp.enqueue(curr);
        }
    }

    if (game->is_interactive()) {
        cout << "SU " << ID << " shots ";
        cout << temp;
    }

    while (!temp.isEmpty()) {
        ArmyUnit *curr{};

        temp.dequeue(curr);

        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }

        damage(curr);

        if (curr->isDead()) {
            curr->setTd(time_step);
            game->add_to_killed_list(curr);
        } else {
            game->add_unit(curr, curr->getTypeId());
        }
    }
}
