#include "draw.h"


#define HEAD_PAIR   1
#define BODY_PAIR   2
#define FRUIT_PAIR  3
#define BOX_PAIR    4


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

void _w_print_head(const Game_State& current_state) {
    mvwaddwstr(
        current_state.game_window,
        current_state.snake_head.y,
        (current_state.snake_head.x*2),
        L"██"
    );
}

void _w_print_body(const Game_State& current_state) {
    for (const auto& snake_segment : (current_state.snake_body)) {
        mvwaddwstr(
            current_state.game_window,
            snake_segment.y,
            (snake_segment.x*2),
            L"▓▓"
        );
    }
}

void _w_print_fruit(const Game_State& current_state) {
    mvwaddwstr(
        current_state.game_window,
        current_state.fruit.y,
        (current_state.fruit.x*2),
        L"░░"
    );
}

#endif

void _print_head(const Game_State& current_state) {
    mvwprintw(
        current_state.game_window,
        current_state.snake_head.y,
        (current_state.snake_head.x*2),
        "@@"
    );
}

void _print_body(const Game_State& current_state) {
    for (const auto& snake_segment : (current_state.snake_body)) {
        mvwprintw(
            current_state.game_window,
            snake_segment.y,
            (snake_segment.x*2),
            "%%%%"
        );
    }
}

void _print_fruit(const Game_State& current_state) {
    mvwprintw(
        current_state.game_window,
        current_state.fruit.y,
        (current_state.fruit.x*2),
        "##"
    );
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
void _color_head(const Game_State& current_state) {
    wattron(screen,COLOR_PAIR(HEAD_PAIR));
    g_color_head_internal(current_state);
    wattroff(screen,COLOR_PAIR(HEAD_PAIR));
}

draw_point_ptr g_color_body_internal;
void _color_body(const Game_State& current_state) {
    wattron(screen,COLOR_PAIR(BODY_PAIR));
    g_color_body_internal(current_state);
    wattroff(screen,COLOR_PAIR(BODY_PAIR));
}

draw_point_ptr g_color_fruit_internal;
void _color_fruit(const Game_State& current_state) {
    wattron(screen,COLOR_PAIR(FRUIT_PAIR));
    g_color_fruit_internal(current_state);
    wattroff(screen,COLOR_PAIR(FRUIT_PAIR));
}

draw_box_ptr g_color_box_internal;
void _color_box(WINDOW* screen) {
    wattron(screen,COLOR_PAIR(BOX_PAIR));
    g_color_box_internal(screen);
    wattroff(screen,COLOR_PAIR(BOX_PAIR));
}

bool draw_init(void) {

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

        init_pair(HEAD_PAIR, COLOR_BLUE, COLOR_BLUE);
        init_pair(BODY_PAIR, COLOR_BLUE, COLOR_CYAN);
        init_pair(FRUIT_PAIR, COLOR_RED, COLOR_RED);
        init_pair(BOX_PAIR, COLOR_RED, COLOR_BLACK);

        g_color_head_internal = g_draw_head;
        g_color_body_internal = g_draw_body;
        g_color_fruit_internal = g_draw_fruit;
        g_color_box_internal = g_draw_box;

        g_draw_head = _color_head;
        g_draw_body = _color_body;
        g_draw_fruit = _color_fruit;
        g_draw_box = _color_box;
    }

    return true;

}



// draw the snake and fruit from a Game_State struct
void draw_frame(const Game_State& current_state) {

    werase(current_state.game_window);

    g_draw_head(current_state.game_window,current_state.snake_head);

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
