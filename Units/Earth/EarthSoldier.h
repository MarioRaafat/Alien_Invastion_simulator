#ifndef EARTHSOLIDER_H
#define EARTHSOLIDER_H

#include "../ArmyUnit.h"
#include "../Alien/AlienSoldier.h"

class EarthSoldier : public ArmyUnit {
    int count_UML; // counter for rounds in UML
    bool infected;
    bool immmune;

public:
    EarthSoldier(Game *game, int id, int t, int pw, int hl, int attc);
    void attack() override;

    int get_count_UML();
    void set_count_UML(int num);

    void set_infection(bool infec);
    bool get_infection();
    void set_immune(bool im);
    bool get_immune();

    int randomNumber(int min, int max);
    bool operator>(const EarthSoldier &other) const;
};
#endif //EARTHSOLIDER_H
