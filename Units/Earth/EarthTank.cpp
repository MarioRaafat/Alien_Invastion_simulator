#include "EarthTank.h"
#include "../../Game.h"
#include "LinkedQueue.h"

EarthTank::EarthTank(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, earth_tank, t, pw, hl, attc) {
}

void EarthTank::attack() {
    LinkedQueue<ArmyUnit *> temp_alien_units;
    unit_type unit;

    cout << "Et " << getID() << " shots ";
    for (int i = 0; i < getAttackCapacity(); i++) {
        //Note That do epsilon is used to get a certian accuracy in the comparison
         if ((double)game->getEarthArmy().soliders_count() < ((double)game->getAlienArmy().soldiers_count() / 3)) {
             unit = alien_soldier;
         } else {
             unit = alien_monster;
         }

        ArmyUnit *curr = game->getAlienArmy().pickUnit(unit);
        if (curr) {
            temp_alien_units.enqueue(curr);
        }
    }

    cout << temp_alien_units;

    while (!temp_alien_units.isEmpty()) {
        ArmyUnit *curr{};

        temp_alien_units.dequeue(curr);
        damage(curr);

        if (curr->isDead()) {
            game->add_to_killed_list(curr);
        } else {
            game->getAlienArmy().addUnit(curr, (unit_type)curr->getTypeId());
        }
    }
}