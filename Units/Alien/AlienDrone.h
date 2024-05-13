#ifndef ALIEN_DRONE_H
#define ALIEN_DRONE_H


#include "../ArmyUnit.h"

class AlienDrone : public ArmyUnit {
public:
    AlienDrone(Game *game, int id, int t, int pw, int hl, int attc);
    void attack() override;
};

#endif //ALIEN_DRONE_H
