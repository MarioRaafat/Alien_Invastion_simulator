#ifndef ALIENSOLIDER_H
#define ALIENSOLIDER_H

#include "ArmyUnit.h"
#include "EarthSoldier.h"


class AlienSoldier :public ArmyUnit {
    public:
        AlienSoldier(int id, int t, int pw, int hl, int attc);
        void attack(ArmyUnit* soldier) override;
};


#endif //ALIENSOLIDER_H
