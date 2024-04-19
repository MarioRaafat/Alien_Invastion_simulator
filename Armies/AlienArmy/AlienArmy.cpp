#include "AlienArmy.h"
#include <cstdlib>

void AlienArmy::addUnit(ArmyUnit *unit, int type) {
    switch (type) {
        case 4:
            Asoldiers.enqueue(static_cast<AlienSoldier *>(unit));
            break;
        case 5:
            //idx is the index of the monster in the array
            monsters.push_back(static_cast<AlienMonster *>(unit));
            break;
        case 6:
                drones.push_back(static_cast<AlienDrone *>(unit));
            break;
        default:
            break;
    }
}

ArmyUnit *AlienArmy::pickUnit(int type, bool droneFront) {
    AlienSoldier *soldier = nullptr;
    AlienDrone *drone = nullptr;
    int random{};
    if (!monsters.empty())
        random = rand() % monsters.size();

    switch (type) {
        case 4:
            if (Asoldiers.dequeue(soldier)) {
                return soldier;
            }
            break;
        case 5:
            if (monsters.empty()) {
                return nullptr;
            }
            return monsters[random];
            break;
        case 6:
            if (drones.is_empty()) {
                return nullptr;
            }
            if (droneFront) {
                drones.pop_front(drone);
                return drone;
            } else {
                drones.pop_back(drone);
                return drone;
            }
            break;
        default:
            return nullptr;
    }
    return nullptr;
}

void AlienArmy::print() const {
    Asoldiers.print();
    monsters.print();
    drones.print();
}

AlienArmy::~AlienArmy() {
    //Just for Phase1 to test memory leak in phase 2 not used in the final version
    //bcs temp list and killed list will conatain the pointers to the units
    //so we will delte them in the game class
    for (size_t i = 0; i < monsters.size(); i++) {
        if (monsters[i] != nullptr) {
            delete monsters[i];
            monsters[i] = nullptr;
        }
    }
    while (!Asoldiers.isEmpty()) {
        AlienSoldier *unit;
        if (Asoldiers.dequeue(unit)) {
            if (unit != nullptr) {
                delete unit;
                unit = nullptr;
            }
        }
    }
    while (!drones.is_empty()) {
        AlienDrone *unit;
        if (drones.pop_front(unit)) {
            if (unit != nullptr) {
                delete unit;
                unit = nullptr;
            }
        }
    }
}
