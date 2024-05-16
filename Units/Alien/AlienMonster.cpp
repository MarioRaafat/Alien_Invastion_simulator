#include "AlienMonster.h"
#include "../../Game.h"
#include "LinkedQueue.h"

AlienMonster::AlienMonster(Game *game, int id, int t, int pw, int hl, int attc, int infec) :
        ArmyUnit(game, id, alien_monster, t, pw, hl, attc)
{
    infection_prob = infec;
}

/**
 * Description: This function is used to attack the earth units or save units
 * givers priority to the earth soldiers or save units then tanks
 * may infect the earth soldiers and make them attack the earth units
 */
void AlienMonster::attack() {
    LinkedQueue<ArmyUnit*> temp;
    int time_step = game->get_time();
    int tank_cap = attackCapacity / 2;
    int soldier_cap = attackCapacity - tank_cap;


    //check for cap - half cap bcs it has most prio bcs of the floor fun for example try if attacCap was 1
    for (int i = 0; i < soldier_cap; i++) {
        ArmyUnit *curr = game->pick_unit(earth_soldier);
        if (curr) {
            temp.enqueue(curr);
        } else {
            curr = game->pick_unit(saver_unit);
            if (curr) {
                temp.enqueue(curr);
            }
        }
    }

    for (int i = 0; i < tank_cap; i++) {
        ArmyUnit *curr = game->pick_unit(earth_tank);
        if (curr) {
            temp.enqueue(curr);
        }
    }


    if (game->is_interactive()) {
        cout << "AM " << ID << " shots ";
        cout << temp;
    }

    while (!temp.isEmpty()) {
        ArmyUnit *curr;
        int random = randomNum(0, 100);

        temp.dequeue(curr);
        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }
        //If eath sodlier in shold infect and not immune infect it
        if (random < infection_prob && curr->getTypeId() == earth_soldier) {
                auto earthsoldier = static_cast<EarthSoldier*>(curr);

                if (!earthsoldier->get_immune() && !earthsoldier->get_infection()) {
                    earthsoldier->set_infection(true);
                    game->increment_infection_number();
                    game->add_unit(curr, earth_soldier);
                    continue;
                }
        }
        //if it is not infected before or not es dmg it
        damage(curr);

        if (curr->isDead()) {
            curr->setTd(time_step);
            game->add_to_killed_list(curr);
            //if killed decrease the infection number
            if (curr->getTypeId() == earth_soldier && static_cast<EarthSoldier*>(curr)->get_infection()) {
                game->decrement_infection_number();
            }
        } else if ((double)curr->getHealth() >= double((double)curr->getOriginalHealth() * 0.2)) {//if it is healed return it to the game
            game->add_unit(curr, curr->getTypeId());
        } else {
            //return it to the UML if soldier or tank and !healed or return the save unit to the game
            if (curr->getTypeId() == earth_soldier) {
                game->add_to_soldier_UML(static_cast<EarthSoldier*>(curr));
            } else if (curr->getTypeId() == earth_tank) {
                game->add_to_tank_UML(static_cast<EarthTank*>(curr));
            } else {
                game->add_unit(curr, curr->getTypeId());
            }
        }
    }
}

int AlienMonster::randomNum(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
}

