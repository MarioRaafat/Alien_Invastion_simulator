#ifndef EARTHGUNNERY_H
#define EARTHGUNNERY_H

#include "../ArmyUnit.h"
#include "../Alien/AlienDrone.h"
#include "../Alien/AlienMonster.h"


class EarthGunnery : public ArmyUnit {
public:
    EarthGunnery(int id, int t, int pw, int hl, int attc);
    void attack(ArmyUnit* solider) override;
};


#endif //EARTHGUNNERY_H
