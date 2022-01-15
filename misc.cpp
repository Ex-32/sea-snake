#include "misc.h"

int g_game_width {};
int g_game_hight {};

void sleep(int seconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds((seconds*1000)));
}

void sleep_milli(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds((milliseconds)));
}

int random_int(int lower_bound, int upper_bound) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> generator(lower_bound,upper_bound);
    return generator(rng);
}