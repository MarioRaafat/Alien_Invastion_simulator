#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H


#include "../ArmyUnit.h"

class AlienMonster : public ArmyUnit {
public:
    AlienMonster(Game *game, int id, int t, int pw, int hl, int attc);
    void attack(int time_step) override;
};
#endif