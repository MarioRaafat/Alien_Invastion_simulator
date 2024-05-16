#ifndef EARTHSOLIDER_H
#define EARTHSOLIDER_H

#include "../ArmyUnit.h"
#include "../Alien/AlienSoldier.h"
#include <iostream>

class EarthSoldier : public ArmyUnit {
    int count_UML; // counter for rounds in UML
    bool infected;
    bool immmune;

public:
    EarthSoldier(Game *game, int id, int t, int pw, int hl, int attc);
    void attack() override;

    int get_count_UML() const;
    void set_count_UML(int num);

    void set_infection(bool infec);
    bool get_infection() const;
    void set_immune(bool im);
    bool get_immune() const;
    bool is_healed() const;
    bool should_be_healed() const;

    static int randomNumber(int min, int max);
    bool operator>(const EarthSoldier &other) const;
    friend std::ostream &operator<<(std::ostream &os, const EarthSoldier &soldier);
};
#endif //EARTHSOLIDER_H
