cmake_minimum_required(VERSION 3.8)

project("sea-snake")

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED)

# include local "include" folder with local libraires
include_directories("./include")

find_library(NCURSES_LIB ncurses)
link_libraries("${NCURSES_LIB}")

add_executable(sea-snake "main.cpp" "draw.cpp" "game_tick.cpp" "misc.cpp")

target_compile_options(sea-snake PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
