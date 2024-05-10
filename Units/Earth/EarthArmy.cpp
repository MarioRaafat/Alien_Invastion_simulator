#include "EarthArmy.h"

void EarthArmy::attack(ArmyUnit *unit) {

}

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
    cout << Esoldiers.size() << " ES ";
    Esoldiers.print();
    cout << tanks.getTop() << " ET ";
    tanks.print();
    cout << gunneries.size() << " EG ";
    gunneries.print();
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
