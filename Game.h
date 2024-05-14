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
    int get_time() const;
    void add_unit(ArmyUnit*, unit_type);
    ArmyUnit* pick_unit(unit_type type);
    void add_to_killed_list(ArmyUnit* unit);


    void heal();
    void count_rounds_in_UML();
    void add_heal_unit(HealUnit* HU);

    void add_to_soldier_UML(EarthSoldier* damaged_unit);
    void add_to_tank_UML(EarthTank* damaged_unit);
    EarthSoldier* pick_from_soldier_UML();
    EarthTank* pick_from_tank_UML();

    void play();
    void fight();

    // special cases
    bool which_tank_attack(); // to know if the tanks need to attack alien soldier ir not
    bool stop_attacking_soldiers();

    bool is_interactive() const;
    void print();

private:
    struct CompareEarthSoldier {
        bool operator()(const EarthSoldier* lhs, const EarthSoldier* rhs) const {
            return *lhs > *rhs;
        }
    };

    Generator* generator;
    EarthArmy Earmy;
    AlienArmy Aarmy;
    ArrayStack<HealUnit*> heal_list;
    PriorityQueue<EarthSoldier*, CompareEarthSoldier> soldier_UML;
    LinkedQueue<EarthTank*> tank_UML;
    LinkedQueue<ArmyUnit *> temp_list;
    LinkedQueue<ArmyUnit *> killed_list;


    int curr_time_step;
//    std::ofstream out_file;
    bool interactive_mode{};


    const string& winner() const;
};

#endif //GAME_H