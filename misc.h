#pragma once

#ifndef MISC_H
#define MISC_H

// for std::random_device, std::mt19937, std::uniform_int_distribution<>
#include <random>

#include <ncurses.h> // for endwin()

#include "global_structs.h"

void nc_exit(int exitcode);

int random_int(int lower_bound, int upper_bound);

bool same_point2d_int(Point2d_int a, Point2d_int b);

#endif
