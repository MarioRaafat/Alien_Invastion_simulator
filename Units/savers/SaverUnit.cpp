//
// Created by mario on 5/15/2024.
//

#include "SaverUnit.h"
#include "../../Game.h"

SaverUnit::SaverUnit(Game *game, int id, int t, int pw, int hl, int attc) :
////////Ya Mariooooooooo
///55555555555555555555555555555555555555555555555555555555
///EarthSolider y3m 3amal adr al error gy mnin w 3amal include lel EarthSoldier
//ysts kosom al d7k al copilot by auto compolete al 4taim m3aia wa bl franko ::::::::::::::::::::::::::D
//copilot: bt3rf t45r?
//ana: la2
//Lollllllll
//copilot bt3rf t4tm tyb ?
//ana: la2
//anta mod2b ?
//ans: la2 bardo !?

        ArmyUnit {game, id, saver_unit, t, pw, hl, attc}
{}

void SaverUnit::attack() {

//    if (game->getFightSaversState() != 1) {//means no fight
//        return;
//    }
    LinkedQueue<ArmyUnit *> temp;
    int time_step = game->get_time();

    //size_t alien_soldier_size = game->getAlienArmy().soldiers_count();

    for (int i = 0; i < attackCapacity; i++) {
        ArmyUnit *curr;
        curr = game->pick_unit(alien_soldier);

        if (curr) {
            temp.enqueue(curr);
        }
    }

    if (game->is_interactive()) {
        cout << "SU " << ID << " shots ";
        cout << temp;
    }

    while (!temp.isEmpty()) {
        ArmyUnit *curr{};

        temp.dequeue(curr);

        if (!curr->is_attacked()) {
            curr->setTa(time_step);
        }

        damage(curr);

        if (curr->isDead()) {
            curr->setTd(time_step);
            game->add_to_killed_list(curr);
        } else {
            game->add_unit(curr, curr->getTypeId());
        }
    }
}
