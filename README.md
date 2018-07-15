# panzgb

panzgb is an emulator for the Gameboy system. It uses [libpanzgb](https://github.com/afiuorio/libpanzgb) as it backend emulator library.

## Build

panzgb uses [SDL 2.0](http://www.libsdl.org) for display and input management. A makefile is provided for Linux. On Linux, after you have installed SDL2 on your system, you can build this project with:
```bash
git clone https://github.com/afiuorio/panzgb
git submodule init
make
```
