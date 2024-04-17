#ifndef ALIEN_INVASTION_SIMULATOR_GAME_H
#define ALIEN_INVASTION_SIMULATOR_GAME_H

#include <iostream>
#include <ArrayStack/ArrayStack.h>
#include <LinkedQueue/LinkedQueue.h>
#include <PriorityQueue/PriorityQueue.h>
#include "AlienSoldier.h"
#include "EarthSoldier.h"
#include <fstream>



class Game {
public:
    Game();
    void generator(int n, int es, int et, int eg, int as, int am, int ad, int prop);
    void earth_units_generator(int n, int es, int et, int eg, int prop);
    void alien_units_generator(int n, int as, int am, int ad, int prop);

private:
    LinkedQueue<EarthSoldier *> EarthSoldiers;
    LinkedQueue<AlienSoldier *> AlienSoldiers;
    //......  rest of conatiners

    static int earth_count;
    static int alien_count;
    int current_time;
    int min_earth_power;
    int max_earth_power;
    int min_earth_health;
    int max_earth_health;
    int min_earth_capacity;
    int max_earth_capacity;

    int min_alien_power;
    int max_alien_power;
    int min_alien_health;
    int max_alien_health;
    int min_alien_capacity;
    int max_alien_capacity;


    int random_range(int min, int max) ;

    void load_file(int &n, int &es, int &et, int &eg, int &as, int &am, int &ad, int &prop);
};


#endif //ALIEN_INVASTION_SIMULATOR_GAME_H