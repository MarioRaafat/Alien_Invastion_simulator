#ifndef ALIEN_INVASTION_SIMULATOR_ALIENARMY_H
#define ALIEN_INVASTION_SIMULATOR_ALIENARMY_H

#include "AlienSoldier.h"
#include "AlienMonster.h"
#include "AlienDrone.h"

#include "../../containers/Array/Array.h"
#include "../../containers/Dequeue/Dequeue.h"
#include "../../containers/LinkedQueue/LinkedQueue.h"


class AlienArmy {
    public:
    void attack(ArmyUnit *unit);
    void addUnit(ArmyUnit *unit, int type);
    ArmyUnit* pickUnit(int type, bool droneFront = true);
    void print() const;
    ~AlienArmy();
private:
    LinkedQueue<AlienSoldier*> Asoldiers;
    Array<AlienMonster*> monsters;
    Dequeue<AlienDrone*> drones;
};


#endif //ALIEN_INVASTION_SIMULATOR_ALIENARMY_H

