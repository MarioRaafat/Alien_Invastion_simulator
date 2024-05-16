#ifndef ALIEN_INVASTION_SIMULATOR_ALIENARMY_H
#define ALIEN_INVASTION_SIMULATOR_ALIENARMY_H

#include "AlienSoldier.h"
#include "AlienMonster.h"
#include "AlienDrone.h"

#include "../../containers/Array/Array.h"
#include "../../containers/Dequeue/Dequeue.h"
#include "../../containers/LinkedQueue/LinkedQueue.h"
#include "fstream"


class AlienArmy {
    public:
    void attack();
    void addUnit(ArmyUnit *unit, unit_type type, bool droneFront = true);
    ArmyUnit* pickUnit(unit_type type, bool droneFront = true, bool pickone = false);
    void print() const;
    ~AlienArmy();
    size_t soldiers_count() const;
    size_t monsters_count() const;
    size_t drones_count() const;
    void updateKilledSoldiers(size_t killed_soldiers);
    void updateKilledMonsters(size_t killed_monsters);
    void updateKilledDrones(size_t killed_drones);
    size_t getKilledSoldiers() const;
    size_t getKilledMonsters() const;
    size_t getKilledDrones() const;
    size_t units_count() const;

private:
    LinkedQueue<AlienSoldier*> Asoldiers;
    Array<AlienMonster*> monsters;
    Dequeue<AlienDrone*> drones;
    static int randomNumber(int min, int max);
    size_t killed_soldiers{};
    size_t killed_monsters{};
    size_t killed_drones{};

    size_t army_count() const;
};
#endif //ALIEN_INVASTION_SIMULATOR_ALIENARMY_H