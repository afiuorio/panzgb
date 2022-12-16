#include "gb-impl.h"

void mbc1_changeBank(gb *cpu, WORD addr, BYTE data) {
    // RAM enabling
    if (addr < 0x2000) {
        BYTE testData = data & 0xF;
        if (testData == 0x0) {
            cpu->isRAMEnable = 0;
        } else {
            cpu->isRAMEnable = 1;
        }
    }

    /*Change ROM bank*/
    else if ((addr >= 0x2000) && (addr < 0x4000)) {
        BYTE lower5 = data & 31;
        cpu->currentROMBank &= 224; // turn off the lower 5
        cpu->currentROMBank |= lower5;
        if (cpu->currentROMBank == 0 || cpu->currentROMBank == 0x20 ||
            cpu->currentROMBank == 0x40 || cpu->currentROMBank == 0x60)
            cpu->currentROMBank++;
    }

    /*Depending from the MBC1 type, I have to change something*/
    else if ((addr >= 0x4000) && (addr < 0x6000)) {
        if (cpu->ROMBankType == 1) {
            cpu->currentROMBank &= 31;
            data &= 0x3;
            data <<= 5;
            cpu->currentROMBank |= data;
            if (cpu->currentROMBank == 0 || cpu->currentROMBank == 0x20 ||
                cpu->currentROMBank == 0x40 || cpu->currentROMBank == 0x60)
                cpu->currentROMBank++;
        } else
            cpu->currentRAMBank = data & 0x3;
    }

    /*Determine which type of MBC1 is*/
    else if ((addr >= 0x6000) && (addr < 0x8000)) {
        BYTE newData = data & 0x1;
        cpu->ROMBankType = (newData == 0) ? 1 : 0;
        if (cpu->ROMBankType == 1)
            cpu->currentRAMBank = 0;
    }
}
