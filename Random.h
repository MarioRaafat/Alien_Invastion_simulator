#ifndef ALIEN_INVASTION_SIMULATOR_RANDOM_H
#define ALIEN_INVASTION_SIMULATOR_RANDOM_H

int randomNum(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
#endif //ALIEN_INVASTION_SIMULATOR_RANDOM_H
