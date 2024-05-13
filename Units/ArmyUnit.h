#ifndef ARMYUNIT_H
#define ARMYUNIT_H
#include <iostream>

enum unit_type {
    earth_soldier = 1,
    earth_tank,
    earth_gunnery,
    alien_soldier,
    alien_monster,
    alien_drone,
    heal_unit
};


class Game;
class ArmyUnit {

protected:
    int ID,
        Tj, // time joining
        power,
        health,
        original_health,
        attackCapacity,
        count_UML; // counter for rounds in UML
    unit_type typeIdentifier; // 1 for ES , 2 for ET , 3 for EG ...etc
    Game *game;
public:
    ArmyUnit(Game *game, int id, unit_type tyId, int t, int pw, int hl, int attC);
    virtual ~ArmyUnit() = default;

    int getID() const;
    int getTypeId() const;
    int getPower() const;
    void setHealth(int hl);
    int getHealth() const;
    int getOriginalHealth();
    int getAttackCapacity() const;
    int get_count_UML();
    void set_count_UML(int num);

    void damage(ArmyUnit* enemy);
    virtual void print() const;
    virtual void attack() = 0;
    bool isDead() const;
    friend std::ostream &operator<<(std::ostream &os, const ArmyUnit &unit);
};

#endif //ARMYUNIT_H