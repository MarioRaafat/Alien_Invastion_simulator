#include "Game.h"

int Game::earth_count = 0;
int Game::alien_count = 0;

Game::Game() {
    current_time = 0;
}

void Game::generator(int n, int es, int et, int eg, int as, int am, int ad, int prop) {
    load_file(n, es, et, eg, as, am, ad, prop);
    earth_units_generator(n, es, et, eg, prop);
    alien_units_generator(n, as, am, ad, prop);
}

void Game::earth_units_generator(int n, int es, int et, int eg, int prop){
    int A = random_range(1, 100);
    if (A >= prop) {
        for (int i = 0; i < n; i++) {
            int B = random_range(1, 100);

            if (B <= es) {
                auto earth_soldier = new EarthSoldier(earth_count++, current_time, random_range(min_earth_power, max_earth_power),
                                                 random_range(min_earth_health, max_earth_health),
                                                 random_range(min_earth_capacity, max_earth_capacity));
                EarthSoldiers.enqueue(earth_soldier);
            } else if (B <= es + et) {
                // same for tank
            } else {
                // same for gunnery
            }
        }
    }
}
void Game::alien_units_generator(int n, int as, int am, int ad, int prop){
    int A = random_range(1, 100);
    if (A >= prop) {
        for (int i = 0; i < n; i++) {
            int B = random_range(1, 100);

            if (B <= as) {
                auto alien_soldier = new AlienSoldier(2000 + alien_count++, current_time,
                                                      random_range(min_alien_power, max_alien_power),
                                                      random_range(min_alien_health, max_alien_health),
                                                      random_range(min_alien_capacity, max_alien_capacity));
                AlienSoldiers.enqueue(alien_soldier);
            } else if (B <= as + am) {
                // same for tank
            } else {
                // same for gunnery
            }
        }
    }
}

int Game::random_range(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void Game::load_file(int n, int es, int et, int eg, int as, int am, int ad, int prop) {
    std::ifstream file("input.txt");

    if (!file.is_open()) {
        std::cout << "File not found" << std::endl;
        return;
    }

    file >> n;
    file >> es >> et >> eg;
    file >> as >> am >> ad;
    file >> prop;

    file >> min_earth_power >> max_earth_power >> min_earth_health >> max_earth_health >> min_earth_capacity >> max_earth_capacity;
    file >> min_alien_power >> max_alien_power >> min_alien_health >> max_alien_health >> min_alien_capacity >> max_alien_capacity;

    file.close();
}
