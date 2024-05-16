#ifndef ALIEN_INVASTION_SIMULATOR_EARTHARMY_H
#define ALIEN_INVASTION_SIMULATOR_EARTHARMY_H

#include "../../containers/LinkedQueue/LinkedQueue.h"
#include "../../containers/ArrayStack/ArrayStack.h"
#include "../../containers/PriorityQueue/PriorityQueue.h"

#include "EarthSoldier.h"
#include "EarthTank.h"
#include "EarthGunnery.h"
#include "fstream"

class EarthArmy {

    /**
     * CompareEarthGunnery struct
     * to compare two EarthGunnery objects based on their power + health the derived formula
     * defing the call operator to be used in the priority queue
     */
    struct CompareEarthGunnery {
        bool operator()(const EarthGunnery* lhs, const EarthGunnery* rhs) const {
            return *lhs > *rhs;
        }
    };

    LinkedQueue<EarthSoldier*> Esoldiers;
    ArrayStack<EarthTank*> tanks;
    PriorityQueue<EarthGunnery*, CompareEarthGunnery> gunneries;
public:
    void addUnit(ArmyUnit *unit, unit_type type);
    ArmyUnit* pickUnit(unit_type type);
    ~EarthArmy();
    void print() const;
    void attack();
    size_t soliders_count() const;
    size_t army_size() const;
};
#endif //ALIEN_INVASTION_SIMULATOR_EARTHARMY_H
