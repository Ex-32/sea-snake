#pragma once

#ifndef GLOBAL_STRUCTS_H
#define GLOBAL_STRUCTS_H

#include <list>
#include <ncurses.h>

// these are declred at the top of main.cpp
#ifndef NO_UNICODE
extern bool g_arg_wide_mode;
#endif
extern bool g_arg_skip_menu;
extern int g_arg_speed;
extern int g_arg_increment;
extern int g_arg_max_speed;
extern int g_console_width;
extern int g_console_hight;

struct Point2d_int {
    int x{0};
    int y{0};
};

struct Game_State {
    WINDOW* game_window;
    int game_width;
    int game_height;
    unsigned int game_size;
    int facing;
    std::list<Point2d_int> snake_body;
    unsigned int snake_length;
    Point2d_int fruit;
    int speed;
};

#endif
