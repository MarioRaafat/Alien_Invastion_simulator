#ifndef EARTHSOLIDER_H
#define EARTHSOLIDER_H

#include "../ArmyUnit.h"
#include "../Alien/AlienSoldier.h"

class EarthSoldier : public ArmyUnit {
    int count_UML; // counter for rounds in UML

    public:
        EarthSoldier(Game *game, int id, int t, int pw, int hl, int attc);
        void attack() override;
        int get_count_UML();
        void set_count_UML(int num);
};
#endif //EARTHSOLIDER_H
