#ifndef ALIEN_INVASTION_SIMULATOR_EARTHARMY_H
#define ALIEN_INVASTION_SIMULATOR_EARTHARMY_H

#include "../../containers/LinkedQueue/LinkedQueue.h"
#include "../../containers/ArrayStack/ArrayStack.h"
#include "../../containers/PriorityQueue/PriorityQueue.h"

#include "EarthSoldier.h"
#include "EarthTank.h"
#include "EarthGunnery.h"


class EarthArmy {
public:
    void addUnit(ArmyUnit *unit, unit_type type);
    ArmyUnit* pickUnit(unit_type type);
    ~EarthArmy();
    void print() const;
    void attack();
    size_t soliders_count() const;
private:
    struct CompareEarthGunnery {
        bool operator()(const EarthGunnery* lhs, const EarthGunnery* rhs) const {
            return *lhs > *rhs;
        }
    };

    LinkedQueue<EarthSoldier*> Esoldiers;
    ArrayStack<EarthTank*> tanks;
    PriorityQueue<EarthGunnery*, CompareEarthGunnery> gunneries;
    size_t units_count() const;
};




#endif //ALIEN_INVASTION_SIMULATOR_EARTHARMY_H
