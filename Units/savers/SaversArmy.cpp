#include "SaversArmy.h"

void SaversArmy::addUnit(ArmyUnit *unit) {
    savers.enqueue(static_cast<SaverUnit*>(unit));
}

ArmyUnit * SaversArmy::pickUnit() {
    SaverUnit* saver = nullptr;
    if (savers.dequeue(saver)) {
        return saver;
    }
    return nullptr;
}

void SaversArmy::attack() {
    ArmyUnit* saver{};
    saver = pickUnit();
    if (saver) {
        saver->attack();
        addUnit(saver);
    }
}

bool SaversArmy::is_destroyed() const {
    return destroyed_before;
}

void SaversArmy::print() const{
    cout << "======================= Saver Army Alive Units =====================\n";
    cout << savers.size() << " Saver Units " << savers << "\n";
}

void SaversArmy::destroy_savers() {
    SaverUnit* saver = {};
    while (savers.dequeue(saver)) {
        delete saver;
        saver = nullptr;
    }
    destroyed_before = true;
}

int SaversArmy::army_size() const{
    return savers.size();
}

SaversArmy::~SaversArmy() {
    destroy_savers();
}
