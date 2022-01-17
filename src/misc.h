#pragma once

#ifndef MISC_H
#define MISC_H

// for std::random_device, std::mt19937, std::uniform_int_distribution<>
#include <random>
#include <iostream> // for std:cout and std::endl
#include <string>
#include <chrono> // for std::chrono::milliseconds
#include <thread> // for std::this_thread::sleep_for()

#include <ncurses.h> // for endwin()

#include "global_structs.h"

void nc_exit(int exitcode);
void death(int score);

void sleep_milli(int milliseconds);

int random_int(int lower_bound, int upper_bound);

bool same_point2d_int(const Point2d_int& a, const Point2d_int& b);

#endif
