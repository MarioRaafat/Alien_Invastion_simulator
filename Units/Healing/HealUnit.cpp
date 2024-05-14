#include "HealUnit.h"
#include "../../Game.h"
#include "LinkedQueue.h"

#include <cmath>

HealUnit::HealUnit(Game *game, int id, int t, int pw, int hl, int attC) :
        ArmyUnit(game, id, heal_unit, t, pw, hl, attC) {}

void HealUnit::attack() {
    ArmyUnit* damaged_unit;
    LinkedQueue<ArmyUnit *> temp_list;
    EarthSoldier* damaged_soldier = game->pick_from_soldier_UML();
    EarthTank* damaged_tank = game->pick_from_tank_UML();

    for(int i = 0; i < attackCapacity; i++) {
        if (damaged_soldier) {
            heal(damaged_soldier);
            if (damaged_soldier->getHealth() < double(damaged_soldier->getOriginalHealth() * 0.2)) {
                temp_list.enqueue(damaged_soldier);
            }
            else {
                game->add_unit(damaged_soldier, earth_soldier);
            }
            damaged_soldier = game->pick_from_soldier_UML();
        }
        else if (damaged_tank){
            heal(damaged_tank);
            if (damaged_tank->getHealth() < double(damaged_tank->getOriginalHealth() * 0.2)) {
                temp_list.enqueue(damaged_tank);
            }
            else {
                game->add_unit(damaged_tank, earth_tank);
            }
            damaged_tank = game->pick_from_tank_UML();
        }
        else {
            break;
        }
    }

    while(!temp_list.isEmpty()) {
        temp_list.dequeue(damaged_unit);

        if (damaged_unit->getTypeId() == earth_soldier) {
            game->add_to_soldier_UML(static_cast<EarthSoldier*>(damaged_unit));
        }
        else {
            game->add_to_tank_UML(static_cast<EarthTank*>(damaged_unit));
        }
    }
}

void HealUnit::heal(ArmyUnit *damaged_unit) {
    int hl = (damaged_unit->getHealth() + (( (power * health) / 100) / sqrt(damaged_unit->getHealth()) )) ;
    damaged_unit->setHealth(hl);
}

