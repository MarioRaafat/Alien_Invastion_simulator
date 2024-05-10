#include "Game.h"

int main()
{
    Game game;
    game.phase1Test();
    return 0;
}

// if 0<X<10, pick ES from its list and insert it again
// if 10<X<20, pick ET from its list and move it to Killed list
// if 20<X<30, pick EG from its list, decrement its health to its half then insert it again
// if 30<X<40, pick 5 AS from their list dec their health and instert them again
// if 40<X<50, pick 5 Monsters from their list and insert them again
// if 50<X<60, pick 6 drones, from front and rear of their list and move them to Killed List