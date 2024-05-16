#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include "Generator.h"
#include "Units/Earth/EarthArmy.h"
#include "Units/Alien/AlienArmy.h"
#include "Units/Healing/HealUnit.h"
#include "Units/savers/SaversArmy.h"


using namespace std;

class Game {

    //Compartor Strcut for the priority queue for EarthSoldier
    struct CompareEarthSoldier {
        bool operator()(const EarthSoldier* lhs, const EarthSoldier* rhs) const {
            return *lhs > *rhs;
        }
    };
    ArrayStack<HealUnit*> heal_list;
    PriorityQueue<EarthSoldier*, CompareEarthSoldier> soldier_UML;
    LinkedQueue<EarthTank*> tank_UML;
    LinkedQueue<ArmyUnit *> killed_list;
    EarthArmy Earmy;
    AlienArmy Aarmy;
    SaversArmy Sarmy;
    Generator* generator;

    double earth_avg_df{};
    double earth_avg_dd{};
    double earth_avg_DBb{};
    double alien_avg_df{};
    double alien_avg_dd{};
    double alien_avg_DBb{};
    double saver_ave_df{};
    double saver_ave_dd{};
    double saver_ave_DBb{};

    int curr_time_step;
    int threshold;
    int infection_number, immune_number, total_infected{};
    bool interactive_mode{};
    bool saver_mode;

    int killed_earth_soldiers{}, killed_earth_tanks{}, killed_earth_gunneries{};
    int killed_aliens_drones{}, killed_aliens_soldiers{}, killed_aliens_monsters{}, killed_saver_units{};
    int total_killed_earth() const;
    int total_killed_aliens() const;
    int total_killed_savers() const;
    const string& winner() const;
    void print_earth_stats(ofstream& out_file) const;
    void print_saver_satats(ofstream& out_file) const;
    void print_alien_stats(ofstream& out_file) const;
    void print_stats(ofstream& out_file) const;
    void incremenat_avg_to_print(ArmyUnit *unit);
    void print() const;
    void randGen();
    void load_file();
    void heal();
    void count_rounds_in_UML();//Counts rounts from 1 up to 10 and then remove it from the UML
    void fight();
public:
    Game();
    ~Game();

    void play();

    void add_unit(ArmyUnit*, unit_type, bool droneFront = true);
    ArmyUnit* pick_unit(unit_type type, bool droneFront = true, bool pickone = false);
    void add_to_killed_list(ArmyUnit* unit);
    void add_heal_unit(HealUnit* HU);
    void add_to_soldier_UML(EarthSoldier* damaged_unit);
    void add_to_tank_UML(EarthTank* damaged_unit);
    EarthSoldier* pick_from_soldier_UML();
    EarthTank* pick_from_tank_UML();

    bool which_tank_attack() const; // to know if the tanks need to attack alien soldier ir not
    bool stop_attacking_soldiers() const;
    bool check_savers_mode();
    bool is_interactive() const;
    int get_time() const;
    int total_earth_soldiers_count() const;
    void increment_infection_number();
    void decrement_infection_number();
    void increment_immune_number();
};
#endif //GAME_H