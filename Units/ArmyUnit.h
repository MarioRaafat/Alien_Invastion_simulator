#ifndef ARMYUNIT_H
#define ARMYUNIT_H


class Game;
class ArmyUnit {

protected:

    int ID,
        typeIdentifier, // 1 for ES , 2 for ET , 3 for EG ...etc
        Tj, // time joining
        power,
        health,
        attackCapacity;
private:
    Game *game;
public:

    ArmyUnit(Game *game, int id, int tyId, int t, int pw, int hl, int attC);
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