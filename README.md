# Sea-Snake
Sea-Snake is a command-line implementation of the classic game "snake" written in C++ using the ncurses library, the name is a play on the language name as it was created as approachable project for me to start to learn C++.

It should compile with no issue on linux and mac assuming you have `g++`, `cmake` and `ncurses` installed, releases marked with "Cygwin Compatible" i was able to compile on windows using [Cygwin](https://www.cygwin.com/), but since it's dependent on `cygwin1.dll` i do not (yet) provide windows executables in the releases, alternatively, on windows you can build and run it in [WSL2](https://docs.microsoft.com/en-us/windows/wsl/about).

## build instructions:
Ensure you have `g++`, `cmake`, and `ncurses` installed:

#### Linux:
```bash
sudo apt-get install g++ cmake libncurses-dev # Ubuntu or Debian
apk add make cmake g++ ncurses-dev            # Alpine (run as root or sudo)
```
if you use a different linux distro, your package manager probably has the same packages under the same or similar names, if not, you can find, build, and install them yourself.

#### MacOS:
if you have the Xcode command line utils installed there's a decent chance you already have the necessary tools and libraries, otherwise you can install them by hand, or with a 3rd party package manager such as [Homebrew](https://brew.sh/):
```bash
brew install g++ cmake ncurses
```

#### Then download or clone the code, (downloding the latest release is recomended) and compile with cmake:
```bash
# from .../sea-snake
mkdir build
cd build
cmake ..
make
```
if your `ncurses` doesn't support unicode, you can compile without unicode using by adding the `NO_UNICODE` option to your cmake, like so:
```bash
cmake .. -D NO_UNICODE=ON
```
once it has compiled you can run it with:
```bash
./sea-snake
```
adding the `-u` and/or `-c` will use unicode and/or color respectively, you can also do `-h` for a full list of options.

(the `-u` option will not be available if you compiled without unicode)

## credits:
This project uses [TCLAP](http://tclap.sourceforge.net/) (licensed under MIT) for command line parsing.

## disclaimer:
I have no association with [Cygwin](https://www.cygwin.com/), Microsoft ([WSL2](https://docs.microsoft.com/en-us/windows/wsl/about)), [Homebrew](https://brew.sh/), [TCLAP](http://tclap.sourceforge.net/), or their respective maintainers.
