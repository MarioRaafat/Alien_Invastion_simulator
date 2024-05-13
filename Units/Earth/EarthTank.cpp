#include "EarthTank.h"
#include "../../Game.h"
#include "LinkedQueue.h"

EarthTank::EarthTank(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, earth_tank, t, pw, hl, attc) {
}

void EarthTank::attack(int time_step) {
    LinkedQueue<ArmyUnit *> temp_alien_units;
    bool fight_solider{};
    int  cap = getAttackCapacity();

    //NEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    size_t alien_soldier_size = game->getAlienArmy().soldiers_count();
    size_t alien_monster_size = game->getAlienArmy().monsters_count();


    if ((double)game->getEarthArmy().soliders_count() < (((double)game->getAlienArmy().soldiers_count()) * .3)) {
        fight_solider = true;
    }

    if (fight_solider) {
        while (((double)game->getEarthArmy().soliders_count() < (((double)game->getAlienArmy().soldiers_count()) * .8)) &&
                cap > getAttackCapacity() >> 1) {
            ArmyUnit* solider = game->getAlienArmy().pickUnit(alien_soldier);
            if (solider) {
                temp_alien_units.enqueue(solider);
            }
            --cap;
        }

        if (cap & 1)//cap is odd
            --cap;

        for (int i = cap; i >=0; --i) {
            ArmyUnit *monstear = game->getAlienArmy().pickUnit(alien_monster);
            if (monstear)
                temp_alien_units.enqueue(monstear);
        }
    } else {
        for (int i = cap; i >= 0; --i) {
            ArmyUnit *monstear = game->getAlienArmy().pickUnit(alien_monster);
            if (monstear)
                temp_alien_units.enqueue(monstear);
        }
    }

    //NEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    if (game->is_interactive()) {
        cout << "Et " << getID() << " shots ";
        cout << temp_alien_units;
    }

    while (!temp_alien_units.isEmpty()) {
        ArmyUnit *curr{};

        temp_alien_units.dequeue(curr);
        //NEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }

        damage(curr);

        if (curr->isDead()) {
            curr->setTd(time_step);
            game->add_to_killed_list(curr);
        } else {
            game->getAlienArmy().addUnit(curr, (unit_type) curr->getTypeId());
        }
    }

    //NEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    size_t curr_soldiers_count = game->getAlienArmy().soldiers_count();
    size_t curr_monsters_count = game->getAlienArmy().monsters_count();
    if (alien_soldier_size != curr_soldiers_count) {
        game->getAlienArmy().updateKilledSoldiers(alien_soldier_size - curr_soldiers_count);
    }
    if (alien_monster_size != curr_monsters_count) {
        game->getAlienArmy().updateKilledMonsters(alien_monster_size - curr_monsters_count);
    }
}