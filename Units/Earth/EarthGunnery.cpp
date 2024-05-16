#include "EarthGunnery.h"
#include "../../Game.h"
#include "LinkedQueue.h"
#include "ArrayStack.h"

EarthGunnery::EarthGunnery(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit{game, id, earth_gunnery, t, pw, hl, attc} {}

bool EarthGunnery::operator>(const EarthGunnery &other) const {
    //Priority is based on power + health;
    return (power + health) > (other.power + other.health);
}

void EarthGunnery::attack() {

    LinkedQueue<ArmyUnit*> temp_alien_units;
    Dequeue<ArmyUnit*> front_unit;
    Dequeue<ArmyUnit*> back_unit;

    bool front = true;

     for (int i = 0; i < (getAttackCapacity() - getAttackCapacity() / 2); ++i) {
         ArmyUnit* curr = game->pick_unit(alien_monster);
         if (curr) {
             temp_alien_units.enqueue(curr);
         }
     }

     for (int i = 0; i < getAttackCapacity() / 2; ++i) {
         ArmyUnit *curr = game->pick_unit(alien_drone,front, true);
         if (curr) {
             temp_alien_units.enqueue(curr);
         }
         front = !front;
     }

     if (game->is_interactive()) {
         cout << "EG " << ID << " shots ";
         cout << temp_alien_units;
     }

     front = true;
     while (!temp_alien_units.isEmpty()) {
         ArmyUnit* curr{};
         temp_alien_units.dequeue(curr);

         if (curr->getTypeId() == alien_drone) {
             if (front) {
                 front_unit.push_front(curr);
             } else {
                 back_unit.push_front(curr);
             }
             front = !front;
             continue;
         }

         if (!curr->is_attacked()) {
             curr->setTa(game->get_time());
         }

         damage(curr);

         if (curr->isDead()) {
             curr->setTd(game->get_time());
             game->add_to_killed_list(curr);
         } else {
             game->add_unit(curr, curr->getTypeId());
         }
     }

     while (!front_unit.is_empty()) {
         ArmyUnit *curr{};
         front_unit.pop_front(curr);
         if (!curr->is_attacked()) {
             curr->setTa(game->get_time());
         }

         damage(curr);
         if (curr->isDead()) {
             curr->setTd(game->get_time());
             game->add_to_killed_list(curr);
         } else {
             game->add_unit(curr, curr->getTypeId(), true);
         }
     }

     while (!back_unit.is_empty()) {
         ArmyUnit *curr{};
         back_unit.pop_front(curr);
         if (!curr->is_attacked()) {
             curr->setTa(game->get_time());
         }

         damage(curr);
         if (curr->isDead()) {
             curr->setTd(game->get_time());
             game->add_to_killed_list(curr);
         } else {
             game->add_unit(curr, curr->getTypeId(), false);
         }
     }
}