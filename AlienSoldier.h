#ifndef ALIEN_INVASTION_SIMULATOR_ALIENSOLDIER_H
#define ALIEN_INVASTION_SIMULATOR_ALIENSOLDIER_H
#include "ArmyUnit.h"
#include "EarthSoldier.h"


class AlienSoldier :public ArmyUnit {
    public:
        AlienSoldier(int id, int t, int pw, int hl, int attc);
        void attack(ArmyUnit* soldier) override;
};


#endif //ALIEN_INVASTION_SIMULATOR_ALIENSOLDIER_H
