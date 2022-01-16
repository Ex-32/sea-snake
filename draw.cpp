#include "draw.h"

// prints string (designed to be 2 chars long) at x*2, y
void print_point(Point2d_int point, const char* str) {
    mvprintw(point.y,(point.x*2),str);
}

// draw the snake and fruit from a Game_State struct
void draw_frame(Game_State current_state) {
    clear();

    // prints a "##" in every "tile" of the snake_body list
    for (const auto& snake_segment : (current_state.snake_body)) {
        print_point(snake_segment,"##");
    }

    // prints a "@@" in the "tile" of the fruit
    print_point((current_state.fruit),"@@");

    refresh();

}

// // TODO: add start and death screens
// void draw_start() {
// }

// void draw_death() {
// }
