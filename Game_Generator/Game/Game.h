#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include "Generator.h"
#include "../../Armies/EarthArmy/EarthArmy.h"
#include "../../Armies/AlienArmy/AlienArmy.h"


using namespace std;

class Game {
private:
    Generator* generator;
    EarthArmy Earmy;
    AlienArmy Aarmy;
    LinkedQueue<ArmyUnit *> temp_list;
    LinkedQueue<ArmyUnit *> killed_list;


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