#include "EarthTank.h"
#include "../../Game.h"
#include "LinkedQueue.h"

EarthTank::EarthTank(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, earth_tank, t, pw, hl, attc)
{
    count_UML = 0;
}

void EarthTank::attack() {
    int time_step = game->get_time();
    LinkedQueue<ArmyUnit *> temp_alien_units;
    bool fight_solider{};
    int  cap = attackCapacity;

    // size_t alien_soldier_size = game->getAlienArmy().soldiers_count();
    // size_t alien_monster_size = game->getAlienArmy().monsters_count();

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

    // edit it

    // size_t curr_soldiers_count = game->getAlienArmy().soldiers_count();
    // size_t curr_monsters_count = game->getAlienArmy().monsters_count();
    // if (alien_soldier_size != curr_soldiers_count) {
    //     game->getAlienArmy().updateKilledSoldiers(alien_soldier_size - curr_soldiers_count);
    // }
    // if (alien_monster_size != curr_monsters_count) {
    //     game->getAlienArmy().updateKilledMonsters(alien_monster_size - curr_monsters_count);
    // }
}

int EarthTank::get_count_UML() {
    return count_UML;
}

void EarthTank::set_count_UML(int num) {
    count_UML = num;
}