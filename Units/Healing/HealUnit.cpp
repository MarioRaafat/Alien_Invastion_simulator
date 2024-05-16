#include "HealUnit.h"
#include "../../Game.h"
#include "LinkedQueue.h"

#include <cmath>

HealUnit::HealUnit(Game *game, int id, int t, int pw, int hl, int attC) :
        ArmyUnit(game, id, heal_unit, t, pw, hl, attC) {}

void HealUnit::attack() {
    ArmyUnit* damaged_unit = nullptr;
    LinkedQueue<ArmyUnit *> temp_list;
    EarthSoldier* damaged_soldier = nullptr;
    EarthTank* damaged_tank = nullptr;

    for(int i = 0; i < attackCapacity; i++) {
        damaged_soldier = game->pick_from_soldier_UML();

        if (damaged_soldier) {
            heal(damaged_soldier);

            if (!damaged_soldier->is_healed()) {
                temp_list.enqueue(damaged_soldier);
            } else {
                game->add_unit(damaged_soldier, earth_soldier);
            }
        } else {
            damaged_tank = game->pick_from_tank_UML();
            if (damaged_tank){
                heal(damaged_tank);

                if (!damaged_tank->is_healed()) {
                    temp_list.enqueue(damaged_tank);
                } else {
                    game->add_unit(damaged_tank, earth_tank);
                }
            } else {
                break;
            }
        }

    }

    while(!temp_list.isEmpty()) {
        temp_list.dequeue(damaged_unit);

        if (damaged_unit->getTypeId() == earth_soldier) {
            game->add_to_soldier_UML(static_cast<EarthSoldier*>(damaged_unit));
        } else {
            game->add_to_tank_UML(static_cast<EarthTank*>(damaged_unit));
        }
    }
}

void HealUnit::heal(ArmyUnit *damaged_unit) {
    if (!damaged_unit) {
        return;
    }

    int hl = 0;
    if (damaged_unit->getTypeId() == earth_soldier) {
        auto soldier = static_cast<EarthSoldier*>(damaged_unit);
        if (soldier->get_infection()) {
            //samll change here damaunig_getHealth() should be after this operation
            hl = (((((power * health) / 100) / sqrt(damaged_unit->getHealth()) ))) / 2;
            //shouldnot we check for the new health after the healing ????
            soldier->setHealth(soldier->getHealth() + hl);

            if (soldier->is_healed()) {
                soldier->set_immune(true);
                game->increment_immune_number();
                soldier->set_infection(false);
            }
        }
        return;
    }
//    if (hl == 0) {
    hl = (damaged_unit->getHealth() + (( (power * health) / 100) / sqrt(damaged_unit->getHealth())));
//    }
    damaged_unit->setHealth(hl);
}

