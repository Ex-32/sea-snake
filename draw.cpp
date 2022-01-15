#include "draw.h"

void reset_screen(void) {
    clear();
    move(0,0);
}

void print_point(Point2d_int point, const char* str) {
    mvprintw(point.y,(point.x*2),str);
}

void draw_frame(Game_State* current_state) {
    clear();

    int snake_len = current_state -> snake_body.size();
    for (int i{0}; i < snake_len; ++i) {
        print_point(current_state -> snake_body[i],"##");
    }

    refresh();

}

void draw_start() {
    reset_screen();

}

void draw_death() {
    reset_screen();

}
