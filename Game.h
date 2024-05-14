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
    ~Game(); // ---------> commented

    void randGen();
    void load_file();
    int get_time();
    void add_unit(ArmyUnit*, unit_type);
    ArmyUnit* pick_unit(unit_type type);
    void add_to_killed_list(ArmyUnit* unit);

    // AlienArmy& getAlienArmy();
    // EarthArmy& getEarthArmy();

    void heal();
    void count_rounds_in_UML();
    void add_heal_unit(HealUnit* HU);

    void add_to_soldier_UML(EarthSoldier* damaged_unit);
    void add_to_tank_UML(EarthTank* damaged_unit);
    EarthSoldier* pick_from_soldier_UML();
    EarthTank* pick_from_tank_UML();

    void play();
    void fight(int time_step);

    // special cases
    bool which_tank_attack(); // to know if the tanks need to attack alien soldier ir not
    bool stop_attacking_soldiers();

    bool is_interactive() const;
    void print();

private:

    int curr_time_step;
    Generator* generator;
    EarthArmy Earmy;
    AlienArmy Aarmy;

    ArrayStack<HealUnit*> heal_list;
    PriorityQueue<EarthSoldier*> soldier_UML;
    LinkedQueue<EarthTank*> tank_UML;

    LinkedQueue<ArmyUnit *> temp_list;
    LinkedQueue<ArmyUnit *> killed_list;

    void add_Aunit(ArmyUnit* unit, unit_type type);
    void add_Eunit(ArmyUnit* unit, unit_type type);

    const string& winner() const;
    bool interactive_mode{};
    std::ofstream out_file;
};

#endif //GAME_H