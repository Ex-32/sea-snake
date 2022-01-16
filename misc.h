#pragma once

#ifndef MISC_H
#define MISC_H

#include <chrono> // used sleep_milli()
#include <thread> // used sleep_milli()
#include <random> // used in random_int()

#include <ncurses.h> // used in nc_exit()

#include "global_structs.h"

void nc_exit(int exitcode);

void sleep_milli(int milliseconds);

int random_int(int lower_bound, int upper_bound);

bool same_point2d_int(Point2d_int a, Point2d_int b);

#endif
