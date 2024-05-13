#ifndef EARTHTANK_H
#define EARTHTANK_H

#include "../ArmyUnit.h"

class EarthTank : public ArmyUnit {
public:
    EarthTank(Game *game, int id, int t, int pw, int hl, int attc);
    void attack(int time_step) override;
};
#endif //EARTHTANK_H
