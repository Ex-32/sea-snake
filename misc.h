#pragma once

#ifndef MISC_H
#define MISC_H

#include <chrono> // used in sleep() and sleep_milli()
#include <thread> // used in sleep() and sleep_milli()

#include <random> // used in random_int()

#include <vector> // used in Game_State

extern int g_game_width;
extern int g_game_hight;

void sleep(int seconds);
void sleep_milli(int milliseconds);

int random_int(int lower_bound, int upper_bound);

#endif
