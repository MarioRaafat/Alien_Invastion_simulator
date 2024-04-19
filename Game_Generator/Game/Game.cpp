#include "Game.h"


Game::Game() {
    load_file();
    //call Generatror Edited by Kerolos al 3l2
    Game::randGen();
}

void Game::randGen() {
    generator->Eunits_generator(this,n, es, et, eg, prop);
    generator->Aunits_generator(this,n, as, am, ad, prop);
}

void Game::load_file() {
    ifstream file("input.txt");
    //in which dierectory should i put the input file ?
    //ans:

    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
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
    delete generator;
    generator = nullptr;

    for (size_t i = 0; i < temp_list.size(); i++) {
        if (temp_list[i] != nullptr) {
            delete temp_list[i];
            temp_list[i] = nullptr;
        }
    }

    for (size_t i = 0; i < killed_list.size(); i++) {
        if (killed_list[i] != nullptr) {
            delete killed_list[i];
            killed_list[i] = nullptr;
        }
    }
}

 AlienArmy &Game::getAlienArmy()   {
    return Aarmy;
}

EarthArmy &Game::getEarthArmy()  {
   return Earmy;
}

void Game::phase1Test() {
    //generate a numer x between 1 and 100
    cout << "Phase 1 Test" << endl;
    cout << "----------------" << endl;
    cout << "----------------" << endl;
    int loopCount  = 10;
    while (loopCount--) {
        int X = rand() % 100 + 1;
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
                killed_list.push_back(unit);
            }
        } else if (20 < X && X < 30) {
            unit = Earmy.pickUnit(3);
            if (unit != nullptr) {
                unit->setHealth(unit->getHealth() / 2);
                cout << "Health: " << unit->getHealth() << endl;
                unit->print();
                Earmy.addUnit(unit, 3);
            }
        } else if (30 < X && X < 40) {
            for (int i = 0; i < 5; i++) {
                unit = Aarmy.pickUnit(4, false);
                if (unit != nullptr) {
                    unit->setHealth(unit->getHealth() - 10);
                    temp_list.push_back(unit);

                    //make a new Unit with the same data to donot deltete it twice
                    unit = new AlienSoldier(*static_cast<AlienSoldier *>(unit));
                    Aarmy.addUnit(unit, 4);
                    unit->print();
                }
            }
        } else if (40 < X && X < 50) {
            for (int i = 0; i < 5; i++) {
                unit = Aarmy.pickUnit(5, false);
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
                    killed_list.push_back(unit);
                    unit->print();
                }
                front = !front;
            }
        }
    }
    cout << "Temp List: " << endl;
    for (size_t i = 0; i < temp_list.size(); i++) {
        if (temp_list[i] != nullptr) {
            temp_list[i]->print();
        }
    }
    cout << "Killed List: " << endl;
    for (size_t i = 0; i < killed_list.size(); i++) {
        if (killed_list[i] != nullptr) {
            killed_list[i]->print();
        }
    }
}
