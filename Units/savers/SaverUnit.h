//
// Created by mario on 5/15/2024.
//

#ifndef SAVERUNIT_H
#define SAVERUNIT_H
#include "../ArmyUnit.h"


class SaverUnit : public ArmyUnit {

public:

    SaverUnit(Game *game, int id, int t, int pw, int hl, int attc);
    void attack() override;
};



#endif //SAVERUNIT_H
