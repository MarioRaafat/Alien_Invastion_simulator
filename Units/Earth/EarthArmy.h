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
    ArrayStack<EarthTank*> tanks;
    PriorityQueue<EarthGunnery*, CompareEarthGunnery> gunneries;
    LinkedQueue<SaverUnit*> savers;

    size_t units_count() const;
public:

    void addUnit(ArmyUnit *unit, unit_type type);
    ArmyUnit* pickUnit(unit_type type);
    ~EarthArmy();
    void print() const;
    void attack();
    void destroy_savers();
    size_t soliders_count() const;
    size_t tanks_count() const;
    size_t gunneries_count() const;

    size_t army_size() const;
};
#endif //ALIEN_INVASTION_SIMULATOR_EARTHARMY_H
