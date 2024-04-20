#include "AlienArmy.h"
#include <cstdlib>
#include <random>


void AlienArmy::addUnit(ArmyUnit *unit, unit_type type) {
    switch (type) {
        case alien_solider:
            Asoldiers.enqueue(static_cast<AlienSoldier *>(unit));
            break;
        case alien_monster:
            monsters.push_back(static_cast<AlienMonster *>(unit));
            break;
        case alien_drone:
                drones.push_back(static_cast<AlienDrone *>(unit));
            break;
        default:
            break;
    }
}

ArmyUnit *AlienArmy::pickUnit(unit_type type, bool droneFront) {
    AlienSoldier *soldier = nullptr;
    AlienDrone *drone = nullptr;
    AlienMonster *monster = nullptr;
    int random = 0;

    if (!monsters.empty()) {
        random = randomNumber(0, static_cast<int>(monsters.size()) - 1);
    }

    switch (type) {
        case alien_solider:
            if (Asoldiers.dequeue(soldier)) {
                return soldier;
            }
            break;
        case alien_monster:
            if (monsters.empty()) {
                return nullptr;
            }
            monster = monsters[random];
            monsters[random] = nullptr;
            return monster;
        case alien_drone:
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

 int AlienArmy::randomNumber(int min, int max) {
     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
