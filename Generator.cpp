#include "Generator.h"


int Generator::Ecount = 0;
int Generator::Acount = 0;



Generator::Generator(int min_Epw, int max_Epw, int min_Ehl, int max_Ehl, int min_Ecap, int max_Ecap, 
    int min_Apw, int max_Apw, int min_Ahl, int max_Ahl, int min_Acap, int max_Acap)

    : min_Epower(min_Epw), max_Epower(max_Epw), min_Ehealth(min_Ehl), max_Ehealth(max_Ehl), min_Ecapacity(min_Ecap), max_Ecapacity(max_Ecap),
    min_Apower(min_Epw), max_Apower(max_Epw), min_Ahealth(min_Ehl), max_Ahealth(max_Ehl), min_Acapacity(min_Ecap), max_Acapacity(max_Ecap)
{}

void Generator::Eunits_generator(int n, int es, int et, int eg, int prop) {
    int A = random_range(1, 100);
    if (A >= prop) {
        LinkedQueue<ArmyUnit*> Eq;
        for (int i = 0; i < n; i++) {
            int B = random_range(1, 100);

            if (B <= es) {
                EarthSoldier* earth_soldier = new EarthSoldier(Ecount++, current_time, 
                    random_range(min_Epower, max_Epower),
                    random_range(min_Ehealth, max_Ehealth),
                    random_range(min_Ecapacity, max_Ecapacity));

                Eq.enqueue(earth_soldier);
            }
            else if (B <= es + et) {
                // same for tank
            }
            else {
                // same for gunnery
            }
        }
    }
}
void Generator::Aunits_generator(int n, int as, int am, int ad, int prop) {
    int A = random_range(1, 100);
    if (A >= prop) {
        for (int i = 0; i < n; i++) {
            LinkedQueue<ArmyUnit*> Aq;
            int B = random_range(1, 100);

            if (B <= as) {

                AlienSoldier* alien_soldier = new AlienSoldier(2000 + Acount++, current_time,
                    random_range(min_Apower, max_Apower),
                    random_range(min_Ahealth, max_Ahealth),
                    random_range(min_Acapacity, max_Acapacity));

                Aq.enqueue(alien_soldier);
            }
            else if (B <= as + am) {
                // same for tank
            }
            else {
                // same for gunnery
            }
        }
    }
}

int Generator::random_range(int min, int max) {
    return rand() % (max - min + 1) + min;
}