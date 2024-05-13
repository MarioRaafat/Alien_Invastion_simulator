#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include "Generator.h"
#include "Units/Earth/EarthArmy.h"
#include "Units/Alien/AlienArmy.h"
#include "Units/Healing/HealUnit.h"


using namespace std;

class Game {
public:
    Game();
    ~Game();

    void randGen();
    void load_file();
    void add_unit(ArmyUnit*, unit_type);
    void fight(int time_step);
    EarthArmy& getEarthArmy();
    AlienArmy& getAlienArmy();
    void add_to_killed_list(ArmyUnit* unit);
    void print();
    void heal();
    void count_rounds_in_UML();
    void play();
    void add_heal_unit(HealUnit* HU);
    bool is_interactive() const;
private:
    Generator* generator;
    EarthArmy Earmy;
    AlienArmy Aarmy;

    ArrayStack<HealUnit*> heal_list;
    PriorityQueue<ArmyUnit*> soldier_UML;
    LinkedQueue<ArmyUnit*> tank_UML;
    LinkedQueue<ArmyUnit *> temp_list;
    LinkedQueue<ArmyUnit *> killed_list;
    void add_Aunit(ArmyUnit* unit, unit_type type);
    void add_Eunit(ArmyUnit* unit, unit_type type);
    const string& winner() const;
    bool interactive_mode{};
    std::ofstream out_file;
};
#endif //GAME_H