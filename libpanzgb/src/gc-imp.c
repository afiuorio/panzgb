#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "gb-impl.h"
#include "gb-opcode.h"

void loadROM(gb *cpu, char *rom) {
    FILE *f = fopen(rom, "rb");
    if (!f) {
        fprintf(stderr, "Can't load ROM\n");
        exit(2);
    }
    fread(cpu->cartridge, 1, CARTRIDGE_SIZE, f);
    fclose(f);

    switch (cpu->cartridge[0x147]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 0x13:
    break;

    default:
        printf("Can't execute this rom (ROM code: %x)\n",
               cpu->cartridge[0x147]);
        exit(EXIT_FAILURE);
    }
}

void no_changeBank(gb *cpu, WORD addr, BYTE data) {
}

void initGameBoy(gb *cpu) {
    cpu->changeBank = no_changeBank;
    cpu->progCounter = 0x100;
    cpu->whenDisableInterrupts = 0;
    cpu->enable_interr = 0;
    cpu->stack = 0xFFFE;

    memset(cpu->memory, 0, MEMORY_SIZE);

    cpu->master_interr_switch = 0;

    cpu->clockScanline = 456;
    cpu->clockBeforeTimer = 1024;
    cpu->clockBeforeDividerTimer = 256;
    cpu->ROMType = 0;
    cpu->currentROMBank = 1;
    cpu->cpuHalted = 1;
    cpu->whenDisableInterrupts = 0;
    cpu->keymap = 0xFF;

    setGbBanking(cpu);
}

void DMATransfert(gb *cpu, BYTE data) {
    WORD addr = data * 0x100;
    for (int i = 0; i < 0xA0; i++) {
        writeMemory(cpu, 0xFE00 + i, readMemory(cpu, addr + i));
    }
}

BYTE getKeypad(gb *cpu) {
    BYTE mem = cpu->memory[0xFF00];

    mem ^= 0xFF;
    if ((mem & 0x10) == 0) {
        BYTE currentPad = cpu->keymap >> 4;
        currentPad |= 0xF0;
        mem &= currentPad;
        mem ^= 0x30;
    } else if ((mem & 0x20) == 0) {
        BYTE currentPad = cpu->keymap & 0xF;
        currentPad |= 0xF0;
        mem &= currentPad;
        mem ^= 0x30;
    }

    return mem;
}

void keyReleased(gb *cpu, int key) {
    cpu->keymap |= (0x1 << key);
}

void keyPressed(gb *cpu, int key) {
    BYTE previouslyUnset = 0;

    // if setting from 1 to 0 we may have to request an interupt
    if (((cpu->keymap >> key) & 0x1) == 0)
        previouslyUnset = 1;

    // a keypressed is 0 not 1
    cpu->keymap &= ~(0x1 << key);

    // button pressed
    BYTE button = 1;

    // is this a standard button or a directional button?
    if (key > 3)
        button = 1;
    else
        button = 0;

    BYTE keyReq = cpu->memory[0xFF00];
    BYTE requestInterupt = 1;

    // only request interupt if the button just pressed is
    // the style of button the game is interested in
    if (button && (((keyReq >> 5) & 0x1) == 0))
        requestInterupt = 1;

    // same as above but for directional button
    else if (button && (((keyReq >> 4) & 0x1) == 0))
        requestInterupt = 1;

    // request interupt
    if (requestInterupt && (previouslyUnset == 0))
        raiseInterrupt(cpu, 4);
}

void changeKeyState(gb *cpu, BYTE key, BYTE state) {
    if (state == GB_KEY_PRESSED) {
        keyPressed(cpu, key);
    } else
        keyReleased(cpu, key);
}

BYTE executeGameBoy(gb *cpu) {
    BYTE opcode;
    BYTE numClock = 4;

    if (cpu->cpuHalted != 0) {
        GET_BYTE_PC(cpu, opcode);
        numClock = executeOpcode(cpu, opcode);

        if (cpu->whenDisableInterrupts > 0) {
            cpu->whenDisableInterrupts--;
            if (cpu->whenDisableInterrupts == 0)
                cpu->master_interr_switch = cpu->enable_interr;
        }
    }

    increaseTimer(cpu, numClock);
    handleInterrupts(cpu);
    handleGraphic(cpu, numClock);

    return numClock;
}

gb *newGameboy(char *rom) {
    gb *game = malloc(sizeof(gb));
    if (!game) {
        return NULL;
    }
    loadROM(game, rom);
    initGameBoy(game);
    return game;
}

char *getGameName(gb *cpu) {
    return (char *)cpu->cartridge + NAME_CART;
}
