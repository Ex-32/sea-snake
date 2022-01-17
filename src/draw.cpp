#include "draw.h"

// prints string (designed to be 2 chars long) at x*2, y
// 'w" version prints long unicode chars
void w_print_point(const Point2d_int& point, const wchar_t* wstr) {
    mvaddwstr(point.y,(point.x*2),wstr);
}
void print_point(const Point2d_int& point, const char* str) {
    mvprintw(point.y,(point.x*2),str);
}
void print_centered_string(const Game_State& current_state, std::string msg, int y_offset) {
    // calculate offset from string length
    int msg_length{static_cast<int>(msg.length())};
    int x_offset{msg_length/2};
    // since game_width assumes blocks of 2 charaters
    // the value doesn't have to be halved
    int middle_x{current_state.game_width};
    int middle_y{current_state.game_height / 2};

    mvprintw((middle_y+y_offset),(middle_x-x_offset),msg.c_str());
}

// draw the snake and fruit from a Game_State struct
// 'w" version prints long unicode chars
void w_draw_frame(const Game_State& current_state) {
    erase();

    // prints a "██" in every "tile" of the snake_body list
    for (const auto& snake_segment : (current_state.snake_body)) {
        w_print_point(snake_segment,L"██");
    }

    // prints a "▒▒" in the "tile" of the fruit
    w_print_point((current_state.fruit),L"░░");

    refresh();
}
void draw_frame(const Game_State& current_state) {
    erase();

    // prints a "##" in every "tile" of the snake_body list
    for (const auto& snake_segment : (current_state.snake_body)) {
        print_point(snake_segment,"##");
    }

    // prints a "@@" in the "tile" of the fruit
    print_point((current_state.fruit),"@@");

    refresh();
}

// draws a basic text screen showing a start and death screen
void draw_start(const Game_State& current_state) {

    std::string title{"Wellcome to Sea-Snake!"};
    std::string subtitle{"(Press any key to start)"};

    clear();
    print_centered_string(current_state,title,-1);
    print_centered_string(current_state,subtitle,1);
    refresh();
    await_key();

}
void draw_death(const Game_State& current_state) {

    std::string title{"You died :("};
    std::ostringstream str_stream;
    str_stream << "Your score was: " << current_state.snake_length;
    std::string subtitle{str_stream.str()};
    std::string subtitle2{"(Press any key to close)"};

    clear();
    print_centered_string(current_state,title,-1);
    print_centered_string(current_state,subtitle,1);
    print_centered_string(current_state,subtitle2,2);
    refresh();
    await_key();

    nc_exit(0);

}