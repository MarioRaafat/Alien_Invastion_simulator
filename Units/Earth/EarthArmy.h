#ifndef ALIEN_INVASTION_SIMULATOR_EARTHARMY_H
#define ALIEN_INVASTION_SIMULATOR_EARTHARMY_H

#include "../../containers/LinkedQueue/LinkedQueue.h"
#include "../../containers/ArrayStack/ArrayStack.h"
#include "../../containers/PriorityQueue/PriorityQueue.h"

#include "EarthSoldier.h"
#include "EarthTank.h"
#include "EarthGunnery.h"
#include "fstream"
#include "../savers/SaverUnit.h"

class EarthArmy {

    struct CompareEarthGunnery {
        bool operator()(const EarthGunnery* lhs, const EarthGunnery* rhs) const {
            return *lhs > *rhs;
        }
    };

    LinkedQueue<EarthSoldier*> Esoldiers;
    LinkedQueue<SaverUnit*> savers;
    ArrayStack<EarthTank*> tanks;
    PriorityQueue<EarthGunnery*, CompareEarthGunnery> gunneries;
    size_t units_count() const;

    size_t killed_soldiers{};
    size_t killed_tanks{};
    size_t killed_gunneries{};

public:

    void addUnit(ArmyUnit *unit, unit_type type);
    ArmyUnit* pickUnit(unit_type type);
    ~EarthArmy();
    void print() const;
    void attack();
    void savers_attack();
    size_t soliders_count() const;
    size_t tanks_count() const;
    size_t gunneries_count() const;

    void updateKilledSoldiers(size_t killed_soldiers);
    void updateKilledTanks(size_t killed_tanks);
    void updateKilledGunneries(size_t killed_gunneries);
    size_t getKilledSoldiers() const;
    size_t getKilledTanks() const;
    size_t getKilledGunneries() const;
    size_t getTotalKilled() const;
    void print_stats(ofstream &out) const;
};




#endif //ALIEN_INVASTION_SIMULATOR_EARTHARMY_H
