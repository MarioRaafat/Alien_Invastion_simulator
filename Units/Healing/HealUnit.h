//
// Created by mario on 5/10/2024.
//

#ifndef HEALUNIT_H
#define HEALUNIT_H

#include "../ArmyUnit.h"


class HealUnit : public ArmyUnit{
public:
    HealUnit(Game *game, int id, int t, int pw, int hl, int attC);
    void attack() override;
    void heal(ArmyUnit *damaged_unit);
};



#endif //HEALUNIT_H
