#include "Game.h"

Game::Game()  {
    char mode;

    cout << "If you want to join Interactive mode press any character expect letter n in small case\n";
    cin >> mode;

    if (mode != 'n')
        interactive_mode = true;

    load_file();
    curr_time_step = 0;
    infection_number = immune_number = 0;
    saver_mode = false;
    Game::randGen();
//    out_file.open("output.txt", std::ios::out | std::ios::trunc);
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

    int n, es, eg, et, as, am, ad, prob, infection_prob;
    file >> n;
    file >> es >> et >> eg;
    file >> as >> am >> ad;
    file >> prob;
    file >> infection_prob;
    file >> threshold;

    int min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
            min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity;

    file >> min_Epower >> max_Epower >> min_Ehealth >> max_Ehealth >> min_Ecapacity >> max_Ecapacity;
    file >> min_Apower >> max_Apower >> min_Ahealth >> max_Ahealth >> min_Acapacity >> max_Acapacity;

    if (file.fail()) {
        cout << "Error in reading file" << endl;
        exit(9);//SIGKILL number 9
    }

    generator = new Generator(n, es, et, eg, as, am, ad, prob, infection_prob,
        min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
        min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity);

    file.close();
}

int Game::get_time() const {
    return curr_time_step;
}

void Game::increment_infection_number() {
    infection_number++;
}

void Game::increment_immune_number() {
    immune_number++;
}


void Game::add_heal_unit(HealUnit* HU) {
    heal_list.push(HU);
}

void Game::add_to_soldier_UML(EarthSoldier* damaged_unit) {
    if (damaged_unit) {
        soldier_UML.push(damaged_unit);
    }
}

void Game::add_to_tank_UML(EarthTank *damaged_unit) {
    if (damaged_unit)
        tank_UML.enqueue(damaged_unit);
}

EarthSoldier* Game::pick_from_soldier_UML() {
    EarthSoldier* damaged_unit{};
    soldier_UML.pop(damaged_unit);

    return damaged_unit;
}

EarthTank * Game::pick_from_tank_UML() {
    EarthTank* damaged_unit{};
    tank_UML.dequeue(damaged_unit);

    return damaged_unit;
}

