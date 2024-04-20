#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include "Generator.h"
#include "../../Units/Earth/EarthArmy.h"
#include "../../Units/Alien/AlienArmy.h"


using namespace std;

class Game {
private:
    Generator* generator;
    EarthArmy Earmy;
    AlienArmy Aarmy;
    Array<ArmyUnit*> temp_list;
    Array<ArmyUnit*> killed_list;


//    EarthUnits Eunits;
//    AlienUnits Aunits;
    int n, es, et, eg, as, am, ad, prop;

public:
    Game();
    ~Game();
    void randGen();
    void load_file();

    void phase1Test();
    EarthArmy &getEarthArmy();
    AlienArmy& getAlienArmy();
};
#endif //GAME_H