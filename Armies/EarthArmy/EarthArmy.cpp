#include "EarthArmy.h"

void EarthArmy::addUnit(ArmyUnit *unit, int type) {
    switch (type) {
        case 1:
            Esoldiers.enqueue(static_cast<EarthSoldier *>(unit));
            break;
        case 2:
            tanks.push(static_cast<EarthTank *>(unit));
            break;
        case 3:
            gunneries.push(static_cast<EarthGunnery *>(unit));
            break;
    }
}

ArmyUnit* EarthArmy::pickUnit(int type) {
    EarthTank *tank = nullptr;
    EarthSoldier *soldier = nullptr;
    EarthGunnery *gunnery = nullptr;

    switch (type) {
        case 1:
            if (Esoldiers.dequeue(soldier)) {
                return soldier;
            }
            break;
        case 2:
            if (tanks.pop(tank)) {
                return tank;
            }
            break;
        case 3:
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
