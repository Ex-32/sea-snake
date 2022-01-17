cmake_minimum_required(VERSION 3.8)

project("sea-snake")

# C++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED)

# find ncursesw library on system
find_library(NCURSESW_LIB ncursesw)

# add sea-snake executable
add_executable(sea-snake "./src/main.cpp" "./src/draw.cpp" "./src/game_tick.cpp" "./src/misc.cpp")

# add local include folder to nprimes target
target_include_directories(sea-snake PRIVATE "./include")

# add ncurses library to sea-snake
target_link_libraries(sea-snake PRIVATE "${NCURSESW_LIB}")

# add warning and optimization flags
target_compile_options(sea-snake PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /O2>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -O2>
)
