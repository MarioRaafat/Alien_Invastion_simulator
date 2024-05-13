#ifndef ALIEN_SOLIDER_H
#define ALIEN_SOLIDER_H


#include "../ArmyUnit.h"

class AlienSoldier : public ArmyUnit {
public:
    AlienSoldier(Game *game, int id, int t, int pw, int hl, int attc);
    void attack(int time_step) override;
};

#endif //ALIEN_SOLIDER_H
