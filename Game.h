#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include "Generator.h"
#include "Units/Earth/EarthArmy.h"
#include "Units/Alien/AlienArmy.h"


using namespace std;

class Game {
private:
    Generator* generator;
    EarthArmy Earmy;
    AlienArmy Aarmy;
    LinkedQueue<ArmyUnit *> temp_list;
    LinkedQueue<ArmyUnit *> killed_list;

public:
    Game();
    ~Game();

    void randGen();
    void load_file();

    void add_Aunit(ArmyUnit* unit, unit_type type);
    void add_Eunit(ArmyUnit* unit, unit_type type);

    void earth_attack_aliens();
    void aliens_attack_earth();

    void Esolider_attack();
    void Asolider_attack();
    void phase1Test();
};
#endif //GAME_H