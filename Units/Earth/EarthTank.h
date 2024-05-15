#ifndef EARTHTANK_H
#define EARTHTANK_H

#include "../ArmyUnit.h"

class EarthTank : public ArmyUnit {
    int count_UML; // counter for rounds in UML

public:
    EarthTank(Game *game, int id, int t, int pw, int hl, int attc);
    void attack() override;
    int get_count_UML() const;
    void set_count_UML(int num);
};
#endif //EARTHTANK_H
