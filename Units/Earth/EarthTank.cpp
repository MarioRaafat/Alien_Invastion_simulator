#include "EarthTank.h"
#include "../../Game.h"
#include "LinkedQueue.h"

EarthTank::EarthTank(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit{game, id, earth_tank, t, pw, hl, attc} , count_UML{0} {}

/**
 * @brief attack function for EarthTank that attacks alien solider and monster
 * return them to the game if they are not killed and set the time of attack
 * priority to the solider
 * @param none
 * @return none
 */
void EarthTank::attack() {
    int time_step = game->get_time();
    LinkedQueue<ArmyUnit *> temp_alien_units;
    int  cap = attackCapacity;


    //Based on the 20% of the health of the tank condition to attack
    if (game->which_tank_attack()) {
        while (!game->stop_attacking_soldiers() && cap > getAttackCapacity() >> 1) {
            ArmyUnit* solider = game->pick_unit(alien_soldier);
            if (solider) {
                temp_alien_units.enqueue(solider);
            }
            --cap;
        }

        for (int i = cap; i > 0; --i) {
            ArmyUnit *monstear = game->pick_unit(alien_monster);
            if (monstear)
                temp_alien_units.enqueue(monstear);
        }
    } else {
        for (int i = cap; i > 0; --i) {
            ArmyUnit *monstear = game->pick_unit(alien_monster);
            if (monstear)
                temp_alien_units.enqueue(monstear);
        }
    }

    if (game->is_interactive()) {
        cout << "Et " << ID << " shots ";
        cout << temp_alien_units;
    }

    while (!temp_alien_units.isEmpty()) {
        ArmyUnit *curr{};

        temp_alien_units.dequeue(curr);

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

int EarthTank::get_count_UML() const {
    return count_UML;
}

void EarthTank::set_count_UML(int num) {
    count_UML = num;
}

bool EarthTank::is_healed() const {
    return (double(getHealth()) > double((double)getOriginalHealth() * 0.2));
}
