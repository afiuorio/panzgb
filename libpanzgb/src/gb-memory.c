#include "gb-impl.h"
#include <string.h>
#include <stdio.h>

/*This function assumes that the ROM is already loaded*/

void setGbBanking(gb *cpu) {
    switch (cpu->cartridge[0x147]) {
    case 1:
    case 2:
    case 3:
        cpu->ROMType = 1;
        cpu->currentROMBank = 1;
        cpu->changeBank = mbc1_changeBank;
        break;

    case 0x13:
        cpu->ROMType = 3;
        cpu->currentROMBank = 1;
        cpu->changeBank = mbc3_changeBank;
        break;
    }

    cpu->currentRAMBank = 0;
}

BYTE readMemory(gb *cpu, WORD addr) {
    if ((addr >= 0x0000) && (addr <= 0x3FFF)) {
        return cpu->cartridge[addr];
    }
    if ((addr >= 0x4000) && (addr <= 0x7FFF)) {
        WORD t = addr - 0x4000;
        return cpu->cartridge[t + (cpu->currentROMBank * 0x4000)];
    }

    else if ((addr >= 0xA000) && (addr <= 0xBFFF)) {
        WORD t = addr - 0xA000;
        return cpu->RAMBank[t + (cpu->currentRAMBank * 0x2000)];
    } else if (addr == 0xFF00)
        return getKeypad(cpu);

    return cpu->memory[addr];
}

/*This function is necessary for replicate the ECHO (E000-FDFF) area*/

void writeMemory(gb *cpu, WORD addr, BYTE data) {
    /*This part is mapped on the rom, so read-only*/
    if (addr < 0x8000) {
        cpu->changeBank(cpu, addr, data);
    }

    else if ((addr >= 0xA000) && (addr < 0xC000)) {
        if (cpu->isRAMEnable != 0) {
            WORD t = addr - 0xA000;
            cpu->RAMBank[t + (cpu->currentRAMBank * 0x2000)] = data;
        }
    }

    else if ((addr >= 0xE000) && (addr < 0xFE00)) {
        cpu->memory[addr] = data;
        writeMemory(cpu, addr - 0x2000, data);
    }

    /*Not usable */
    else if ((addr >= 0xFEA0) && (addr < 0xFEFF)) {
    }

    else if (addr == TIMER_CONTROLLER) {
        BYTE freq = readMemory(cpu, TIMER_CONTROLLER) & 0x3;
        cpu->memory[TIMER_CONTROLLER] = data;
        BYTE newfreq = readMemory(cpu, TIMER_CONTROLLER) & 0x3;

        if (freq != newfreq)
            setTimerFreq(cpu);
    } else if (addr == DIVIDER_TIMER)
        cpu->memory[DIVIDER_TIMER] = 0;
    else if (addr == LCD_SCANLINE_ADRR)
        cpu->memory[LCD_SCANLINE_ADRR] = 0;
    else if (addr == DMA_ADRR)
        DMATransfert(cpu, data);
    else
        cpu->memory[addr] = data;
}
