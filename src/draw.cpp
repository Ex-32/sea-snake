#include "draw.h"


#define HEAD_PAIR   1
#define BODY_PAIR   2
#define FRUIT_PAIR  3
#define BACK_PAIR   4
#define BOX_PAIR    5


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

void _print_back(WINDOW* screen, const Point2d_int& point) {
    mvwprintw(screen,point.y,(point.x*2)," .");
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


draw_point_ptr g_color_head_internal;
void _color_head(WINDOW* screen, const Point2d_int& point) {
    wattron(screen,COLOR_PAIR(HEAD_PAIR));
    g_color_head_internal(screen,point);
    wattroff(screen,COLOR_PAIR(HEAD_PAIR));
}

draw_point_ptr g_color_body_internal;
void _color_body(WINDOW* screen, const Point2d_int& point) {
    wattron(screen,COLOR_PAIR(BODY_PAIR));
    g_color_body_internal(screen,point);
    wattroff(screen,COLOR_PAIR(BODY_PAIR));
}

draw_point_ptr g_color_fruit_internal;
void _color_fruit(WINDOW* screen, const Point2d_int& point) {
    wattron(screen,COLOR_PAIR(FRUIT_PAIR));
    g_color_fruit_internal(screen,point);
    wattroff(screen,COLOR_PAIR(FRUIT_PAIR));
}

draw_point_ptr g_color_back_internal;
void _color_back(WINDOW* screen, const Point2d_int& point) {
    wattron(screen,COLOR_PAIR(BACK_PAIR));
    g_color_back_internal(screen,point);
    wattroff(screen,COLOR_PAIR(BACK_PAIR));
}

draw_box_ptr g_color_box_internal;
void _color_box(WINDOW* screen) {
    wattron(screen,COLOR_PAIR(BOX_PAIR));
    g_color_box_internal(screen);
    wattroff(screen,COLOR_PAIR(BOX_PAIR));
}

bool draw_init(void) {

    g_draw_back = _print_back;

    #ifndef NO_UNICODE
    if (g_arg_wide_mode) {
        g_draw_head = _w_print_head;
        g_draw_body = _w_print_body;
        g_draw_fruit = _w_print_fruit;
        g_draw_box = _w_print_box;
    } else {
    #endif
        g_draw_head = _print_head;
        g_draw_body = _print_body;
        g_draw_fruit = _print_fruit;
        g_draw_box = _print_box;
    #ifndef NO_UNICODE
    }
    #endif

    if (g_arg_color_mode) {

        start_color();

        init_pair(HEAD_PAIR, COLOR_CYAN, COLOR_CYAN);
        init_pair(BODY_PAIR, COLOR_BLUE, COLOR_BLUE);
        init_pair(FRUIT_PAIR, COLOR_RED, COLOR_YELLOW);
        init_pair(BACK_PAIR, COLOR_YELLOW, COLOR_GREEN);
        init_pair(BODY_PAIR, COLOR_RED, COLOR_GREEN);

        g_color_head_internal = g_draw_head;
        g_color_body_internal = g_draw_body;
        g_color_fruit_internal = g_draw_fruit;
        g_color_back_internal = g_draw_back;
        g_color_box_internal = g_draw_box;

        g_draw_head = _color_head;
        g_draw_body = _color_body;
        g_draw_fruit = _color_fruit;
        g_draw_back = _color_back;
        g_draw_box = _color_box;
    }

    return true;

}



// draw the snake and fruit from a Game_State struct
void draw_frame(const Game_State& current_state) {

    werase(current_state.game_window);

    for (const auto& snake_segment : (current_state.snake_body)) {
        g_draw_body(current_state.game_window,snake_segment);
    }

    g_draw_fruit(current_state.game_window,current_state.fruit);

    g_draw_box(current_state.game_window);
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

    // wait for user to realize they died, then wait for keystroke, then exit
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
