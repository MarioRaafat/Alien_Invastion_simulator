#include "Game.h"

Game::Game() {
    load_file();
    Game::randGen();
}

void Game::randGen() {
    generator->generate(this);
}

void Game::load_file() {
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(3);//SIGQUIT number 3
    }

    int n, es, eg, et, as, am, ad, prob;
    file >> n;
    file >> es >> et >> eg;
    file >> as >> am >> ad;
    file >> prob;


    int min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
            min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity;

    file >> min_Epower >> max_Epower >> min_Ehealth >> max_Ehealth >> min_Ecapacity >> max_Ecapacity;
    file >> min_Apower >> max_Apower >> min_Ahealth >> max_Ahealth >> min_Acapacity >> max_Acapacity;

    if (file.fail()) {
        cout << "Error in reading file" << endl;
        exit(9);//SIGKILL number 9
    }

    generator = new Generator(n, es, et, eg, as, am, ad, prob,
        min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
        min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity);

    file.close();
}

void Game::add_Aunit(ArmyUnit *unit, unit_type type) {
    Aarmy.addUnit(unit, type);
}

void Game::add_Eunit(ArmyUnit *unit, unit_type type) {
    Earmy.addUnit(unit, type);
}

void Game::add_heal_unit(HealUnit* HU) {
    heal_list.push(HU);
}

//void Game::earth_attack_aliens() {
//    Esolider_attack();
//
//    heal();
//}
//
//void Game::aliens_attack_earth() {
//    Asolider_attack();
//}

Game::~Game() {
    ArmyUnit *unit = nullptr;

    delete generator;
    generator = nullptr;

    while (!killed_list.isEmpty()) {
        killed_list.dequeue(unit);
        delete unit;
    }
}

//void Game::Esolider_attack() {
//    ArmyUnit* soldier_to_attack = Earmy.pickUnit(earth_soldier);
//    ArmyUnit* soldier_to_be_attacked;
//    int capacity;
//    int empty_spaces = 0;
//
//    if (dynamic_cast<EarthSoldier*>(soldier_to_attack)) {
//        capacity = soldier_to_attack->getAttackCapacity();
//        for(int i = 0; i < capacity; i++) {
//            soldier_to_be_attacked = Aarmy.pickUnit(alien_soldier);
//            if (soldier_to_be_attacked){
//                temp_list.enqueue(soldier_to_be_attacked);
//            }
//            else {
//                empty_spaces++;
//            }
//        }
//    }
//
//    for (int i = 0; i < (capacity - empty_spaces); i++) {
//        temp_list.dequeue(soldier_to_be_attacked);
//        soldier_to_attack->attack(soldier_to_be_attacked);
//        if (soldier_to_be_attacked->isDead()) {
//            killed_list.enqueue(soldier_to_be_attacked);
//        }
//        else {
//            Aarmy.addUnit(soldier_to_be_attacked, alien_soldier);
//        }
//    }
//    Earmy.addUnit(soldier_to_attack, earth_soldier);
//}
//
//
//void Game::Asolider_attack() {
//    ArmyUnit* soldier_to_attack = Aarmy.pickUnit(alien_soldier);
//    ArmyUnit* soldier_to_be_attacked;
//    int capacity;
//    int empty_spaces = 0;
//
//    if (dynamic_cast<AlienSoldier*>(soldier_to_attack)) {
//        capacity = soldier_to_attack->getAttackCapacity();
//        for(int i = 0; i < capacity; i++) {
//            soldier_to_be_attacked = Earmy.pickUnit(earth_soldier);
//            if (soldier_to_be_attacked){
//                temp_list.enqueue(soldier_to_be_attacked);
//            }
//            else {
//                empty_spaces++;
//            }
//        }
//    }
//
//    for (int i = 0; i < (capacity - empty_spaces); i++) {
//        temp_list.dequeue(soldier_to_be_attacked);
//        soldier_to_attack->attack(soldier_to_be_attacked);
//        if (soldier_to_be_attacked->isDead()) {
//            killed_list.enqueue(soldier_to_be_attacked);
//        }
//        else if (soldier_to_be_attacked->getHealth() >= double(soldier_to_be_attacked->getOriginalHealth() * 0.2)){
//            Earmy.addUnit(soldier_to_be_attacked, earth_soldier);
//        }
//        else {
//            soldier_UML.push(soldier_to_be_attacked);
//        }
//    }
//    Aarmy.addUnit(soldier_to_attack, alien_soldier);
//}

