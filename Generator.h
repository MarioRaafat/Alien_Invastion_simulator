#ifndef GENERATOR_H
#define GENERATOR_H


#include "Units/ArmyUnit.h"
class Generator {

    static int Ecount, Acount, Scount, HealNum;  // earth and aliens units number

    int N, ES, ET, EG, AS, AM, AD, HU, probability, infection_prob;
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
    Generator(int n, int es, int et, int eg, int as, int am, int ad, int hu, int prob, int infec,
              int min_Epw, int max_Epw,
              int min_Ehl, int max_Ehl,
              int min_Ecap, int max_Ecap,
              int min_Apw, int	max_Apw,
              int min_Ahl, int max_Ahl,
              int min_Acap, int max_Acap);

    void generate(Game *game) const;
    static  int random_range(int min, int max);
    //geetrs for Ecount and Acount and Scount
    static int get_Ecount();
    static int get_Acount();
    static int get_Scount();
};


#endif // !GENERATOR_H