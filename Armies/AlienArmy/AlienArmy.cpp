#include "AlienArmy.h"
#include <cstdlib>
#include <random>


void AlienArmy::addUnit(ArmyUnit *unit, int type) {
    switch (type) {
        case 4:
            Asoldiers.enqueue(static_cast<AlienSoldier *>(unit));
            break;
        case 5:
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
    AlienMonster *monster = nullptr;
    int random = 0;

    if (!monsters.empty()) {
        random = randomNumber(0, static_cast<int>(monsters.size()) - 1);
    }

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
            monster = monsters[random];
            monsters[random] = nullptr;
            return monster;
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