Game::~Game() {
//     ArmyUnit *unit = nullptr;
//     double earth_avg_df{};
//     double earth_avg_dd{};
//     double earth_avg_DBb{};
//     double alien_avg_df{};
//     double alien_avg_dd{};
//     double alien_avg_DBb{};
//
//     delete generator;
//     generator = nullptr;
//
//     while (!killed_list.isEmpty()) {
//         killed_list.dequeue(unit);
//
//         if (unit->getTypeId() == earth_soldier || unit->getTypeId() == earth_tank || unit->getTypeId() == earth_gunnery) {
//             earth_avg_df += unit->getDf();
//             earth_avg_dd += unit->getDd();
//             earth_avg_DBb += unit->getDBb();
//         } else if (unit->getTypeId() == alien_soldier || unit->getTypeId() == alien_monster || unit->getTypeId() == alien_drone){
//             alien_avg_df += unit->getDf();
//             alien_avg_dd += unit->getDd();
//             alien_avg_DBb += unit->getDBb();
//         }
//         out_file << unit->getTd() << " " << unit->getID() << " " << unit->getTj() << " ";
//         out_file << unit->getDf() << " " << unit->getDd() << " " << unit->getDBb() << endl;
//         delete unit;
//     }
//     out_file << "Result is " << winner() << endl;
//     Earmy.print_stats(out_file);
//     out_file << "Earth Army Avg Df: " << earth_avg_df / Earmy.getTotalKilled() << endl;
//     out_file << "Earth Army Avg Dd: " << earth_avg_dd / Earmy.getTotalKilled() << endl;
//     out_file << "Earth Army Avg DBb: " << earth_avg_DBb / Earmy.getTotalKilled() << endl;
//     //print avg df/db % and dd / db %
//     out_file << "Avg df / db percentage: " << ((earth_avg_df / Earmy.getTotalKilled()) / (earth_avg_DBb / Earmy.getTotalKilled()) * 100)  << endl;
//     out_file << "Avg dd / db percentage: " << ((earth_avg_dd / Earmy.getTotalKilled()) / (earth_avg_DBb / Earmy.getTotalKilled()) * 100)  << endl;
//
//     Aarmy.print_stats(out_file);
//     out_file << "Alien Army Avg Df: " << alien_avg_df / Aarmy.total_killed() << endl;
//     out_file << "Alien Army Avg Dd: " << alien_avg_dd / Aarmy.total_killed() << endl;
//     out_file << "Alien Army Avg DBb: " << alien_avg_DBb / Aarmy.total_killed() << endl;
//
//     out_file << "Avg df / db percentage: " << ((alien_avg_df / Aarmy.total_killed()) / (alien_avg_DBb / Aarmy.total_killed()) * 100)  << endl;
//     out_file << "Avg dd / db percentage: " << ((alien_avg_dd / Aarmy.total_killed()) / (alien_avg_DBb / Aarmy.total_killed()) * 100)  << endl;
//     out_file.close();
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

void Game::heal() {
    HealUnit* HU;

    count_rounds_in_UML();

    while(true) {
        if( (soldier_UML.is_empty() && tank_UML.isEmpty()) || heal_list.isEmpty()) {
            return;
        }
        heal_list.pop(HU);
        HU->attack();
        delete HU;
        HU = nullptr;
    }
}

void Game::count_rounds_in_UML() {
    EarthSoldier* soldier{};
    EarthTank* tank{};
    LinkedQueue<EarthSoldier*> soldier_list;
    LinkedQueue<EarthTank*> tank_list;

    while(!soldier_UML.is_empty()) {
        soldier_UML.pop(soldier);
        soldier->set_count_UML(soldier->get_count_UML() + 1);
        soldier_list.enqueue(soldier);
    }

    while(!soldier_list.isEmpty()) {
        soldier_list.dequeue(soldier);
        if (soldier->get_count_UML() < 10) {
            soldier_UML.push(soldier);
        }
        else {
            killed_list.enqueue(soldier);
        }
    }

    while(!tank_UML.isEmpty()) {
        tank_UML.dequeue(tank);
        tank->set_count_UML(tank->get_count_UML() + 1);
        tank_list.enqueue(tank);
    }

    while(!tank_list.isEmpty()) {
        tank_list.dequeue(tank);
        if (tank->get_count_UML() < 10) {
            tank_UML.enqueue(tank);
        }
        else {
            killed_list.enqueue(tank);
        }
    }
}

void Game::play() {
    cout << "Simulation Starts\n";
    while (true) {
        if (interactive_mode) {
            cout << "Enter a key to print ";
            cin.get();
            cout << "\n Current time step: " << curr_time_step << endl;
            print();
        }

        fight();
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

ArmyUnit * Game::pick_unit(unit_type type) {
    if (type == earth_soldier || type == earth_gunnery || type == earth_tank) {
        return Earmy.pickUnit(type);
    }
    else if (type == alien_soldier || type == alien_monster || type == alien_drone) {
        return Aarmy.pickUnit(type);
    }
    else {
        HealUnit* h{};
        heal_list.pop(h);
        return h;
    }
}

void Game::fight() {
    if (interactive_mode) {
        cout << "=================== Units Fighting at cuurent time step ==========\n";
    }
    Earmy.attack();
    if (check_savers_mode()) {
        Earmy.savers_attack();
    }
    heal();
    Aarmy.attack();
}

bool Game::which_tank_attack() {
    return (double(Earmy.soliders_count()) < (double(Aarmy.soldiers_count()) * .3));
}

bool Game::stop_attacking_soldiers() {
    return (double(Earmy.soliders_count()) > (double(Aarmy.soldiers_count()) * .8));
}

bool Game::check_savers_mode() {
    if (infection_number == 0) {
        saver_mode = false;
    }
    else if ( ((infection_number * 100) / Earmy.soliders_count()) > threshold) {
        saver_mode = true;
    }

    return saver_mode;
}

// EarthArmy &Game::getEarthArmy() {
//     return Earmy;
// }
//
// AlienArmy &Game::getAlienArmy() {
//     return Aarmy;
// }

void Game::add_to_killed_list(ArmyUnit *unit) {
    if (unit) {
        killed_list.enqueue(unit);
    }
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

const string &Game::winner() const { // why static
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
    if (Aarmy.soldiers_count() == Earmy.soliders_count()) {
        return draw;
    }
    return none;
}

bool Game::is_interactive() const {
    return interactive_mode;
}
