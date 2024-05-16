#include "Game.h"


Game::Game()  :generator{nullptr}, threshold{0} {
    cout << "If you want to join Interactive mode press any character expect letter n in small case\n";

    if (cin.get() != 'n')
        interactive_mode = true;

    load_file();
    curr_time_step = 1;
    infection_number = immune_number = 0;
    saver_mode   = false;
    Game::randGen();
}

void Game::randGen() {
    generator->generate(this);
}

/**
 * Read always from file input.txt
 * If the file is not found the program will exit(3) SIGQUITS
 * if the fail fails to read the file the program will exit (9) SIGKILL
 */
void Game::load_file() {
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(3);//SIGQUIT number 3
    }

    int n, es, eg, et, as, am, ad, hu, prob, infection_prob;
    file >> n;
    file >> es >> et >> eg >> hu;
    file >> as >> am >> ad;
    file >> prob;
    file >> infection_prob;
    file >> threshold;

    if (infection_prob > 5) {
        infection_prob = 5;
    }

    int min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
            min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity,
            min_Spower, max_Spower, min_Shealth, max_Shealth, min_Scapacity, max_Scapacity;

    file >> min_Epower >> max_Epower >> min_Ehealth >> max_Ehealth >> min_Ecapacity >> max_Ecapacity;
    file >> min_Apower >> max_Apower >> min_Ahealth >> max_Ahealth >> min_Acapacity >> max_Acapacity;
    file >> min_Spower >> max_Spower >>  min_Shealth >>  max_Shealth >> min_Scapacity >> max_Scapacity;

    if (file.fail()) {
        cout << "Error in reading file" << endl;
        exit(9);//SIGKILL number 9
    }

    generator = new Generator(n, es, et, eg, as, am, ad, hu, prob, infection_prob,
        min_Epower, max_Epower, min_Ehealth, max_Ehealth, min_Ecapacity, max_Ecapacity,
        min_Apower, max_Apower, min_Ahealth, max_Ahealth, min_Acapacity, max_Acapacity,
        min_Spower, max_Spower, min_Shealth, max_Shealth, min_Scapacity, max_Scapacity);

    file.close();
}

int Game::get_time() const {
    return curr_time_step;
}

void Game::increment_infection_number() {
    ++total_infected;
    ++infection_number;
}

void Game::decrement_infection_number() {
    --infection_number;
}

void Game::increment_immune_number() {
    ++immune_number;
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
    out_file << winner() << endl;
    out_file << "Current Time Step: " << curr_time_step << endl;

    //Delete Heal List
    while (!heal_list.isEmpty()) {
        HealUnit* HU{};
        heal_list.pop(HU);
        delete HU;
        HU = nullptr;
    }

    //Delete Killed List
    while (!killed_list.isEmpty()) {
        ArmyUnit *unit = nullptr;
        killed_list.dequeue(unit);
        incremenat_avg_to_print(unit);

        out_file << unit->getTd() << " " << unit->getID() << " " << unit->getTj() << " ";
        out_file << unit->getDf() << " " << unit->getDd() << " " << unit->getDBb() << endl;
        out_file << "==========================================================================" << endl;

        delete unit;
        unit = nullptr;
    }
    print_stats(out_file);
    delete generator;
    generator = nullptr;

    out_file.close();
}

/**
 * heal
 * @param none
 * @return none
 * Description: heal a unit first count rounds in UML and assure that it doesnot exceed 10 rounds
 * then pop the unit from the heal list and attack it
 * if the heal list is empty or the UML is empty return
 */
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

/**
 * count_rounds_in_UML
 * Increments the rounds in the UML for each unit
 * if the rounds exceed 10 rounds then the unit is removed from the UML and added to the killed list
 * @param none
 * @return none
 */
