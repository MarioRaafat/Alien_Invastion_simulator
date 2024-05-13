#include "EarthSoldier.h"
#include "LinkedQueue.h"
#include "../../Game.h"

EarthSoldier::EarthSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit(game, id, earth_soldier, t, pw, hl, attc) {}

void EarthSoldier::attack(int time_step) {
    LinkedQueue<ArmyUnit *> temp_alien_soldiers;

    size_t alien_soldier_size = game->getAlienArmy().soldiers_count();

    for (int i = 0; i < getAttackCapacity(); i++) {
        ArmyUnit *curr = game->getAlienArmy().pickUnit(alien_soldier);
        if (curr) {
            temp_alien_soldiers.enqueue(curr);
        }
    }

    if (game->is_interactive()) {
        cout << "Es " << getID() << " shots ";
        cout << temp_alien_soldiers;
    }

    while (!temp_alien_soldiers.isEmpty()) {
        ArmyUnit *curr{};

        temp_alien_soldiers.dequeue(curr);

        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }
        damage(curr);

        if (curr->isDead()) {
            curr->setTd(time_step);
            game->add_to_killed_list(curr);
        } else {
            game->getAlienArmy().addUnit(curr, alien_soldier);
        }
    }

    size_t curr_soldiers_count = game->getAlienArmy().soldiers_count();
    if (alien_soldier_size != curr_soldiers_count) {
        game->getAlienArmy().updateKilledSoldiers(alien_soldier_size - curr_soldiers_count);
    }
}
