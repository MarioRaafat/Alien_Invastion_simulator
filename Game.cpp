#include "Game.h"

Game::Game()  {
    char mode;

    cout << "If you want to join Interactive mode press any character expect letter n in small case\n";
    cin >> mode;

    if (mode != 'n')
        interactive_mode = true;

    load_file();
    Game::randGen();
    out_file.open("output.txt", std::ios::out | std::ios::trunc);
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
    double earth_avg_df{};
    double earth_avg_dd{};
    double earth_avg_DBb{};
    double alien_avg_df{};
    double alien_avg_dd{};
    double alien_avg_DBb{};

    delete generator;
    generator = nullptr;

    while (!killed_list.isEmpty()) {
        killed_list.dequeue(unit);

        if (unit->getTypeId() == earth_soldier || unit->getTypeId() == earth_tank || unit->getTypeId() == earth_gunnery) {
            earth_avg_df += unit->getDf();
            earth_avg_dd += unit->getDd();
            earth_avg_DBb += unit->getDBb();
        } else if (unit->getTypeId() == alien_soldier || unit->getTypeId() == alien_monster || unit->getTypeId() == alien_drone){
            alien_avg_df += unit->getDf();
            alien_avg_dd += unit->getDd();
            alien_avg_DBb += unit->getDBb();
        }
        out_file << unit->getTd() << " " << unit->getID() << " " << unit->getTj() << " ";
        out_file << unit->getDf() << " " << unit->getDd() << " " << unit->getDBb() << endl;
        delete unit;
    }
    out_file << "Result is " << winner() << endl;
    Earmy.print_stats(out_file);
    out_file << "Earth Army Avg Df: " << earth_avg_df / Earmy.getTotalKilled() << endl;
    out_file << "Earth Army Avg Dd: " << earth_avg_dd / Earmy.getTotalKilled() << endl;
    out_file << "Earth Army Avg DBb: " << earth_avg_DBb / Earmy.getTotalKilled() << endl;
    //print avg df/db % and dd / db %
    out_file << "Avg df / db percentage: " << ((earth_avg_df / Earmy.getTotalKilled()) / (earth_avg_DBb / Earmy.getTotalKilled()) * 100)  << endl;
    out_file << "Avg dd / db percentage: " << ((earth_avg_dd / Earmy.getTotalKilled()) / (earth_avg_DBb / Earmy.getTotalKilled()) * 100)  << endl;

    Aarmy.print_stats(out_file);
    out_file << "Alien Army Avg Df: " << alien_avg_df / Aarmy.total_killed() << endl;
    out_file << "Alien Army Avg Dd: " << alien_avg_dd / Aarmy.total_killed() << endl;
    out_file << "Alien Army Avg DBb: " << alien_avg_DBb / Aarmy.total_killed() << endl;

    out_file << "Avg df / db percentage: " << ((alien_avg_df / Aarmy.total_killed()) / (alien_avg_DBb / Aarmy.total_killed()) * 100)  << endl;
    out_file << "Avg dd / db percentage: " << ((alien_avg_dd / Aarmy.total_killed()) / (alien_avg_DBb / Aarmy.total_killed()) * 100)  << endl;
    out_file.close();
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
    cout << "Simulation Starts\n";
    while (true) {
        if (interactive_mode) {
            cout << "Enter a key to print ";
            cin.get();
            print();
        }

        fight(curr_time_step);
        randGen();
        if (curr_time_step++ > 40 && winner() != "None") {
            break;
        }
    }
    cout << "Simulation Ended && Output File Is Created\n";
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

void Game::fight(int time_step) {
    if (interactive_mode) {
        cout << "=================== Units Fighting at cuurent time step ==========\n";
    }
    Earmy.attack(time_step);
//    heal();
   Aarmy.attack(time_step);
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
    if (!interactive_mode) {
        return;
    }

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

bool Game::is_interactive() const {
    return interactive_mode;
}
