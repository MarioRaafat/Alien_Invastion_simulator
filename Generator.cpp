#include "Generator.h"
#include "Units/Earth/EarthSoldier.h"
#include "Units/Earth/EarthTank.h"
#include "Units/Earth/EarthGunnery.h"
#include "Game.h"
#include <random>

#include "Units/Alien/AlienSoldier.h"

int Generator::Ecount = 1;
int Generator::Acount = 1;
int Generator::HealNum = 1;



Generator::Generator(int n, int es, int et, int eg, int as, int am, int ad, int prob, int infec,
                     int min_Epw, int max_Epw, int min_Ehl, int max_Ehl, int min_Ecap, int max_Ecap,
                     int min_Apw, int max_Apw, int min_Ahl, int max_Ahl, int min_Acap, int max_Acap)

        : N(n), ES(es), ET(et), EG(eg), AS(as), AM(am), AD(ad), probability{prob}, infection_prob(infec),
          min_Epower(min_Epw), max_Epower(max_Epw), min_Ehealth(min_Ehl), max_Ehealth(max_Ehl), min_Ecapacity(min_Ecap), max_Ecapacity(max_Ecap),
          min_Apower(min_Apw), max_Apower(max_Apw), min_Ahealth(min_Ahl), max_Ahealth(max_Ahl), min_Acapacity(min_Acap), max_Acapacity(max_Acap)
{}

void Generator::generate(Game *game) {
    int A = random_range(1, 100);
    int healing_probability = random_range(1, 100);

    if (A <= probability) {
        for (int i = 0; i < N; i++) {
            int B = random_range(1, 100);
            int power = random_range(min_Epower, max_Epower);
            int health = random_range(min_Ehealth, max_Ehealth);
            int capacity = random_range(min_Ecapacity, max_Ecapacity);

            if(healing_probability <= 50) {
                auto* heal_unit = new HealUnit(game, 3000 + HealNum++, game->get_time(), power, health, capacity);
                game->add_heal_unit(heal_unit);
            }

            if (B <= ES) {
                auto Esoldier = new EarthSoldier(game, Ecount++, game->get_time(), power, health, capacity);
                game->add_unit(Esoldier, earth_soldier);
            }
            else if (B <= ES + ET) {
                auto Etank = new EarthTank(game,Ecount++, game->get_time(), power, health, capacity);
                game->add_unit(Etank, earth_tank);
            }
            else {
                auto Egunnery = new EarthGunnery(game, Ecount++, game->get_time(), power, health, capacity);
                game->add_unit(Egunnery, earth_gunnery);
            }
        }
        for (int i = 0; i < N; i++) {
            int B = random_range(1, 100);
            int power = random_range(min_Apower, max_Apower);
            int health = random_range(min_Ahealth, max_Ahealth);
            int capacity = random_range(min_Acapacity, max_Acapacity);

            if (B <= AS) {

                auto Asoldier = new AlienSoldier(game, 2000 + Acount++, game->get_time(), power, health, capacity);
                game->add_unit(Asoldier, alien_soldier);
            }
            else if (B <= AS + AM) {
                auto Amonster = new AlienMonster(game, 2000 + Acount++, game->get_time(), power, health, capacity, infection_prob);
                game->add_unit(Amonster, alien_monster);
            }
            else {
                auto Adrone = new AlienDrone(game, 2000 + Acount++, game->get_time(), power, health, capacity);
                game->add_unit(Adrone, alien_drone);
            }
        }
    }

    game->get_time()++;
}

int Generator::random_range(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
