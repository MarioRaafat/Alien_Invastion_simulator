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

    int min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
            min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity;

    file >> min_Epower >> max_Epower >> min_Ehealth >> max_Ehealth >> min_Ecapacity >> max_Ecapacity;
    file >> min_Apower >> max_Apower >> min_Ahealth >> max_Ahealth >> min_Acapacity >> max_Acapacity;

    generator = new Generator(min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
                              min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity);

    file.close();
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

AlienArmy &Game::getAlienArmy()   {
    return Aarmy;
}

EarthArmy &Game::getEarthArmy()  {
    return Earmy;
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

    int loopCount  = 10;

    while (loopCount--) {
        int X = generator->random_range(1, 60);
        ArmyUnit *unit = nullptr;

        if (0 < X && X < 10) {
            unit = Earmy.pickUnit(1);
            if (unit != nullptr) {
                Earmy.addUnit(unit, 1);
                unit->print();
            }
        } else if (10 < X && X < 20) {
            unit = Earmy.pickUnit(2);
            if (unit != nullptr) {
                unit->print();
                killed_list.enqueue(unit);
            }
        } else if (20 < X && X < 30) {
            unit = Earmy.pickUnit(3);
            if (unit != nullptr) {
                unit->setHealth(unit->getHealth() / 2);
                unit->print();
                Earmy.addUnit(unit, 3);
            }
        } else if (30 < X && X < 40) {
            for (int i = 0; i < 5; i++) {
                unit = Aarmy.pickUnit(4);
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
                Aarmy.addUnit(unit, 4);
            }

        } else if (40 < X && X < 50) {
            for (int i = 0; i < 5; i++) {
                unit = Aarmy.pickUnit(5);
                if (unit != nullptr) {
                    Aarmy.addUnit(unit, 5);
                    unit->print();
                }
            }
        } else if (50 < X && X < 60) {
            int front = true;
            for (int i = 0; i < 6; i++) {
                unit = Aarmy.pickUnit(6, front);
                if (unit != nullptr) {
                    killed_list.enqueue(unit);
                    unit->print();
                }
                front = !front;
            }
        }
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