#include "EarthArmy.h"

void EarthArmy::addUnit(ArmyUnit *unit, unit_type type) {
    switch (type) {
        case earth_solider:
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
        case earth_solider:
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
    Esoldiers.print();
    tanks.print();
    gunneries.print();
}

EarthArmy::~EarthArmy() {
    while (!Esoldiers.isEmpty()) {
        EarthSoldier *unit;
        if (Esoldiers.dequeue(unit)) {
            if (unit != nullptr) {
                delete unit;
                unit = nullptr;
            }
        }
    }

    while (!tanks.isEmpty()) {
        EarthTank *unit;
        if (tanks.pop(unit)) {
            if (unit != nullptr) {
                delete unit;
                unit = nullptr;
            }
        }
    }

    while (!gunneries.empty()) {
        EarthGunnery *unit;
        if (gunneries.pop(unit)) {
            if (unit != nullptr) {
                delete unit;
                unit = nullptr;
            }
        }
    }
}
