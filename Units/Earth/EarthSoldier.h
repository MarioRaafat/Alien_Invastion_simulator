#ifndef EARTHSOLIDER_H
#define EARTHSOLIDER_H

#include "../ArmyUnit.h"
#include "../Alien/AlienSoldier.h"

class EarthSoldier : public ArmyUnit {
    public:
        EarthSoldier(Game *game, int id, int t, int pw, int hl, int attc);
        virtual void attack(ArmyUnit * enemy);
};
#endif //EARTHSOLIDER_H
