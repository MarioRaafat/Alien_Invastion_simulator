#include "AlienSoldier.h"
#include "../../Game.h"
#include "LinkedQueue.h"

AlienSoldier::AlienSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit{game, id, alien_soldier, t, pw, hl, attc} {}

    /**
     * @brief AlienSoldier::attack
     * AlienSoldier's attack function. It attacks the EarthSoldiers and SaverUnits.
     * It picks the units to attack and then attacks them if exist.
     */
void AlienSoldier::attack() {
    LinkedQueue<ArmyUnit*> temp_alien_soldiers;
    int time_step = game->get_time();


    for (int i = getAttackCapacity(); i > 0; --i) {
        ArmyUnit *curr = game->pick_unit(earth_soldier);
        if (curr) {
            temp_alien_soldiers.enqueue(curr);
        } else {
            curr = game->pick_unit(saver_unit);
            if (curr) {
                temp_alien_soldiers.enqueue(curr);
            }
        }
    }

    if (game->is_interactive()) {
        cout << "AS " << ID << " shots ";
        cout << temp_alien_soldiers;
    }

    while (!temp_alien_soldiers.isEmpty()) {
        ArmyUnit *curr{};

        temp_alien_soldiers.dequeue(curr);
        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }

        damage(curr);
        unit_type curr_type = curr->getTypeId();

        if (curr_type == earth_soldier) {
            if (curr->isDead()) {
                curr->setTd(time_step);
                game->add_to_killed_list(curr);
                if (static_cast<EarthSoldier*>(curr)->get_infection()) {
                   //if it is killed and infected decrement the infection number
                    game->decrement_infection_number();
                }
            } else if ((double) curr->getHealth() >= double((double)curr->getOriginalHealth() * 0.2)){
                //if it is not dead and healed return it to the game
                game->add_unit(curr, earth_soldier);
            } else {
                //else it need to be returned to the UML
                game->add_to_soldier_UML(static_cast<EarthSoldier*>(curr));
            }
        } else if (curr_type == saver_unit) {
            if (curr->isDead()) {
                curr->setTd(time_step);
                game->add_to_killed_list(curr);
            } else {
                game->add_unit(curr, saver_unit);
            }
        }
    }
}
