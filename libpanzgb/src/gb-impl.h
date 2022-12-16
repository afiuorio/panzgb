#ifndef GB_IMPL_H
#define GB_IMPL_H
#include "panzgb.h"

#define NAME_CART 0x134

#define CARTRIDGE_SIZE 0x200000
#define MEMORY_SIZE 0x10000

#define KEYMAP_ADDR 0xFF00

#define DIVIDER_TIMER 0xFF04

#define TIMER_ADDR 0xFF05
#define TIMER_DEFAULT 0xFF06
#define TIMER_CONTROLLER 0xFF07

#define INTERRUPT_ENABLED_ADDR 0xFFFF
#define INTERRUPT_REQUEST_ADDR 0xFF0F

#define LCD_SCANLINE_ADRR 0xFF44
#define LCD_REG_CONTROL 0xFF40
#define LCD_REG_STATUS 0xFF41

#define DMA_ADRR 0xFF46

#define SCROLLX 0xFF43
#define SCROLLY 0xFF42

#define WINDOWY 0xFF4A
#define WINDOWX 0xFF4B

#define getAF(cpu) ((cpu->A << 8) | (cpu->F))
#define getBC(cpu) ((cpu->B << 8) | (cpu->C))
#define getDE(cpu) ((cpu->D << 8) | (cpu->E))
#define getHL(cpu) ((cpu->H << 8) | (cpu->L))

#define SET_ZFLAG(cpu) (cpu->F |= 0x80)
#define SET_NFLAG(cpu) (cpu->F |= 0x40)
#define SET_HFLAG(cpu) (cpu->F |= 0x20)
#define SET_CFLAG(cpu) (cpu->F |= 0x10)

#define RESET_ZFLAG(cpu) (cpu->F &= ~(0x80))
#define RESET_NFLAG(cpu) (cpu->F &= ~(0x40))
#define RESET_HFLAG(cpu) (cpu->F &= ~(0x20))
#define RESET_CFLAG(cpu) (cpu->F &= ~(0x10))

#define PUSH(cpu, base, l)                                                     \
    do {                                                                       \
        writeMemory(cpu, base - 2, l & 0xFF);                                  \
        writeMemory(cpu, base - 1, (l >> 8) & 0xFF);                           \
        base -= 2;                                                             \
    } while (0);

#define POP(cpu, base, l)                                                      \
    do {                                                                       \
        BYTE _low = readMemory(cpu, base);                                     \
        l = (readMemory(cpu, base + 1) << 8) | _low;                           \
        base += 2;                                                             \
    } while (0);

#define GET_BYTE_PC(cpu, l)                                                    \
    do {                                                                       \
        l = readMemory(cpu, cpu->progCounter);                                 \
        cpu->progCounter++;                                                    \
    } while (0);

#define GET_WORD_PC(cpu, l)                                                    \
    do {                                                                       \
        l = readMemory(cpu, cpu->progCounter);                                 \
        cpu->progCounter++;                                                    \
        BYTE _hi = readMemory(cpu, cpu->progCounter);                          \
        cpu->progCounter++;                                                    \
        l = (_hi << 8) | l;                                                    \
    } while (0);

struct gameboy {
    BYTE cartridge[CARTRIDGE_SIZE];
    BYTE memory[MEMORY_SIZE];

    // Now the CPU registers

    WORD progCounter;
    WORD stack;

    BYTE A;
    BYTE B;
    BYTE C;
    BYTE D;
    BYTE E;
    BYTE F;
    BYTE H;
    BYTE L;

    /*This part represent the memory banking system*/

    BYTE ROMType; /*This variable represents the ROM type MBCx*/
    WORD currentROMBank;
    BYTE ROMBankType;

    BYTE RAMBank[0x10000]; /*This should contains all the RAM banks*/
    BYTE currentRAMBank;
    BYTE isRAMEnable;

    /*This part helps handling the timers*/

    int clockBeforeTimer;
    int clockBeforeDividerTimer;

    /*This is the master interrupt switch*/

    BYTE master_interr_switch;
    BYTE whenDisableInterrupts;
    BYTE enable_interr;

    /*This area is for handle the LCD timing*/

    int clockScanline;

    /*This is the screen*/

    BYTE screenData[144][160];

    BYTE cpuHalted;

    BYTE keymap;

    void (*changeBank)(gb *, WORD, BYTE);
};

BYTE readMemory(gb *cpu, WORD addr);
void writeMemory(gb *cpu, WORD addr, BYTE data);

void increaseTimer(gb *cpu, BYTE clocks);
void setTimerFreq(gb *cpu);
void raiseInterrupt(gb *cpu, BYTE code);
void handleInterrupts(gb *cpu);

void handleGraphic(gb *cpu, BYTE cycles);

void DMATransfert(gb *cpu, BYTE data);

void mbc1_changeBank(gb *cpu, WORD addr, BYTE data);
void mbc3_changeBank(gb *cpu, WORD addr, BYTE data);

BYTE getKeypad(gb *cpu);

BYTE executeOpcode(gb *cpu, BYTE opcode);
unsigned int extendedOpcodes(gb *cpu, BYTE opcode);

void writeSaveRam(gb *cpu);
void loadSaveRam(gb *cpu);

#endif
