#ifndef PANZGB_H
#define PANZGB_H
/*
 * BYTE must always be an unsigned, 8 bit value
 * WORD must always be an unsigned, 16 bit value
 *
 * Must be changed, depending the architecture (if the compiler
 * doesn't support C99 types)
 */

#include <stdint.h>

typedef uint8_t BYTE;
typedef int8_t SIGNED_BYTE;
typedef uint16_t WORD;
typedef int16_t SIGNED_WORD;

#define GB_CLOCK 4194304
#define GB_SCREEN_REFRESH_RATE 59.7
typedef struct gameboy gb;

gb *newGameboy(char *rom);
char *getGameName(gb *cpu);

BYTE executeGameBoy(gb *cpu);

/* Those macros are for handling the gameboy keymap*/

#define GB_K_RIGHT 0x0
#define GB_K_LEFT 0x1
#define GB_K_UP 0x2
#define GB_K_DOWN 0x3
#define GB_K_A 0x4
#define GB_K_B 0x5
#define GB_K_SELECT 0x6
#define GB_K_START 0x7

#define GB_KEY_PRESSED 0x0
#define GB_KEY_RELEASED 0x1

void changeKeyState(gb *cpu, BYTE key, BYTE state);

#define WHITE_COL 0x00
#define LIGHTGRAY_COL 0x77//0x55//0x77
#define GRAY_COL 0xcc//0xaa
#define BLACK_COL 0xff

BYTE getPixelColor(gb *cpu, BYTE x, BYTE y);

void setGbBanking(gb *cpu);
#endif
