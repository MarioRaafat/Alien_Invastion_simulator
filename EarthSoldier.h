#ifndef ALIEN_INVASTION_SIMULATOR_EARTHSOLDIER_H
#define ALIEN_INVASTION_SIMULATOR_EARTHSOLDIER_H

#include "ArmyUnit.h"
#include "AlienSoldier.h"


class EarthSoldier : public ArmyUnit {
    public:
        EarthSoldier(int id, int t, int pw, int hl, int attc);
        void attack(ArmyUnit * solider) override;
};


#endif //ALIEN_INVASTION_SIMULATOR_EARTHSOLDIER_H
