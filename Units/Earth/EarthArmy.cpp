#include "EarthArmy.h"
#include "Array.h"


void EarthArmy::addUnit(ArmyUnit *unit, unit_type type) {
    switch (type) {
        case earth_soldier:
            Esoldiers.enqueue(static_cast<EarthSoldier *>(unit));
            break;
        case earth_tank:
            tanks.push(static_cast<EarthTank *>(unit));
            break;
        case earth_gunnery:
            gunneries.push(static_cast<EarthGunnery *>(unit));
            break;
        default:
            break;
    }
}

ArmyUnit* EarthArmy::pickUnit(unit_type type) {
    EarthTank *tank = nullptr;
    EarthSoldier *soldier = nullptr;
    EarthGunnery *gunnery = nullptr;

    switch (type) {
        case earth_soldier:
            if (Esoldiers.dequeue(soldier)) {
                return soldier;
            }
            break;
        case earth_tank:
            if (tanks.pop(tank)) {
                return tank;
            }
            break;
        case earth_gunnery:
            if (gunneries.pop(gunnery)) {
                return gunnery;
            }
            break;
        default:
            return nullptr;
    }
    return nullptr;
}

void EarthArmy::print() const {
    cout << "====================== Earth Army Alive Units =====================\n";
    cout << Esoldiers.size() << " ES " << Esoldiers;
    cout << tanks.getTop() << " ET " << tanks;
    cout << gunneries.size() << " EG " << gunneries << "\n";
}

EarthArmy::~EarthArmy() {
    EarthSoldier *solider = {};
    EarthTank *tank = {};
    EarthGunnery *gunnery = {};

    while (Esoldiers.dequeue(solider)) {
            delete solider;
            solider = nullptr;
    }

    while (tanks.pop(tank)) {
        delete tank;
        tank = nullptr;
    }

    while (gunneries.pop(gunnery)) {
        delete gunnery;
        gunnery = nullptr;
    }
}

void EarthArmy::attack(int time_step) {
    ArmyUnit* attackers[3]{};
    attackers[0] = pickUnit(earth_soldier);
    attackers[1] = pickUnit(earth_tank);
    attackers[2] = pickUnit(earth_gunnery);

    for (const auto & attacker : attackers) {
        if (attacker) {
            attacker->attack(time_step);
            addUnit(attacker,(unit_type)attacker->getTypeId());
        }
    }
}

size_t EarthArmy::soliders_count() const {
   return Esoldiers.size();
}

size_t EarthArmy::units_count() const {
   return Esoldiers.size() + tanks.getTop() + gunneries.size();
}

size_t EarthArmy::gunneries_count() const {
    return gunneries.size();
}

size_t EarthArmy::tanks_count() const {
    return tanks.getTop();
}

size_t EarthArmy::getKilledSoldiers() const {
    return killed_soldiers;
}

size_t EarthArmy::getKilledTanks() const {
    return killed_tanks;
}

size_t EarthArmy::getKilledGunneries() const {
    return killed_gunneries;
}

void EarthArmy::updateKilledSoldiers(size_t killed_soldierss) {
    EarthArmy::killed_soldiers += killed_soldierss;
}

void EarthArmy::updateKilledTanks(size_t killed_tankss) {
    EarthArmy::killed_tanks += killed_tankss;
}

void EarthArmy::updateKilledGunneries(size_t killed_gunneriess) {
    EarthArmy::killed_gunneries += killed_gunneriess;
}

size_t EarthArmy::getTotalKilled() const {
    return killed_soldiers + killed_tanks + killed_gunneries;
}

void EarthArmy::print_stats(ofstream &out) const {
    out << "====================== Earth Army Stats =====================\n";
    out << "Total Killed Soldiers: " << killed_soldiers << "\n";
    out << "Total Killed Tanks: " << killed_tanks << "\n";
    out << "Total Killed Gunneries: " << killed_gunneries << "\n";
    out << "Total Killed Units: " << getTotalKilled() << "\n";
    out << "Earth Soliders destuced Soliders" << (killed_soldiers / soliders_count()) * 100 << "\n";
    out << "Earth Tanks destuced Tanks" << (killed_tanks / tanks_count()) * 100 << "\n";
    out << "Earth Gunneries destuced Gunneries" << (killed_gunneries / gunneries_count()) * 100 << "\n";
    out << "Perecentage of Killed Units: " << (getTotalKilled() / units_count()) * 100 << "\n";

}
