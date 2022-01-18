#pragma once

#ifndef GLOBAL_STRUCTS_H
#define GLOBAL_STRUCTS_H

#include <list>

// these are declred at the top of main.cpp
extern bool g_arg_wide_mode;
extern bool g_arg_skip_menu;
extern int g_arg_speed;
extern int g_arg_increment;
extern int g_arg_max_speed;

struct Point2d_int {
    int x{0};
    int y{0};
};

struct Game_State {
    int game_width;
    int game_height;
    int game_size;
    int facing;
    std::list<Point2d_int> snake_body;
    unsigned int snake_length;
    Point2d_int fruit;
    int speed;
};

#endif
