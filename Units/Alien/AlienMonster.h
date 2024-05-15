#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H


#include "../ArmyUnit.h"

class AlienMonster : public ArmyUnit {

    int infection_prob;

public:

    AlienMonster(Game *game, int id, int t, int pw, int hl, int attc, int infec);
    void attack() override;
    static int randomNumber(int min, int max);
};
#endif