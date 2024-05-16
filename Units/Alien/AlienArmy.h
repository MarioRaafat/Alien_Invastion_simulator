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
    void attack();
    void addUnit(ArmyUnit *unit, unit_type type, bool droneFront = true);
    ArmyUnit* pickUnit(unit_type type, bool droneFront = true, bool pickone = false);
    void print() const;
    ~AlienArmy();
    size_t soldiers_count() const;
    size_t army_size() const;
private:
    LinkedQueue<AlienSoldier*> Asoldiers;
    Array<AlienMonster*> monsters;
    Dequeue<AlienDrone*> drones;
};
#endif //ALIEN_INVASTION_SIMULATOR_ALIENARMY_H