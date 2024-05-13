#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H


#include "../ArmyUnit.h"

class AlienMonster : public ArmyUnit {
public:
    void attack() override;
    AlienMonster(Game *game, int id, int t, int pw, int hl, int attc);
};
#endif