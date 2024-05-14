#include "EarthSoldier.h"
#include "LinkedQueue.h"
#include "../../Game.h"

EarthSoldier::EarthSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit(game, id, earth_soldier, t, pw, hl, attc)
{
    count_UML = 0;
    immmune = infected = false;
}

void EarthSoldier::attack() {
    LinkedQueue<ArmyUnit *> temp_alien_soldiers;
    int time_step = game->get_time();

    //size_t alien_soldier_size = game->getAlienArmy().soldiers_count();

    for (int i = 0; i < attackCapacity; i++) {
        ArmyUnit *curr;
        if(infected) {
             curr = game->pick_unit(earth_soldier);
        }
        else {
            curr = game->pick_unit(alien_soldier);
        }

        if (curr) {
            temp_alien_soldiers.enqueue(curr);
        }
    }

    if (game->is_interactive()) {
        cout << "Es " << ID << " shots ";
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
        }
        else {
            if (infected) {
                int random = randomNumber(0, 100);
                if (random < 2) {
                    static_cast<EarthSoldier*>(curr)->set_infection(true);
                }
            }
            game->add_unit(curr, curr->getTypeId());
        }
    }

    // size_t curr_soldiers_count = game->getAlienArmy().soldiers_count();
    // if (alien_soldier_size != curr_soldiers_count) {
    //     game->getAlienArmy().updateKilledSoldiers(alien_soldier_size - curr_soldiers_count);
    // }

    /*
     Note:

     as we agreed, you will count the killed units in --> add_to_kill_list or in the end of the game
     */
}

int EarthSoldier::get_count_UML() {
    return count_UML;
}

void EarthSoldier::set_count_UML(int num) {
    count_UML = num;
}

void EarthSoldier::set_infection(bool infec) {
    infected = infec;
}

bool EarthSoldier::get_infection() {
    return infected;
}

void EarthSoldier::set_immune(bool im) {
    immmune = im;
}

bool EarthSoldier::get_immune() {
    return immmune;
}

int EarthSoldier::randomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
