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
        case saver_unit:
            savers.enqueue(static_cast<SaverUnit*>(unit));
            break;
        default:
            break;
    }
}

ArmyUnit* EarthArmy::pickUnit(unit_type type) {
    EarthTank *tank = nullptr;
    EarthSoldier *soldier = nullptr;
    EarthGunnery *gunnery = nullptr;
    SaverUnit* saver = nullptr;

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
        case saver_unit:
            if (savers.dequeue(saver)) {
                return saver;
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
    cout << savers.size() << " Saver Units " << savers << "\n";
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

    while (!savers.isEmpty()) {
        SaverUnit* saver = {};
        if (savers.dequeue(saver)) {
            delete saver;
            saver = nullptr;
        }
    }
}

void EarthArmy::attack() {
    ArmyUnit* attackers[4]{};
    attackers[0] = pickUnit(earth_soldier);
    attackers[1] = pickUnit(earth_tank);
    attackers[2] = pickUnit(earth_gunnery);
    attackers[3] = pickUnit(saver_unit);

    for (const auto& attacker : attackers) {
        if (attacker) {
            attacker->attack();
            addUnit(attacker, attacker->getTypeId());
        }
    }
}

void EarthArmy::destroy_savers() {
    SaverUnit* saver = {};
    while (savers.dequeue(saver)) {
        delete saver;
        saver = nullptr;
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

size_t EarthArmy::army_size() const {
   return Esoldiers.size() + tanks.getTop() + gunneries.size();
}

