#pragma once

#ifndef GLOBAL_STRUCTS_H
#define GLOBAL_STRUCTS_H

#include <list>

struct Point2d_int {
    int x{0};
    int y{0};
};

struct Game_State {
    int game_width;
    int game_height;
    int facing;
    std::list<Point2d_int> snake_body;
    unsigned int snake_length;
    Point2d_int fruit;
    int speed;
};

#endif
