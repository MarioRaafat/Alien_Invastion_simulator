#include "AlienMonster.h"
#include "../../Game.h"
#include "LinkedQueue.h"

AlienMonster::AlienMonster(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit(game, id, alien_monster, t, pw, hl, attc) {
}

void AlienMonster::attack() {
        LinkedQueue<ArmyUnit*> temp_alien_monsters;
        int time_step = game->get_time();
        int tank_cap = attackCapacity / 2;
        int soldier_cap = attackCapacity - tank_cap;


        for (int i = 0; i < soldier_cap; i++) {
                ArmyUnit *curr = game->pick_unit(earth_soldier);
                if (curr) {
                        temp_alien_monsters.enqueue(curr);
                }
        }
        for (int i = 0; i < tank_cap; i++) {
                ArmyUnit *curr = game->pick_unit(earth_tank);
                if (curr) {
                        temp_alien_monsters.enqueue(curr);
                }
        }


        if (game->is_interactive()) {
                cout << "AM " << ID << " shots ";
                cout << temp_alien_monsters;
        }

        while (!temp_alien_monsters.isEmpty()) {
                ArmyUnit *curr;

                temp_alien_monsters.dequeue(curr);
                if (!curr->is_attacked()) {
                        curr->setTa(time_step);
                }
                damage(curr);

                if (curr->isDead()) {
                        curr->setTd(time_step);
                        game->add_to_killed_list(curr);
                }else if (curr->getHealth() >= double(curr->getOriginalHealth() * 0.2)){
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