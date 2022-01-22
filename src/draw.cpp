#include "draw.h"

//////////////////////////////////////////
// START SECTION 0: Printing game tiles //
//////////////////////////////////////////

// prints different parts of the game onto screen
// 'w' version prints "wide" (unicode) chars
#ifndef NO_UNICODE

// prints "██" at head location from current game state
void _w_print_head(const Game_State& current_state) {
    mvwaddwstr(
        current_state.game_window,
        current_state.snake_head.y,
        (current_state.snake_head.x*2),
        L"██"
    );
}

// loops over body positions and prints "▓▓"
// at each location from current game state
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

// prints "░░" at fruit location from current game state
void _w_print_fruit(const Game_State& current_state) {
    mvwaddwstr(
        current_state.game_window,
        current_state.fruit.y,
        (current_state.fruit.x*2),
        L"░░"
    );
}

#endif

// prints "@@" at head location from current game state
void _print_head(const Game_State& current_state) {
    mvwprintw(
        current_state.game_window,
        current_state.snake_head.y,
        (current_state.snake_head.x*2),
        "@@"
    );
}

// loops over body positions and prints "%%"
// at each location from current game state
void _print_body(const Game_State& current_state) {
    for (const auto& snake_segment : (current_state.snake_body)) {
        mvwprintw(
            current_state.game_window,
            snake_segment.y,
            (snake_segment.x*2),
            "%%%%" // "%%" but percent signes need to be escaped
        );
    }
}

// prints "##" at fruit location from current game state
void _print_fruit(const Game_State& current_state) {
    mvwprintw(
        current_state.game_window,
        current_state.fruit.y,
        (current_state.fruit.x*2),
        "##"
    );
}

////////////////////////////////////////
// END SECTION 0: Printing game tiles //
////////////////////////////////////////

//////////////////////////////////////////
// START SECTION 1: Coloring game tiles //
//////////////////////////////////////////

// apply colors to the snake head
draw_point_ptr g_color_head_internal;
void _color_head(const Game_State& current_state) {
    wattron(current_state.game_window,COLOR_PAIR(HEAD_PAIR));
    g_color_head_internal(current_state);
    wattroff(current_state.game_window,COLOR_PAIR(HEAD_PAIR));
}

// apply colors to the snake body
draw_point_ptr g_color_body_internal;
void _color_body(const Game_State& current_state) {
    wattron(current_state.game_window,COLOR_PAIR(BODY_PAIR));
    g_color_body_internal(current_state);
    wattroff(current_state.game_window,COLOR_PAIR(BODY_PAIR));
}

// apply colors to fruit
draw_point_ptr g_color_fruit_internal;
void _color_fruit(const Game_State& current_state) {
    wattron(current_state.game_window,COLOR_PAIR(FRUIT_PAIR));
    g_color_fruit_internal(current_state);
    wattroff(current_state.game_window,COLOR_PAIR(FRUIT_PAIR));
}

////////////////////////////////////////
// END SECTION 1: Coloring game tiles //
////////////////////////////////////////

//////////////////////////////////////////////////////////
// START SECTION 2: Printing and coloring window border //
//////////////////////////////////////////////////////////

#define VERTICAL_SIDE '|'
#define HORIZONTAL_SIDE '-'
#define CORNER '@'

// draw box around play field
#ifndef NO_UNICODE
void _w_print_box(WINDOW* screen) {
    wborder(screen,0,0,0,0,0,0,0,0); // 0 indicates defaut value
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

// color play field
draw_box_ptr g_color_box_internal;
void _color_box(WINDOW* screen) {
    wattron(screen,COLOR_PAIR(BOX_PAIR));
    g_color_box_internal(screen);
    wattroff(screen,COLOR_PAIR(BOX_PAIR));
}

////////////////////////////////////////////////////////
// END SECTION 2: Printing and coloring window border //
////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// START SECTION 3: Initialize frawing function pointers, and drawing frame //
//////////////////////////////////////////////////////////////////////////////

bool draw_init(void) {

    // assign draw pointers based on weather or not unicode was enabled
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

    // if in color mode,
    if (g_arg_color_mode) {

        // initialize ncurses color,
        start_color();

        // define color pairs,
        init_pair(HEAD_PAIR, COLOR_BLUE, COLOR_BLUE);
        init_pair(BODY_PAIR, COLOR_BLUE, COLOR_CYAN);
        init_pair(FRUIT_PAIR, COLOR_RED, COLOR_RED);
        init_pair(BOX_PAIR, COLOR_RED, COLOR_BLACK);

        // assign existing draw pointers to "internal" varaibles,
        g_color_head_internal = g_draw_head;
        g_color_body_internal = g_draw_body;
        g_color_fruit_internal = g_draw_fruit;
        g_color_box_internal = g_draw_box;

        // assign colorizers to draw pointers,
        g_draw_head = _color_head;
        g_draw_body = _color_body;
        g_draw_fruit = _color_fruit;
        g_draw_box = _color_box;

        // null pointer sanity checks,
        if (
            (g_color_head_internal   == nullptr) ||
            (g_color_body_internal   == nullptr) ||
            (g_color_fruit_internal  == nullptr) ||
            (g_color_box_internal    == nullptr)
        ) {
            return false;
        }
    }

    // more null pointer sanity checks,
    if (
        (g_draw_head  == nullptr) ||
        (g_draw_body  == nullptr) ||
        (g_draw_fruit == nullptr) ||
        (g_draw_box   == nullptr)
    ) {
        return false;
    } else {
        return true;
    }
}

// draw the snake and fruit from a Game_State struct
void draw_frame(const Game_State& current_state) {

    werase(current_state.game_window);

    g_draw_head(current_state);
    g_draw_body(current_state);
    g_draw_fruit(current_state);

    g_draw_box(current_state.game_window);

    wrefresh(current_state.game_window);
}

////////////////////////////////////////////////////////////////////////////
// END SECTION 3: Initialize frawing function pointers, and drawing frame //
////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// START SECTION 4: draw start, death, and win  messages //
///////////////////////////////////////////////////////////

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
void draw_start(const Game_State& current_state) {

    // display start messages
    std::string title{"Wellcome to Sea-Snake!"};
    std::string subtitle{"(Press any key to start)"};
    clear();
    print_centered_string(current_state,title,-1);
    print_centered_string(current_state,subtitle,1);
    refresh();

    // wait for keystroke, then start
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

/////////////////////////////////////////////////////////
// END SECTION 4: draw start, death, and win  messages //
/////////////////////////////////////////////////////////
