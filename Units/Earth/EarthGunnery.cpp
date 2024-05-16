#include "EarthGunnery.h"
#include "../../Game.h"
#include "LinkedQueue.h"
#include "ArrayStack.h"

EarthGunnery::EarthGunnery(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit{game, id, earth_gunnery, t, pw, hl, attc} {}

/**
 * @brief
 * @param other
 * @return true if obj has more power + health than other obj
 */
bool EarthGunnery::operator>(const EarthGunnery &other) const {
    return (power + health) > (other.power + other.health);
}

/**
 * @brief attack the alien units drones and monsters
 * return drones in there place in the front and back if not killed
  * using the attack capacity to attack the alien units
  * higher priority to the drones
 */
void EarthGunnery::attack() {
    LinkedQueue<ArmyUnit*> temp_alien_units;
    ArrayStack<ArmyUnit*> front_unit;
    ArrayStack<ArmyUnit*> back_unit;

    //to push the alien units in the front and back
    bool front = true;

     for (int i = 0; i < (getAttackCapacity() - getAttackCapacity() / 2); ++i) {
         ArmyUnit* curr = game->pick_unit(alien_monster);
         if (curr) {
             temp_alien_units.enqueue(curr);
         }
     }

     for (int i = 0; i < getAttackCapacity() / 2; ++i) {
         //if Exists one get it
         ArmyUnit *curr = game->pick_unit(alien_drone,front, true);
         if (curr) {
             temp_alien_units.enqueue(curr);
         }
         //Toggle the front
         front = !front;
     }

     if (game->is_interactive()) {
         cout << "EG " << ID << " shots ";
         cout << temp_alien_units;
     }

     //reset front
     front = true;
     //Damages and kills the alien units except drones handling is below
     while (!temp_alien_units.isEmpty()) {
         ArmyUnit* curr{};
         temp_alien_units.dequeue(curr);

         if (curr->getTypeId() == alien_drone) {
             if (front) {
                 front_unit.push(curr);
             } else {
                 back_unit.push(curr);
             }
             //toggle the front
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

     //Adding fron to front and back to back with relative order of the drones and if killed to the killed list
     while (!front_unit.isEmpty()) {
         ArmyUnit *curr{};
         front_unit.pop(curr);
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

     while (!back_unit.isEmpty()) {
         ArmyUnit *curr{};
         back_unit.pop(curr);
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