#include "EarthGunnery.h"
#include "../../Game.h"
#include "LinkedQueue.h"

EarthGunnery::EarthGunnery(Game *game, int id, int t, int pw, int hl, int attc) :
        ArmyUnit{game, id, earth_gunnery, t, pw, hl, attc} {}

bool EarthGunnery::operator>(const EarthGunnery &other) const {
    //Priority is based on power + health;
    return (power + health) > (other.power + other.health);
}

void EarthGunnery::attack() {

}
