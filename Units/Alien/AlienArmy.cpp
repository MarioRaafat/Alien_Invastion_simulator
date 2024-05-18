#include "AlienArmy.h"
#include <cstdlib>
#include "../../Random.h"

/**
 * @param droneFront to add to the front of the queue default is true
 * @brief Add a unit to the army in its list provide bool to add to the front of the queue
 */
void AlienArmy::addUnit(ArmyUnit *unit, unit_type type, bool droneFront) {
    switch (type) {
        case alien_soldier:
            Asoldiers.enqueue(static_cast<AlienSoldier *>(unit));
            break;
        case alien_monster:
            monsters.push_back(static_cast<AlienMonster *>(unit));
            break;
        case alien_drone:
            if (droneFront) {
                drones.push_front(static_cast<AlienDrone *>(unit));
            } else {
                drones.push_back(static_cast<AlienDrone *>(unit));
            }
            break;
        default:
            break;
    }
}

/**
 * Pick a unit from the army
 * @param type
 * @param droneFront to pick from the front of the queue default is true
 * @param pickone to pick only one unit default is false else pick nullptr if drone
 * @return ArmyUnit* of anyType Army or nullptr
 */
ArmyUnit *AlienArmy::pickUnit(unit_type type, bool droneFront, bool pickone) {
    AlienSoldier *soldier = nullptr;
    AlienDrone *drone = nullptr;
    AlienMonster *monster = nullptr;
    int random = 0;

    if (!monsters.empty()) {
        random = randomNum(0, static_cast<int>(monsters.size()) - 1);
    }

    switch (type) {
        case alien_soldier:
            if (Asoldiers.dequeue(soldier)) {
                return soldier;
            }
            break;
        case alien_monster:
            if (monsters.empty()) {
                return nullptr;
            }
            //BAG ADT swap with the last element and pop_back
            monster = monsters[random];
            monsters[random] = monsters[monsters.size() - 1];
            monsters[monsters.size() - 1] = nullptr;
            monsters.pop_back();
            return monster;
        case alien_drone:
            if (drones.size() <= 1) {
                if (drones.is_empty()) {
                    return nullptr;
                }
                if (pickone) {
                    drones.pop_front(drone);
                    return drone;
                } else {
                    return nullptr;
                }
            }
            if (droneFront) {
                drones.pop_front(drone);
                return drone;
            } else {
                drones.pop_back(drone);
                return drone;
            }
        default:
            return nullptr;
    }
    return nullptr;
}

void AlienArmy::print() const {
    std::cout << "====================== Alien Army Alive Units =====================\n";
    std::cout << Asoldiers.size() << " AS " << Asoldiers;
    std::cout << monsters.size() << " AM " << monsters;
    std::cout << drones.size() << " AD " << drones;
}

AlienArmy::~AlienArmy() {
    AlienSoldier *solider = {};
    AlienDrone *drone = {};

    for (size_t i = 0; i < monsters.size(); i++) {
        if (monsters[i] != nullptr) {
            delete monsters[i];
            monsters[i] = nullptr;
        }
    }

    while (Asoldiers.dequeue(solider)) {
            delete solider;
            solider = nullptr;
    }

    while (drones.pop_back(drone)) {
        delete drone;
        drone = nullptr;
    }
}

void AlienArmy::attack() {
    ArmyUnit* attackers[4]{};
    attackers[0] = pickUnit(alien_soldier);
    attackers[1] = pickUnit(alien_drone, true, false);
    attackers[2] = pickUnit(alien_drone, false, true);
    attackers[3] = pickUnit(alien_monster);
    bool front = true;

    // if there is only one drone then return it to the army donot attack
    if (attackers[2] && !attackers[1]) {
        addUnit(attackers[2], alien_drone);
        attackers[2] = nullptr;
    }

    for (const auto & attacker : attackers) {
        if (attacker) {
            attacker->attack();
            addUnit(attacker, attacker->getTypeId(), front);
        }
        front = !front;
    }
}

size_t AlienArmy::soldiers_count() const {
    return Asoldiers.size();
}
size_t AlienArmy::army_size() const {
    return Asoldiers.size() + monsters.size() + drones.size();
}