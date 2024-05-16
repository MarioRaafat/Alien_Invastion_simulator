#include "EarthSoldier.h"
#include "LinkedQueue.h"
#include "../../Game.h"

EarthSoldier::EarthSoldier(Game *game, int id, int t, int pw, int hl, int attc) :
    ArmyUnit(game, id, earth_soldier, t, pw, hl, attc)
{
    count_UML = 0;
    immmune = infected = false;
}

void EarthSoldier::attack() {
    LinkedQueue<ArmyUnit *> temp_alien_soldiers;
    int time_step = game->get_time();
    unit_type pick_type = alien_soldier;

    //inf attack his brothers
    if (infected) {
        pick_type = earth_soldier;
    }


    for (int i = 0; i < attackCapacity; i++) {
        ArmyUnit* curr  = game->pick_unit(pick_type);
        if (curr) {
            temp_alien_soldiers.enqueue(curr);
        }
    }

    if (game->is_interactive()) {
        cout << "ES " << ID << " shots ";
        cout << temp_alien_soldiers;
    }

    while (!temp_alien_soldiers.isEmpty()) {
        ArmyUnit *curr{};

        temp_alien_soldiers.dequeue(curr);

        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }

        damage(curr);

        if (curr->isDead()) {
            curr->setTd(time_step);
            game->add_to_killed_list(curr);
            //dec if the killed unit is infected
            if (curr->getTypeId() == earth_soldier && static_cast<EarthSoldier*>(curr)->get_infection()) {
                game->decrement_infection_number();
            }
        } else {
            if (infected) {
                int random = randomNumber(0, 100);
                if (random < 2) {
                     auto e_solider = static_cast<EarthSoldier*>(curr);
                     //if infected and not immune he can infect
                     if (!e_solider->get_infection() && !e_solider->get_immune()) {
                         e_solider->set_infection(true);
                         game->increment_infection_number();
                     }
                }
                if (should_be_healed()) {
                    game->add_to_soldier_UML(static_cast<EarthSoldier*>(curr));
                    continue;
                }
            }
            game->add_unit(curr, curr->getTypeId());
        }
    }
}

int EarthSoldier::get_count_UML() const {
    return count_UML;
}

void EarthSoldier::set_count_UML(int num) {
    count_UML = num;
}

void EarthSoldier::set_infection(bool infec) {
    if(!immmune){
        infected = infec;
    }
}

bool EarthSoldier::get_infection() const {
    return infected;
}

void EarthSoldier::set_immune(bool im) {
    immmune = im;
}

bool EarthSoldier::get_immune() const {
    return immmune;
}

int EarthSoldier::randomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

bool EarthSoldier::operator>(const EarthSoldier &other) const {
    return this->power > other.power;
}

std::ostream &operator<<(ostream &os, const EarthSoldier &soldier) {
    os <<  "(" << soldier.getID() << "->" << soldier.getHealth() << ")";
    if (soldier.get_infection()) {
        os << "->Inf";
    }
    if (soldier.get_immune()) {
        os << "->Imm";
    }
    return (os);
}

bool EarthSoldier::is_healed() const {
   return ((double)getHealth()) > ((double)this->getOriginalHealth() * 0.2);
}

bool EarthSoldier::should_be_healed() const {
    if (!isDead() && (double)getHealth() < ((double)this->getOriginalHealth() * 0.2)) {
        return true;
    }
    return false;
}
