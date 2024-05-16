#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H


#include "../ArmyUnit.h"

class AlienMonster : public ArmyUnit {
public:
    AlienMonster(Game *game, int id, int t, int pw, int hl, int attc, int infec);
    void attack() override;
private:
    int infection_prob;
    static int randomNum(int min, int max);
};
#endif