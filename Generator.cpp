#include "Generator.h"
#include "Units/Earth/EarthSoldier.h"
#include "Units/Earth/EarthTank.h"
#include "Units/Earth/EarthGunnery.h"
#include "Game.h"
#include <random>

#include "Units/Alien/AlienSoldier.h"

int Generator::Ecount = 1;
int Generator::Acount = 1;
int Generator::current_time = 0;



Generator::Generator(int min_Epw, int max_Epw, int min_Ehl, int max_Ehl, int min_Ecap, int max_Ecap,
                     int min_Apw, int max_Apw, int min_Ahl, int max_Ahl, int min_Acap, int max_Acap)

        : min_Epower(min_Epw), max_Epower(max_Epw), min_Ehealth(min_Ehl), max_Ehealth(max_Ehl), min_Ecapacity(min_Ecap), max_Ecapacity(max_Ecap),
          min_Apower(min_Apw), max_Apower(max_Apw), min_Ahealth(min_Ahl), max_Ahealth(max_Ahl), min_Acapacity(min_Acap), max_Acapacity(max_Acap)
{}

void Generator::Eunits_generator(Game *game, int n, int es, int et, int eg, int prop) {

    int A = random_range(1, 100);
    if (A >= prop) {
        for (int i = 0; i < n; i++) {
            int B = random_range(1, 100);
            int power = random_range(min_Epower, max_Epower);
            int health = random_range(min_Ehealth, max_Ehealth);
            int capacity = random_range(min_Ecapacity, max_Ecapacity);

            if (B <= es) {
                auto Esoldier = new EarthSoldier(game, Ecount++, current_time, power, health, capacity);
                game->add_Eunit(Esoldier, earth_solider);
            }
            else if (B <= es + et) {
                auto Etank = new EarthTank(game,Ecount++, current_time, power, health, capacity);
                game->add_Eunit(Etank, earth_tank);
            }
            else {
                auto Egunnery = new EarthGunnery(game, Ecount++, current_time, power, health, capacity);
                game->add_Eunit(Egunnery, earth_gunnery);
            }
        }
    }
}
void Generator::Aunits_generator(Game *game, int n, int as, int am, int ad, int prop) {
    int A = random_range(1, 100);
    if (A >= prop) {
        for (int i = 0; i < n; i++) {
            int B = random_range(1, 100);
            int power = random_range(min_Apower, max_Apower);
            int health = random_range(min_Ahealth, max_Ahealth);
            int capacity = random_range(min_Acapacity, max_Acapacity);

            if (B <= as) {

                auto Asoldier = new AlienSoldier(game, 2000 + Acount++, current_time, power, health, capacity);
                game->add_Aunit(Asoldier, alien_solider);
            }
            else if (B <= as + am) {
                auto Amonster = new AlienMonster(game, 2000 + Acount++, current_time, power, health, capacity);
                game->add_Aunit(Amonster, alien_monster);
            }
            else {
                auto Adrone = new AlienDrone(game, 2000 + Acount++, current_time, power, health, capacity);
                game->add_Aunit(Adrone, alien_drone);
            }
        }
    }
    current_time++;
}

int Generator::random_range(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
