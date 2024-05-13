#include "AlienSoldier.h"
#include "../../Game.h"
#include "LinkedQueue.h"

AlienSoldier::AlienSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit{game, id, alien_soldier, t, pw, hl, attc} {}

void AlienSoldier::attack() {
    LinkedQueue<ArmyUnit*> temp_alien_soldiers;

    cout << "As " << getID() << " shots ";
    for (int i = 0; i < getAttackCapacity(); ++i) {
        ArmyUnit *curr = game->getEarthArmy().pickUnit(earth_soldier);
        if (curr) {
            temp_alien_soldiers.enqueue(curr);
        }
    }

    cout << temp_alien_soldiers;

    while (!temp_alien_soldiers.isEmpty()) {
        ArmyUnit *curr{};

        temp_alien_soldiers.dequeue(curr);
        damage(curr);

        if (curr->isDead()) {
            game->add_to_killed_list(curr);
        } else {
            game->getEarthArmy().addUnit(curr, earth_soldier);
        }
    }
}