void Game::count_rounds_in_UML() {

    LinkedQueue<EarthSoldier*> soldier_list;
    LinkedQueue<EarthTank*> tank_list;

    while(!soldier_UML.is_empty()) {
        EarthSoldier* soldier{};
        soldier_UML.pop(soldier);
        soldier->set_count_UML(soldier->get_count_UML() + 1);
        soldier_list.enqueue(soldier);
    }

    while(!soldier_list.isEmpty()) {
        EarthSoldier* soldier{};
        soldier_list.dequeue(soldier);
        if (soldier->get_count_UML() <= 10) {
            soldier_UML.push(soldier);
        } else {
            soldier->setTd(curr_time_step);
            add_to_killed_list(soldier);
        }
    }

    while(!tank_UML.isEmpty()) {
        EarthTank* tank{};
        tank_UML.dequeue(tank);
        tank->set_count_UML(tank->get_count_UML() + 1);
        tank_list.enqueue(tank);
    }

    while(!tank_list.isEmpty()) {
        EarthTank* tank{};
        tank_list.dequeue(tank);
        if (tank->get_count_UML() <= 10) {
            tank_UML.enqueue(tank);
        } else {
            tank->setTd(curr_time_step);
            add_to_killed_list(tank);
        }
    }
}

/**
 * Play The Main Game Loop
 * @param none
 * @return none
 * Description: The main game loop that runs the simulation
 * Cheks for the Winner and if the game ends after 40 rounds at least
 * The sequence goes like this print fight generate random units
 * then it will break the loop and add the remaining units in the UML to the killed list
 * since they are not healed
 */
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
        if (curr_time_step++ >= 40 && winner() != "None") {
            break;
        }
    }

    //If the game ends and we still have units in the UML
    // we Should put them in the killed list
    while (!soldier_UML.empty()) {
        EarthSoldier* soldier{};
        soldier_UML.pop(soldier);
        soldier->setTd(curr_time_step);
        killed_list.enqueue(soldier);
        ++killed_earth_soldiers;
    }
    while (!tank_UML.isEmpty()) {
        EarthTank* tank{};
        tank_UML.dequeue(tank);
        tank->setTd(curr_time_step);
        killed_list.enqueue(tank);
        ++killed_earth_tanks;
    }
    cout << "Simulation Ended && Output File Is Created\n";
}

/**
 * @param unit unit to add in the proper army
 * @param type  any Type of earth Alien Heal or Saver
 * @param droneFront true if the drone to add drone in  front of the list
 * Doesont add null units
 */
void Game::add_unit(ArmyUnit *unit, unit_type type, bool droneFront) {

    if (type == earth_soldier || type == earth_tank || type == earth_gunnery) {
        Earmy.addUnit(unit, type);
    } else if (type == alien_soldier || type == alien_monster || type == alien_drone) {
        Aarmy.addUnit(unit, type, droneFront);
    } else if (type == heal_unit){
        add_heal_unit(static_cast<HealUnit*>(unit));
    } else if (type == saver_unit) {
        Sarmy.addUnit(unit);
    }
}

/**
 * @param type Alien Earth Heal or Saver
 * @param droneFront -> if the drone is in front of the list true else false
 * @param pickone -> to return the the unit if it on the list and size is 1 if true
 * @return ArmyUnit* the unit to pick or nullptr if the list is empty
 */
ArmyUnit* Game::pick_unit(unit_type type, bool droneFront, bool pickone) {
    if (type == earth_soldier || type == earth_gunnery || type == earth_tank) {
        return Earmy.pickUnit(type);
    } else if (type == alien_soldier || type == alien_monster || type == alien_drone) {
        return Aarmy.pickUnit(type, droneFront, pickone);
    } else if (type == saver_unit) {
        return Sarmy.pickUnit();
    } else if (type == heal_unit){
        HealUnit* h{};
        heal_list.pop(h);
        return h;
    }
    return nullptr;
}

void Game::fight() {
    if (interactive_mode) {
        cout << "=================== Units Fighting at cuurent time step ==========\n";
    }

    Earmy.attack();
    if (!Sarmy.is_destroyed()) {
        Sarmy.attack();
    }
    Aarmy.attack();
    heal();
}

//To know which one should i attack in the Monster attack
bool Game::which_tank_attack() const {
    return (double(Earmy.soliders_count()) < (double(Aarmy.soldiers_count()) * .3));
}

bool Game::stop_attacking_soldiers() const {
    return (double(Earmy.soliders_count()) > (double(Aarmy.soldiers_count()) * .8));
}

/**
 *
 * @return the conidtion at which we starts or stop Using saver Units
 */
