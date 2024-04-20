#ifndef GENERATOR_H
#define GENERATOR_H


#include "Units/ArmyUnit.h"
class Generator {

    static int Ecount, Acount;  // earth and aliens units number
    static int current_time;

    int N, ES, ET, EG, AS, AM, AD, probability;
    // from input file
    int min_Epower,
            max_Epower,
            min_Ehealth,
            max_Ehealth,
            min_Ecapacity,
            max_Ecapacity;

    int min_Apower,
            max_Apower,
            min_Ahealth,
            max_Ahealth,
            min_Acapacity,
            max_Acapacity;

public:
    // sorry
    Generator(int n, int es, int et, int eg, int as, int am, int ad, int prob,
              int min_Epw, int max_Epw,
              int min_Ehl, int max_Ehl,
              int min_Ecap, int max_Ecap,
              int min_Apw, int	max_Apw,
              int min_Ahl, int max_Ahl,
              int min_Acap, int max_Acap);

    void generate(Game *game);
    int random_range(int min, int max);
};


#endif // !GENERATOR_H