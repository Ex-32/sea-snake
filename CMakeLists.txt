cmake_minimum_required(VERSION 3.8)

project("sea-snake")

# C++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED)

# find ncurses(w) library on system
if(APPLE)
  find_library(NCURSES_LIB ncurses)
else(APPLE)
  find_library(NCURSES_LIB ncursesw)
endif(APPLE)

# add sea-snake executable
add_executable(sea-snake "./src/main.cpp" "./src/draw.cpp" "./src/game_tick.cpp" "./src/misc.cpp")

# add local include folder to nprimes target
target_include_directories(sea-snake PRIVATE "./include")

# must be defined for ncurses wide mode to work on certain platforms
# (looking at you apple)
target_compile_options(sea-snake PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>: /D_XOPEN_SOURCE_EXTENDED >
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -D_XOPEN_SOURCE_EXTENDED >
)

# add ncurses library to sea-snake
target_link_libraries(sea-snake PRIVATE "${NCURSES_LIB}")

# add warning flags
target_compile_options(sea-snake PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>: /W4 >
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -Wpedantic >
)

# add optimization flags
target_compile_options(sea-snake PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>: /O2 >
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -O2 >
)
