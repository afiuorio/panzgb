#include "gb-impl.h"

void mbc3_changeBank(gb *cpu, WORD addr, BYTE data) {
    // RAM enabling
    if (addr < 0x2000) {
        BYTE testData = data & 0xF;
        if (testData == 0x0) {
            cpu->isRAMEnable = 0;
        } else
            cpu->isRAMEnable = 1;
    }

    /*Change ROM bank*/
    else if ((addr >= 0x2000) && (addr < 0x4000)) {
        BYTE lower7 = data & 0x7F;
        cpu->currentROMBank = lower7;
        if (cpu->currentROMBank == 0x00)
            cpu->currentROMBank = 1;

    }

    else if ((addr >= 0x4000) && (addr < 0x6000)) {
        if (data <= 0x3)
            cpu->currentRAMBank = data & 0x3;
    }

    /*Should handle the timer*/
    else if ((addr >= 0x6000) && (addr < 0x8000)) {
    }
}
