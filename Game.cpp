#include "Game.h"

Game::Game() {
    load_file();
    Game::randGen();
}

void Game::randGen() {
    generator->Eunits_generator(this,n, es, et, eg, prop);
    generator->Aunits_generator(this,n, as, am, ad, prop);
}

void Game::load_file() {
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(3);//SIGQUIT number 3
    }

    file >> n;
    file >> es >> et >> eg;
    file >> as >> am >> ad;
    file >> prop;

    if (file.fail()) {
        cout << "Error in reading file" << endl;
        exit(9);//SIGKILL number 9
    }

    int min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
            min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity;

    file >> min_Epower >> max_Epower >> min_Ehealth >> max_Ehealth >> min_Ecapacity >> max_Ecapacity;
    file >> min_Apower >> max_Apower >> min_Ahealth >> max_Ahealth >> min_Acapacity >> max_Acapacity;

    generator = new Generator(min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
                              min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity);

    file.close();
}

void Game::add_Aunit(ArmyUnit *unit, unit_type type) {
    Aarmy.addUnit(unit, type);
}

void Game::add_Eunit(ArmyUnit *unit, unit_type type) {
    Earmy.addUnit(unit, type);
}

Game::~Game() {
    ArmyUnit *unit = nullptr;

    delete generator;
    generator = nullptr;

    while (!killed_list.isEmpty()) {
        killed_list.dequeue(unit);
        delete unit;
    }
}

void Game::phase1Test() {
    cout << "Phase 1 Test" << endl;
    cout << "----------------" << endl;
    cout << "----------------" << endl;
    cout << "Content Before Test" << endl;
    cout << "Earth Army: Content " << endl;
    Earmy.print();
    cout << "==============================================================================================" << endl;
    cout << "Alien Army: Content " << endl;
    Aarmy.print();
    cout << "==============================================================================================" << endl;
    cout << "Killed List: Content " << endl;
    killed_list.print();
    cout << "==============================================================================================" << endl;
    cout << "Temp List: Content " << endl;
    temp_list.print();
    cout << "==============================================================================================" << endl;
    cout << "Start Test" << endl;

    int loopCount  = 50;

    while (loopCount--) {
        int X = generator->random_range(1, 60);
        ArmyUnit *unit = nullptr;

        if (0 < X && X < 10) {
            unit = Earmy.pickUnit(earth_solider);
            if (unit != nullptr) {
                Earmy.addUnit(unit, earth_solider);
                unit->print();
            }
        } else if (10 < X && X < 20) {
            unit = Earmy.pickUnit(earth_tank);
            if (unit != nullptr) {
                unit->print();
                killed_list.enqueue(unit);
            }
        } else if (20 < X && X < 30) {
            unit = Earmy.pickUnit(earth_gunnery);
            if (unit != nullptr) {
                unit->setHealth(unit->getHealth() / 2);
                unit->print();
                Earmy.addUnit(unit, earth_gunnery);
            }
        } else if (30 < X && X < 40) {
            for (int i = 0; i < 5; i++) {
                unit = Aarmy.pickUnit(alien_solider);
                if (unit != nullptr) {
                    unit->setHealth(unit->getHealth() - 10);
                    temp_list.enqueue(unit);
                }
            }

            cout << "Temp List Content: ======================" << endl;
            temp_list.print();
            cout << "==========================================" << endl;
            while (!temp_list.isEmpty()) {
                temp_list.dequeue(unit);
                Aarmy.addUnit(unit, alien_solider);
            }

        } else if (40 < X && X < 50) {
            for (int i = 0; i < 5; i++) {
                unit = Aarmy.pickUnit(alien_monster);
                if (unit != nullptr) {
                    Aarmy.addUnit(unit, alien_monster);
                    unit->print();
                }
            }
        } else if (50 < X && X < 60) {
            int front = true;
            for (int i = 0; i < 6; i++) {
                unit = Aarmy.pickUnit(alien_drone, front);
                if (unit != nullptr) {
                    killed_list.enqueue(unit);
                    unit->print();
                }
                front = !front;
            }
        }
        randGen();
    }
    cout << "Killed List: Content " << endl;
    killed_list.print();
    cout << "==============================================================================================" << endl;

    cout << "Earth Army: Content " << endl;
    Earmy.print();
    cout << "==============================================================================================" << endl;

    cout << "Alien Army: Content " << endl;
    Aarmy.print();
}
