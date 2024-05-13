#include "AlienSoldier.h"
#include "../../Game.h"
#include "LinkedQueue.h"

AlienSoldier::AlienSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit{game, id, alien_soldier, t, pw, hl, attc} {}

void AlienSoldier::attack(int time_step) {
    LinkedQueue<ArmyUnit*> temp_alien_soldiers;

    //NEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    size_t earthSoliderSize = game->getEarthArmy().soliders_count();

    for (int i = 0; i < getAttackCapacity(); ++i) {
        ArmyUnit *curr = game->getEarthArmy().pickUnit(earth_soldier);
        if (curr) {
            temp_alien_soldiers.enqueue(curr);
        }
    }

    //Newwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
    if (game->is_interactive()) {
        cout << "As " << getID() << " shots ";
        cout << temp_alien_soldiers;
    }

    while (!temp_alien_soldiers.isEmpty()) {
        ArmyUnit *curr{};
        //NEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

        temp_alien_soldiers.dequeue(curr);
        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }
        damage(curr);

        if (curr->isDead()) {
            //NEWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
            curr->setTd(time_step);
            game->add_to_killed_list(curr);
        } else {
            game->getEarthArmy().addUnit(curr, earth_soldier);
        }
    }

    //NEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    size_t curr_soliders_count = game->getEarthArmy().soliders_count();
    if (earthSoliderSize != curr_soliders_count) {
        game->getEarthArmy().updateKilledSoldiers(earthSoliderSize - curr_soliders_count);
    }
}