bool Game::check_savers_mode() {
    if (infection_number == 0) {//enters here if all healed or at intital constion
        if (saver_mode) {//if was at saver then stop savers
            Sarmy.destroy_savers();
        }
        saver_mode = false;
    } else if (!Sarmy.is_destroyed()) {//if !distroyed :means not stopiing yet check or stopping condtion
        if (Earmy.soliders_count() && (((infection_number * 100) / Earmy.soliders_count()) >= threshold)) {
            saver_mode = true;
        }
    }
    return saver_mode;
}


/**
 * @param unit the unit to add to the killed list
 * And increment the killed units count
 */
void Game::add_to_killed_list(ArmyUnit *unit) {
    if (!unit) {
        return;
    }
    killed_list.enqueue(unit);
    if (unit->getTypeId() == earth_soldier) {
        killed_earth_soldiers++;
    } else if (unit->getTypeId() == earth_tank) {
        killed_earth_tanks++;
    } else if (unit->getTypeId() == earth_gunnery) {
        killed_earth_gunneries++;
    } else if (unit->getTypeId() == alien_soldier) {
        killed_aliens_soldiers++;
    } else if (unit->getTypeId() == alien_monster) {
        killed_aliens_monsters++;
    } else if (unit->getTypeId() == alien_drone) {
        killed_aliens_drones++;
    } else if (unit->getTypeId() == saver_unit) {
        killed_saver_units++;
    }
}

void Game::print() const {
    if (!interactive_mode) {
        return;
    }
   if (Earmy.soliders_count()) {
       cout << "Infection Percentage % is " << (double)infection_number / (double)(Earmy.soliders_count() + soldier_UML.size()) * 100<< endl;
   } else {
       cout << "Infection Percentage % is 0" << endl;
   }
    Earmy.print();
    Aarmy.print();
    Sarmy.print();
    cout << "======================== Heal List Alive Units ====================\n" << heal_list;
    cout << "======================== Soldier UML Units ====-===================\n" << soldier_UML;
    cout << "========================== Tank UML Units =========================\n" << tank_UML;
    cout << "========================= Kiled List Units ========================\n" << killed_list;
}

/**
 * @return the winner of the game
 */
