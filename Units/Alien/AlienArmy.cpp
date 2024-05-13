#include "AlienArmy.h"
#include <cstdlib>
#include <random>


void AlienArmy::addUnit(ArmyUnit *unit, unit_type type) {
    switch (type) {
        case alien_soldier:
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

    while (drones.pop_front(drone)) {
        delete drone;
        drone = nullptr;
    }
}

 int AlienArmy::randomNumber(int min, int max) {
     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void AlienArmy::attack(int time_step) {
    ArmyUnit* attackers[4]{};
    attackers[0] = pickUnit(alien_soldier);
    attackers[1] = pickUnit(alien_drone, true);
    attackers[2] = pickUnit(alien_drone, false);
    attackers[3] = pickUnit(alien_monster);

    for (const auto & attacker : attackers) {
        if (attacker) {
            attacker->attack(time_step);
            addUnit(attacker,(unit_type)attacker->getTypeId());
        }
    }
}

size_t AlienArmy::soldiers_count() const {
    return Asoldiers.size();
}

size_t AlienArmy::units_count() const {
   return Asoldiers.size() + monsters.size() + drones.size();
}

size_t AlienArmy::monsters_count() const {
    return monsters.size();
}

size_t AlienArmy::drones_count() const {
    return drones.size();
}

void AlienArmy::updateKilledDrones(size_t killed_droness) {
    this->killed_drones += killed_droness;
}

void AlienArmy::updateKilledMonsters(size_t killed_monsterss) {
    this->killed_monsters += killed_monsterss;
}

void AlienArmy::updateKilledSoldiers(size_t killed_soldierss) {
    this->killed_soldiers += killed_soldierss;
}

size_t AlienArmy::getKilledDrones() const {
    return killed_drones;
}

size_t AlienArmy::getKilledMonsters() const {
    return killed_monsters;
}

size_t AlienArmy::getKilledSoldiers() const {
    return killed_soldiers;
}

size_t AlienArmy::total_killed() const {
    return killed_drones + killed_monsters + killed_soldiers;
}


void AlienArmy::print_stats(ofstream &out) const {
    out << "====================== Alien Army Stats =====================\n";
    out << "Total Killed Soldiers: " << killed_soldiers << endl;
    out << "Total Killed Monsters: " << killed_monsters << endl;
    out << "Total Killed Drones: " << killed_drones << endl;
    out << "Total Killed Units: " << total_killed() << endl;
    out << "Alien Soliders destuced Soliders" << (killed_soldiers / soldiers_count()) * 100 << endl;
    out << "Alien Monsters destuced Monsters" << (killed_monsters / monsters_count()) * 100 << endl;
    out << "Alien Drones destuced Drones" << (killed_drones / drones_count()) * 100 << endl;
    out << "Alien Total destuced Units" << (total_killed() / units_count()) * 100 << endl;
}