//void Game::heal() {
//    HealUnit* HU;
//    ArmyUnit* damaged_unit;
//    int capacity;
//
//    count_rounds_in_UML();
//
//    while(true) {
//        if( (soldier_UML.is_empty() && tank_UML.isEmpty()) || heal_list.isEmpty()) {
//            return;
//        }
//
//        heal_list.pop(HU);
//        capacity = HU->getAttackCapacity();
//
//        for(int i = 0; i < capacity; i++) {
//            if (!soldier_UML.is_empty()) {
//                soldier_UML.pop(damaged_unit);
//                HU->attack(damaged_unit);
//                if (damaged_unit->getHealth() < double(damaged_unit->getOriginalHealth() * 0.2)) {
//                    temp_list.enqueue(damaged_unit);
//                }
//                else {
//                    add_Eunit(damaged_unit, earth_soldier);
//                }
//            }
//            else if (!tank_UML.isEmpty()){
//                tank_UML.dequeue(damaged_unit);
//                HU->attack();
//                if (damaged_unit->getHealth() < double(damaged_unit->getOriginalHealth() * 0.2)) {
//                    temp_list.enqueue(damaged_unit);
//                }
//                else {
//                    add_Eunit(damaged_unit, earth_tank);
//                }
//            }
//            else {
//                delete HU;
//                HU = nullptr;
//                break;
//            }
//        }
//        delete HU;
//        HU = nullptr;
//    }
//
//    while(!temp_list.isEmpty()) {
//        temp_list.dequeue(damaged_unit);
//
//        if (damaged_unit->getTypeId() == earth_soldier) {
//            soldier_UML.push(damaged_unit);
//        }
//        else {
//            tank_UML.enqueue(damaged_unit);
//        }
//    }
//}

void Game::count_rounds_in_UML() {
    ArmyUnit* unit;

    while(!soldier_UML.is_empty()) {
        soldier_UML.pop(unit);
        unit->set_count_UML(unit->get_count_UML() + 1);
        temp_list.enqueue(unit);
    }

    while(!temp_list.isEmpty()) {
        temp_list.dequeue(unit);
        if (unit->get_count_UML() < 10) {
            soldier_UML.push(unit);
        }
        else {
            killed_list.enqueue(unit);
        }
    }

    while(!tank_UML.isEmpty()) {
        tank_UML.dequeue(unit);
        unit->set_count_UML(unit->get_count_UML() + 1);
        temp_list.enqueue(unit);
    }

    while(!soldier_UML.is_empty()) {
        temp_list.dequeue(unit);
        if (unit->get_count_UML() < 10) {
            tank_UML.enqueue(unit);
        }
        else {
            killed_list.enqueue(unit);
        }
    }
}

void Game::play() {
    size_t curr_time_step{};
    while (true) {
        print();
        fight();
        randGen();
        if (curr_time_step++ > 40 && winner() != "None") {
            break;
        }
    }
}

void Game::add_unit(ArmyUnit *unit, unit_type type) {
    if (type == earth_soldier || type == earth_tank || type == earth_gunnery) {
        Earmy.addUnit(unit, type);
    } else if (type == alien_soldier || type == alien_monster || type == alien_drone) {
        Aarmy.addUnit(unit, type);
    }
    else {
        add_heal_unit(static_cast<HealUnit*>(unit));
    }
}

void Game::fight() {
    cout << "=================== Units Fighting at cuurent time step ==========\n";
    Earmy.attack();
//    heal();
   Aarmy.attack();
}

EarthArmy &Game::getEarthArmy() {
    return Earmy;
}

AlienArmy &Game::getAlienArmy() {
    return Aarmy;
}

void Game::add_to_killed_list(ArmyUnit *unit) {
    killed_list.enqueue(unit);
}

void Game::print() {
    Earmy.print();
    Aarmy.print();
    cout << "======================== Heal List Alive Units ====================\n" << heal_list;
    cout << "======================== Soldier UML Units ====-===================\n" << soldier_UML;
    cout << "========================== Tank UML Units =========================\n" << tank_UML;
    cout << "========================= Kiled List Units ========================\n" << killed_list;
}

const string &Game::winner() const {
    static string earth = "Earth";
    static string alien = "Alien";
    static string draw = "Draw";
    static string none = "None";

    if (Earmy.soliders_count() > 0 &&  Aarmy.soldiers_count() == 0) {
        return earth;
    }
    if (Aarmy.soldiers_count() > 0 && Earmy.soliders_count() == 0) {
        return alien;
    }
    if (Aarmy.soldiers_count() == 0 && Earmy.soliders_count() == 0) {
        return draw;
    }
    return none;
}
