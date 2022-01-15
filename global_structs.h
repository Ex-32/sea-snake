#pragma once

#ifndef GLOBAL_STRUCTS_H
#define GLOBAL_STRUCTS_H

struct Point2d_int {
    int x{0};
    int y{0};
};

struct Game_State {
    int facing{random_int(0,3)};
    std::vector<Point2d_int> snake_body;
    Point2d_int snake_head;
    Point2d_int fruit;
};

#endif
