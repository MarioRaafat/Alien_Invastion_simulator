#include "EarthSoldier.h"
#include "LinkedQueue.h"
#include "../../Game.h"

EarthSoldier::EarthSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit(game, id, earth_soldier, t, pw, hl, attc) {}

void EarthSoldier::attack() {
    LinkedQueue<ArmyUnit *> temp_alien_soldiers;

    cout << "Es " << getID() << " shots ";
    for (int i = 0; i < getAttackCapacity(); i++) {
        ArmyUnit *curr = game->getAlienArmy().pickUnit(alien_soldier);
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
            game->getAlienArmy().addUnit(curr, alien_soldier);
        }
    }
}
