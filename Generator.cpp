#include "Generator.h"
#include "Units/Earth/EarthSoldier.h"
#include "Units/Earth/EarthTank.h"
#include "Units/Earth/EarthGunnery.h"
#include "Game.h"
#include <random>

#include "Units/Alien/AlienSoldier.h"

int Generator::Ecount = 0;
int Generator::Acount = 0;
int Generator::Scount = 0;
int Generator::HealNum = 0;



Generator::Generator(int n, int es, int et, int eg, int as, int am, int ad, int hu, int prob, int infec,
                     int min_Epw, int max_Epw, int min_Ehl, int max_Ehl, int min_Ecap, int max_Ecap,
                     int min_Apw, int max_Apw, int min_Ahl, int max_Ahl, int min_Acap, int max_Acap,
                     int min_Spw, int max_Spw, int min_Shl, int max_Shl, int min_Scap, int max_Scap)

        : N(n), ES(es), ET(et), EG(eg), AS(as), AM(am), AD(ad), HU(hu), probability{prob}, infection_prob(infec),
          min_Epower(min_Epw), max_Epower(max_Epw), min_Ehealth(min_Ehl), max_Ehealth(max_Ehl), min_Ecapacity(min_Ecap), max_Ecapacity(max_Ecap),
          min_Apower(min_Apw), max_Apower(max_Apw), min_Ahealth(min_Ahl), max_Ahealth(max_Ahl), min_Acapacity(min_Acap), max_Acapacity(max_Acap),
          min_Spower(min_Spw), max_Spower(max_Spw), min_Shealth(min_Shl), max_Shealth(max_Shl), min_Scapacity(min_Scap), max_Scapacity(max_Scap)
{}

void Generator::generate(Game *game) const {
    int A = random_range(1, 100);

    if (A <= probability) {
        for (int i = 0; i < N && Ecount < 1000; i++) {
            int B = random_range(1, 100);
            int power = random_range(min_Epower, max_Epower);
            int health = random_range(min_Ehealth, max_Ehealth);
            int capacity = random_range(min_Ecapacity, max_Ecapacity);
            int Spower = random_range(min_Spower, max_Spower);
            int Shealth = random_range(min_Shealth, max_Shealth);
            int Scapacity = random_range(min_Scapacity, max_Scapacity);

            if (B <= ES) {
                auto Esoldier = new EarthSoldier(game, ++Ecount, game->get_time(), power, health, capacity);
                game->add_unit(Esoldier, earth_soldier);
            }
            else if (B <= ES + ET) {
                auto Etank = new EarthTank(game,++Ecount, game->get_time(), power, health, capacity);
                game->add_unit(Etank, earth_tank);
            }
            else if (B <= ES + ET + EG){
                auto Egunnery = new EarthGunnery(game, ++Ecount, game->get_time(), power, health, capacity);
                game->add_unit(Egunnery, earth_gunnery);
            }
            else {
                auto heal_unitt = new HealUnit(game, 3000 + ++HealNum, game->get_time(), power, health, capacity);
                game->add_unit(heal_unitt, heal_unit);
            }

            if (game->check_savers_mode()) {
                auto saver = new SaverUnit(game, 5000 + ++Scount, game->get_time(), Spower, Shealth, Scapacity);
                game->add_unit(saver, saver_unit);
            }
        }
        for (int i = 0; i < N && Acount < 1000; i++) {
            int B = random_range(1, 100);
            int power = random_range(min_Apower, max_Apower);
            int health = random_range(min_Ahealth, max_Ahealth);
            int capacity = random_range(min_Acapacity, max_Acapacity);

            if (B <= AS) {

                auto Asoldier = new AlienSoldier(game, 2000 + ++Acount, game->get_time(), power, health, capacity);
                game->add_unit(Asoldier, alien_soldier);
            }
            else if (B <= AS + AM) {
                auto Amonster = new AlienMonster(game, 2000 + ++Acount, game->get_time(), power, health, capacity, infection_prob);
                game->add_unit(Amonster, alien_monster);
            }
            else {
                //MARION there is a mem leak here and i dnonto know fkin why>??
                auto Adronee = new AlienDrone(game, 2000 + ++Acount, game->get_time(), power, health, capacity);
                game->add_unit(Adronee, alien_drone);
            }
        }
    }
}

int Generator::random_range(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

int Generator::get_Ecount() {
    return Ecount;
}

int Generator::get_Acount() {
    return Acount;
}