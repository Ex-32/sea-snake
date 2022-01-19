#pragma once

#ifndef GLOBAL_STRUCTS_H
#define GLOBAL_STRUCTS_H

#include <list> // for std::list
#include <chrono> // for std::chrono::duration
#include <ncurses.h>

// these are declred at the top of main.cpp
#ifndef NO_UNICODE
extern bool g_arg_wide_mode;
#endif
extern bool g_arg_color_mode;
extern bool g_arg_skip_menu;
extern int g_arg_speed;
extern int g_arg_increment;
extern int g_arg_max_speed;
extern int g_console_width;
extern int g_console_hight;

// politely explaining to the program that milliseconds do, in fact,
// exist and a duration of them should be called "millisec_type"
typedef std::chrono::duration<int,std::milli> millisec_type;

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
    //Point2d_int snake_head;
    std::list<Point2d_int> snake_body;
    unsigned int snake_length;
    Point2d_int fruit;
    int speed;
};

typedef void (*draw_point_ptr)(WINDOW*,const Point2d_int&);
typedef void (*draw_box_ptr)(WINDOW*);

#endif
