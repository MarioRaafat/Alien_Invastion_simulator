#ifndef ARMYUNIT_H
#define ARMYUNIT_H

enum unit_type {
    earth_solider = 1,
    earth_tank,
    earth_gunnery,
    alien_solider,
    alien_monster,
    alien_drone
};


class Game;
class ArmyUnit {

protected:

    int ID,
        Tj, // time joining
        power,
        health,
        attackCapacity;
    unit_type typeIdentifier; // 1 for ES , 2 for ET , 3 for EG ...etc
private:
    Game *game;
public:

    ArmyUnit(Game *game, int id, unit_type tyId, int t, int pw, int hl, int attC);
    ArmyUnit(const ArmyUnit &other) = default;
    virtual ~ArmyUnit() = default;

    int getID() const;
    int getTypeId() const;
    int getPower() const;
    void setHealth(int hl);
    int getHealth() const;
    int getAttackCapacity() const;

    void damage(ArmyUnit* enemy);
    virtual void print() const;
    virtual void attack(ArmyUnit* enemy) = 0;
    bool isDead() const;
};

#endif //ARMYUNIT_H