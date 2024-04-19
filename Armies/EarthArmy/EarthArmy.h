#ifndef ALIEN_INVASTION_SIMULATOR_EARTHARMY_H
#define ALIEN_INVASTION_SIMULATOR_EARTHARMY_H

#include "LinkedQueue.h"
#include "ArrayStack.h"
#include "PriorityQueue.h"

#include "EarthSoldier.h"
#include "EarthTank.h"
#include "EarthGunnery.h"


class EarthArmy {
public:
    void attack(ArmyUnit *unit);
    void addUnit(ArmyUnit *unit, int type);
    ArmyUnit* pickUnit(int type);
    ~EarthArmy();
    void print() const;

private:
    struct CompareEarthGunnery {
        bool operator()(const EarthGunnery* lhs, const EarthGunnery* rhs) const {
            return *lhs > *rhs;
        }
    };

    LinkedQueue<EarthSoldier*> Esoldiers;
    ArrayStack<EarthTank*> tanks;
    PriorityQueue<EarthGunnery*, CompareEarthGunnery> gunneries;

};




#endif //ALIEN_INVASTION_SIMULATOR_EARTHARMY_H
