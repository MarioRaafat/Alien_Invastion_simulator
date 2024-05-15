#include "AlienMonster.h"
#include "../../Game.h"
#include "LinkedQueue.h"

AlienMonster::AlienMonster(Game *game, int id, int t, int pw, int hl, int attc, int infec) :
        ArmyUnit(game, id, alien_monster, t, pw, hl, attc)
{
    infection_prob = infec;
}

void AlienMonster::attack() {
    LinkedQueue<ArmyUnit*> temp;
    int time_step = game->get_time();
    int tank_cap = attackCapacity / 2;
    int soldier_cap = attackCapacity - tank_cap;


    for (int i = 0; i < soldier_cap; i++) {
        ArmyUnit *curr = game->pick_unit(earth_soldier);
        if (curr) {
            temp.enqueue(curr);
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
        int random = randomNumber(0, 100);

        temp.dequeue(curr);
        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }
        damage(curr);
        if (random < infection_prob) {
            if (curr->getTypeId() == earth_soldier) {
                static_cast<EarthSoldier*>(curr)->set_infection(true);
                game->increment_infection_number();
            }
        }

        if (curr->isDead()) {
            curr->setTd(time_step);
            game->add_to_killed_list(curr);
        }
        else if ((double)curr->getHealth() >= double(curr->getOriginalHealth() * 0.2)) {
            game->add_unit(curr, curr->getTypeId());
        }
        else {
            if (curr->getTypeId() == earth_soldier) {
                game->add_to_soldier_UML(static_cast<EarthSoldier*>(curr));
            }
            else if (curr->getTypeId() == earth_tank) {
                game->add_to_tank_UML(static_cast<EarthTank*>(curr));
            }
        }
    }
}

int AlienMonster::randomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}