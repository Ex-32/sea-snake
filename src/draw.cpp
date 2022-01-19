#include "draw.h"

// different kinds of blocks onto screen
// 'w' version prints long unicode chars
#ifndef NO_UNICODE
void _w_print_head(WINDOW* screen, const Point2d_int& point) {
    mvwaddwstr(screen,point.y,(point.x*2),L"██");
}
void _w_print_body(WINDOW* screen, const Point2d_int& point) {
    mvwaddwstr(screen,point.y,(point.x*2),L"██");
}
void _w_print_fruit(WINDOW* screen, const Point2d_int& point) {
    mvwaddwstr(screen,point.y,(point.x*2),L"░░");
}
#endif
void _print_head(WINDOW* screen, const Point2d_int& point) {
    mvwprintw(screen,point.y,(point.x*2),"@@");
}
void _print_body(WINDOW* screen, const Point2d_int& point) {
    mvwprintw(screen,point.y,(point.x*2),"@@");
}
void _print_fruit(WINDOW* screen, const Point2d_int& point) {
    mvwprintw(screen,point.y,(point.x*2),"##");
}

void print_centered_string(const Game_State& current_state, std::string msg, int y_offset) {
    // calculate offset from string length
    int msg_length{static_cast<int>(msg.length())};
    int x_offset{msg_length/2};
    // since game_width assumes blocks of 2 charaters
    // the x value doesn't have to be halved
    int middle_x{current_state.game_width};
    int middle_y{current_state.game_height / 2};

    mvprintw((middle_y+y_offset),(middle_x-x_offset),msg.c_str());
}

#define VERTICAL_SIDE '|'
#define HORIZONTAL_SIDE '-'
#define CORNER '@'

#ifndef NO_UNICODE
void _w_print_box(WINDOW* screen) {
    wborder(screen,0,0,0,0,0,0,0,0);
}
#endif
void _print_box(WINDOW* screen) {
    wborder(
        screen,
        VERTICAL_SIDE,VERTICAL_SIDE,
        HORIZONTAL_SIDE,HORIZONTAL_SIDE,
        CORNER,CORNER,CORNER,CORNER
    );
}

// draw the snake and fruit from a Game_State struct
void draw_frame(const Game_State& current_state) {

    werase(current_state.game_window);

    // prints a "@@" in every "tile" of the snake_body list
    for (const auto& snake_segment : (current_state.snake_body)) {
        _w_print_body(current_state.game_window,snake_segment);
    }

    // prints a "##" in the "tile" of the fruit
    _w_print_fruit(current_state.game_window,current_state.fruit);

    _w_print_box(current_state.game_window);
    wrefresh(current_state.game_window);
}

// basic text screens showing a start, death, and win messages
void draw_start(const Game_State& current_state) {

    // display start messages
    std::string title{"Wellcome to Sea-Snake!"};
    std::string subtitle{"(Press any key to start)"};
    clear();
    print_centered_string(current_state,title,-1);
    print_centered_string(current_state,subtitle,1);
    refresh();

    // wait for keystroke
    await_key();

}
void draw_death(const Game_State& current_state) {

    // display death message
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

    // wait for user to realize they died, then wait for keystroke, then exit
    sleep_milli(300);
    await_key();
    nc_exit(0);

}
void draw_win(const Game_State& current_state) {

    // display wining message
    std::string title{"You Win!"};
    std::ostringstream str_stream;
    str_stream << "Your score was: " << current_state.snake_length;
    std::string subtitle{str_stream.str()};
    std::string subtitle2{"(Press any key to close)"};
    clear();
    print_centered_string(current_state,title,-1);
    print_centered_string(current_state,subtitle,1);
    print_centered_string(current_state,subtitle2,2);
    refresh();

    // wait for user to realize they won, then wait for keystroke, then exit
    sleep_milli(300);
    await_key();
    nc_exit(0);

}
