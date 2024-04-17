#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include "Generator.h"
#include "Units/Earth/EarthUnits.h"
#include "Units/Alien/AlienUnits.h"

using namespace std;

class Game {

    Generator* generator;
    EarthUnits Eunits;
    AlienUnits Aunits;

    int n, es, et, eg, as, am, ad, prop;

public:
    Game();
    void randGen(); // I know that "تسمية " will not make you happy but fuck you that is its actually name in the document.
    void load_file();
};


#endif //GAME_H