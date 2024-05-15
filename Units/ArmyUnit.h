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
    saver_unit,
    heal_unit
};


class Game;
class ArmyUnit {

protected:
    int ID,
        Tj, // time joining
        Ta = -1 ,
        Td = -1,
        power,
        health,
        original_health,
        attackCapacity;
    unit_type typeIdentifier; // 1 for ES , 2 for ET , 3 for EG ...etc
    Game *game;

public:

    ArmyUnit(Game *game, int id, unit_type tyId, int tj, int pw, int hl, int attC);
    virtual ~ArmyUnit() = default;

    int getID() const;
    unit_type getTypeId() const;
    int getPower() const;
    void setHealth(int hl);
    int getHealth() const;
    int getOriginalHealth() const;
    int getAttackCapacity() const;

    void damage(ArmyUnit* enemy);
    virtual void print() const;
    virtual void attack() = 0;
    bool isDead() const;
    int getTa() const;
    int getTj() const;
    int getTd() const;
    void setTa(int time);
    void setTd(int time);

    int getDf() const;
    int getDd() const;
    int getDBb() const;
    bool is_dimmised() const;
    bool is_attacked() const;

    friend std::ostream &operator<<(std::ostream &os, const ArmyUnit &unit);
};

#endif //ARMYUNIT_H