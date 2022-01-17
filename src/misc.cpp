#include "misc.h"

void nc_exit(int exitcode) {
    endwin(); // deallocates memory and ends ncurses
    std::exit(exitcode);
}

void death(int score) {
    endwin(); // deallocates memory and ends ncurses
    std::cout << "Your score was: " << score << std::endl; // prints exit message
    std::exit(0);
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

bool same_point2d_int(const Point2d_int& a, const Point2d_int& b) {
    if ((a.x == b.x) && (a.y == b.y)) return true;
    else return false;
}
