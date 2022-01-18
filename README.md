# Sea-Snake
Sea-Snake is a command-line implementation of the classic game "snake" written in C++ using the ncurses library, the name is a play on the language name as it was created as approachable project for me to start to learn C++.

It should compile with no issue on linux and mac assuming you have `g++`, `cmake` and `ncurses` installed, releases marked with "Cygwin Compatible" i was able to compile on windows using [Cygwin](https://www.cygwin.com/), but since it's depnednet on `cygwin1.dll` i do not (yet) provide windows executables in the releases, alternativly, on windows you can build and run it in [WSL2](https://docs.microsoft.com/en-us/windows/wsl/about).

## compilation instructions:
Ensure you have `g++`, `cmake`, and `ncurses` installed, if not:
```bash
# install with apt (Ubuntu/Debian):
sudo apt-get install g++ cmake libncurses-dev

# install with Homebrew (Mac):
brew install g++ cmake ncurses

# or some other way...
```

Then download or clone the code, and compile with cmake:
```bash
# from .../sea-snake
mkdir build
cd build
cmake ..
make
```
then run:
```bash
./sea-snake    # for normal ascii mode,
./sea-snake -u # for unicode mode (recommended), or
./sea-snake -h # for additional instructions
```
