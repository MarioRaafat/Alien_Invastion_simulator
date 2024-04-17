#ifndef EARTHSOLIDER_H
#define EARTHSOLIDER_H

#include "../ArmyUnit.h"
#include "../Alien/AlienSoldier.h"


class EarthSoldier : public ArmyUnit {
    public:
        EarthSoldier(int id, int t, int pw, int hl, int attc);
        void attack(ArmyUnit * solider) override;
};


#endif //EARTHSOLIDER_H
