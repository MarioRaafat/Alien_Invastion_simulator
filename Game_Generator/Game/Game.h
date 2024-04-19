#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include "Generator.h"
#include "../../Armies/EarthArmy/EarthArmy.h"
#include "../../Armies/AlienArmy/AlienArmy.h"


using namespace std;

class Game {

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

    void randGen(); // I know that "تسمية " will not make you happy but fuck you that is its actually name in the document.
    void load_file();
    /*IMPORTANNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNT*/
    //u are a Fkin assHole marion actually I like it
    //But what is n??? es et write it dudeee!! it is so weird

    void phase1Test();
    EarthArmy &getEarthArmy();
    AlienArmy& getAlienArmy();
};


#endif //GAME_H