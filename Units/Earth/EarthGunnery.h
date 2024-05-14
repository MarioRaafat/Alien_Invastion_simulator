#ifndef EARTHGUNNERY_H
#define EARTHGUNNERY_H


#include "../ArmyUnit.h"

class EarthGunnery : public ArmyUnit {
public:
    EarthGunnery(Game *game, int id, int t, int pw, int hl, int attc);
    void attack() override;
    bool operator>(const EarthGunnery &other) const;
};


#endif //EARTHGUNNERY_H
