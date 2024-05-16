#ifndef SAVERSARMY_H
#define SAVERSARMY_H

#include "SaverUnit.h"
#include "../../containers/LinkedQueue/LinkedQueue.h"

class SaversArmy {

    LinkedQueue<SaverUnit*> savers;
    bool destroyed_before = false;

public:

    void addUnit(ArmyUnit *unit);
    ArmyUnit* pickUnit();
    void attack();

    bool is_destroyed() const;
    void print() const;
    void destroy_savers();
    int army_size() const;

    ~SaversArmy();
};



#endif //SAVERSARMY_H