const string &Game::winner() const {
    //Why make it static
    //bcs static variables are initialized only once and they are not destroyed until the program ends
    //DESIGN PATTERN: SINGLETON

    static string earth = "Earth Wins";
    static string alien = "Alien Wins";
    static string draw = "Draw";
    static string none = "None";

    if (Earmy.army_size() > 0 &&  Aarmy.army_size() == 0) {
        return earth;
    }
    if (Aarmy.army_size() > 0 && Earmy.army_size() == 0) {
        return alien;
    }
    if (Aarmy.army_size() == Earmy.army_size()) {
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
    out_file << "\nInfecton Ratio: "<< (total_earth_soldiers_count() != 0 ? (double) total_infected / total_earth_soldiers_count() : 0) * 100 << "\n";
    out_file << "#Earth Units Generated vs #Alien Units Generated vs #Savers Units Generated"
             << generator->get_Ecount() << " " << generator->get_Acount() << " " << generator->get_Scount() << "\n";
    print_earth_stats(out_file);
    print_alien_stats(out_file);
    print_saver_satats(out_file);
}


int Game::total_earth_soldiers_count() const {
    return Earmy.soliders_count() + killed_earth_soldiers;
}

int Game::total_killed_savers() const {
    return killed_saver_units;
}

void Game::print_earth_stats(ofstream &out_file) const {
    out_file << "====================== Earth Army Stats =====================\n";
    out_file << "ESd / ESTotal: " << (generator->get_Ecount() != 0 ? static_cast<double>(killed_earth_soldiers) / Generator::get_Ecount() : 0) * 100 << "\n";
    out_file << "ETd / ETTotal: " << (generator->get_Ecount() != 0 ? static_cast<double>(killed_earth_tanks) / Generator::get_Ecount() : 0)  * 100 << "\n";
    out_file << "EGd / EGTotal: " << (generator->get_Ecount() != 0 ? static_cast<double>(killed_earth_gunneries) / Generator::get_Ecount() : 0) * 100 << "\n";
    out_file << "Earth Total Killed: " << total_killed_earth() << "\n";
    out_file << "Average Df : " << (total_killed_earth() != 0 ? double(earth_avg_df / total_killed_earth()) : 0) << "\n";
    out_file << "Average Dd : " << (total_killed_earth() != 0 ? double(earth_avg_dd / total_killed_earth()) : 0)  << "\n";
    out_file << "Average Db : " << (total_killed_earth() != 0 ? double(earth_avg_DBb / total_killed_earth()) : 0) << "\n";
    out_file << "Averge Df / Db percentage " << (earth_avg_DBb != 0 ? double(earth_avg_df / earth_avg_DBb) : 0)  * 100 << "\n";
    out_file  << "Averge Dd / Db percentage " << (earth_avg_DBb != 0 ? double(earth_avg_dd / earth_avg_DBb) : 0) * 100  << "\n";
}

void Game::print_saver_satats(ofstream &out_file) const {
    out_file << "====================== Saver Unit Stats =====================\n";
    out_file << "Sud / STotal: " << (generator->get_Scount() != 0 ? static_cast<double>(killed_saver_units) / Generator::get_Scount() : 0) * 100 << "\n";
    out_file << "Saver Total Killed: " << total_killed_savers() << "\n";
    out_file << "Average Df : " << (total_killed_savers() != 0 ? double(saver_ave_df / total_killed_savers()) : 0) << "\n";
    out_file << "Average Dd : " << (total_killed_savers() != 0 ? double(saver_ave_dd / total_killed_savers()) : 0)  << "\n";
    out_file << "Average Db : " << (total_killed_savers() != 0 ? double(saver_ave_DBb / total_killed_savers()) : 0) << "\n";
    out_file << "Averge Df / Db percentage " << (saver_ave_DBb != 0 ? double(saver_ave_df / saver_ave_DBb) : 0)  * 100 << "\n";
    out_file  << "Averge Dd / Db percentage " << (saver_ave_DBb != 0 ? double(saver_ave_dd / saver_ave_DBb) : 0) * 100 << "\n";
}

void Game::print_alien_stats(ofstream &out_file) const {
    out_file << "====================== Alien Army Stats =====================\n";
    out_file << "ASd / ASTotal: " << (generator->get_Acount() != 0 ? static_cast<double>(killed_aliens_soldiers) /  generator->get_Acount(): 0) * 100 << "\n";
    out_file << "AMd / AMTotal: " << (generator->get_Acount() != 0 ? static_cast<double>(killed_aliens_monsters) /  generator->get_Acount(): 0)  * 100 << "\n";
    out_file << "ADd / ADTotal: " << (generator->get_Acount() != 0 ? static_cast<double>(killed_aliens_drones) /  generator->get_Acount(): 0)  * 100 << "\n";
    out_file << "Alien Total Killed: " << total_killed_aliens() << "\n";
    out_file << "Average Df : " << (total_killed_aliens() != 0 ? double(alien_avg_df / total_killed_aliens()) : 0) << "\n";
    out_file << "Average Dd : " << (total_killed_aliens() != 0 ? double(alien_avg_dd / total_killed_aliens()) : 0)  << "\n";
    out_file << "Average Db : " << (total_killed_aliens() != 0 ? double(alien_avg_DBb / total_killed_aliens()) : 0) << "\n";
    out_file << "Averge Df / Db percentage " << (alien_avg_DBb != 0 ? double(alien_avg_df / alien_avg_DBb) : 0)  * 100 << "\n";
    out_file  << "Averge Dd / Db percentage " << (alien_avg_DBb != 0 ? double(alien_avg_dd / alien_avg_DBb) : 0) * 100 << "\n";

}

void Game::incremenat_avg_to_print(ArmyUnit* unit) {
    if (!unit) {
        return;
    }

    if (unit->getTypeId() == earth_tank ||
        unit->getTypeId() == earth_gunnery ||
        unit->getTypeId() == earth_soldier) {
        earth_avg_df += unit->getDf();
        earth_avg_dd += unit->getDd();
        earth_avg_DBb += unit->getDBb();
    } else if (unit->getTypeId() == alien_soldier ||
               unit->getTypeId() == alien_monster ||
               unit->getTypeId() == alien_drone) {
        alien_avg_df += unit->getDf();
        alien_avg_dd += unit->getDd();
        alien_avg_DBb += unit->getDBb();
    }  else if (unit->getTypeId() == saver_unit) {
        saver_ave_df += unit->getDf();
        saver_ave_dd += unit->getDd();
        saver_ave_DBb += unit->getDBb();
    }
}