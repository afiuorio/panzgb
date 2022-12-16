# libpanzgb

libpanzgb is a C99 library that implements a Gameboy emulator. It tries to emulate the original hardware as closely as possible. Since it's written using only C99 without any external dependencies, it should be working on almost every platform with a C compiler.

Please note that this is only a "backend" library: for playing with the emulator itself is necessary an application that uses libpanzgb.

## Status

At the moment libpanzgb doesn't support:

- Sound
- All MBC chips except MBC1 and (partially) MBC3
- Link cable support
- STOP opcode
- Save RAM

## Build

A makefile for Linux is provided: if you have gcc installed, a simple
```bash
make
```

should be enough for compile the library. Since the library doesn't require any extra dependencies, it should be easy to compile the library on any platform that possess a C99 compiler.
