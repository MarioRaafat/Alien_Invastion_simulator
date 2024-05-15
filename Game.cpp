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

void Game::decrement_infection_number() {
    infection_number--;
}

void Game::increment_immune_number() {
    immune_number++;
}


void Game::add_heal_unit(HealUnit* HU) {
    if (HU) {
        heal_list.push(HU);
    }
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
    ofstream out_file("output.txt", std::ios::out | std::ios::trunc);
    ArmyUnit *unit = nullptr;
    out_file << winner() << endl;

    while (!killed_list.isEmpty()) {
        killed_list.dequeue(unit);

        if (unit->getTypeId() == earth_soldier || unit->getTypeId() == earth_tank
            || unit->getTypeId() == earth_gunnery) {
            earth_avg_df += unit->getDf();
            earth_avg_dd += unit->getDd();
            earth_avg_DBb += unit->getDBb();
        } else if (unit->getTypeId() == alien_soldier || unit->getTypeId() == alien_monster
                   || unit->getTypeId() == alien_drone) {
            alien_avg_df += unit->getDf();
            alien_avg_dd += unit->getDd();
            alien_avg_DBb += unit->getDBb();
        }
        out_file << unit->getTd() << " " << unit->getID() << " " << unit->getTj() << " ";
        out_file << unit->getDf() << " " << unit->getDd() << " " << unit->getDBb() << endl;
        if (unit->getDBb() != 0) {
            out_file << "Df/ Db: " << double(unit->getDf() / unit->getDBb()) * 100.0 << endl;
            out_file << "Dd/ Db: " << double(unit->getDd() / unit->getDBb()) * 100.0 << endl;
        }
        out_file << "==========================================================================" << endl;

        delete unit;
        unit = nullptr;
    }
    print_stats(out_file);

    delete generator;
    generator = nullptr;

    out_file.close();
}
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
//     delete generator;
//     generator = nullptr;
//     out_file.close();
//}


void Game::heal() {
    count_rounds_in_UML();

    while(true) {
        HealUnit* HU{};
        if((soldier_UML.is_empty() && tank_UML.isEmpty()) || heal_list.isEmpty()) {
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

void Game::add_unit(ArmyUnit *unit, unit_type type, bool droneFront) {
    if (type == earth_soldier || type == earth_tank || type == earth_gunnery) {
        Earmy.addUnit(unit, type);
    } else if (type == alien_soldier || type == alien_monster || type == alien_drone) {
        Aarmy.addUnit(unit, type, droneFront);
    }
    else {
        add_heal_unit(static_cast<HealUnit*>(unit));
    }
}

ArmyUnit * Game::pick_unit(unit_type type, bool droneFront, bool pickone) {
    if (type == earth_soldier || type == earth_gunnery || type == earth_tank) {
        return Earmy.pickUnit(type);
    }
    else if (type == alien_soldier || type == alien_monster || type == alien_drone) {
        return Aarmy.pickUnit(type, droneFront, pickone);
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

bool Game::which_tank_attack() const {
    return (double(Earmy.soliders_count()) < (double(Aarmy.soldiers_count()) * .3));
}

bool Game::stop_attacking_soldiers() const {
    return (double(Earmy.soliders_count()) > (double(Aarmy.soldiers_count()) * .8));
}

bool Game::check_savers_mode() {
    if (infection_number == 0) {
        saver_mode = false;
    }
    else if (Earmy.soliders_count() && (((infection_number * 100) / Earmy.soliders_count()) > threshold)) {
        saver_mode = true;
    }

    return saver_mode;
}


void Game::add_to_killed_list(ArmyUnit *unit) {
    if (!unit) {
        return;
    }
    killed_list.enqueue(unit);
    if (unit->getTypeId() == earth_soldier) {
        killed_earth_soldiers++;
    }
    else if (unit->getTypeId() == earth_tank) {
        killed_earth_tanks++;
    }
    else if (unit->getTypeId() == earth_gunnery) {
        killed_earth_gunneries++;
    }
    else if (unit->getTypeId() == alien_soldier) {
        killed_aliens_soldiers++;
    }
    else if (unit->getTypeId() == alien_monster) {
        killed_aliens_monsters++;
    }
    else if (unit->getTypeId() == alien_drone) {
        killed_aliens_drones++;
    }
    else {
        killed_saver_units++;
    }
}

void Game::print() const {
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
    static string earth = "Earth Wins";
    static string alien = "Alien Wins";
    static string draw = "Draw";
    static string none = "None";

    if (Earmy.army_size() > 0 &&  Aarmy.units_count() == 0) {
        return earth;
    }
    if (Aarmy.units_count() > 0 && Earmy.army_size() == 0) {
        return alien;
    }
    if (Aarmy.units_count() == Earmy.army_size()) {
        return draw;
    }
    return none;
}

bool Game::is_interactive() const {
    return interactive_mode;
}

int Game::total_killed_aliens() const {
    return killed_aliens_drones + killed_aliens_soldiers + killed_aliens_monsters;
}

int Game::total_killed_earth() const {
    return killed_earth_gunneries + killed_earth_soldiers + killed_earth_tanks;
}

void Game::print_stats(ofstream &out_file) const {
    out_file << "====================== Earth Army Stats =====================\n";
    out_file << "ESd / ESTotal: " << double(killed_earth_soldiers / Generator::get_Ecount()) << "\n";
    out_file << "ETd / ETTotal: " << double(killed_earth_tanks / Generator::get_Ecount()) << "\n";
    out_file << "EGd / EGTotal: " << double(killed_earth_gunneries / Generator::get_Ecount()) << "\n";
    out_file << "Earth Total Killed: " << total_killed_earth() << "\n";
    out_file << "Average Df: " << earth_avg_df / total_killed_earth() << "\n";
    out_file << "Average Dd: " << earth_avg_dd / total_killed_earth() << "\n";
    out_file << "Average DBb: " << earth_avg_DBb / total_killed_earth() << "\n";

    out_file << "====================== Alien Army Stats =====================\n";
    out_file << "ASd / ASTotal: " << double(killed_aliens_soldiers / Generator::get_Acount()) << "\n";
    out_file << "AMd / AMTotal: " << double(killed_aliens_monsters / Generator::get_Acount()) << "\n";
    out_file << "ADd / ADTotal: " << double(killed_aliens_drones / Generator::get_Acount()) << "\n";
    out_file << "Alien Total Killed: " << total_killed_aliens() << "\n";
    out_file << "Average Df: " << alien_avg_df / total_killed_aliens() << "\n";
    out_file << "Average Dd: " << alien_avg_dd / total_killed_aliens() << "\n";
    out_file << "Average DBb: " << alien_avg_DBb / total_killed_aliens() << "\n";
}
