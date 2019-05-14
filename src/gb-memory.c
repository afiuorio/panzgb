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

    case 0x10:
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
		size_t value = (size_t)t + ((size_t)cpu->currentROMBank * 0x4000);
        return cpu->cartridge[value];
    }

    else if ((addr >= 0x8000) && (addr < 0x9FFF)) {
        WORD t = addr - 0x8000;
        return cpu->videoRamBank[t + (cpu->currentVideoRamBank * 0x2000)];
    }

    else if ((addr >= 0xA000) && (addr <= 0xBFFF)) {
		if (cpu->RTCMapped == 1) {
			printf("Trying to read RTC, using stub\n");
			return 0;
		}
        WORD t = addr - 0xA000;
        return cpu->RAMBank[t + (cpu->currentRAMBank * 0x2000)];
    }
	else if ((addr >= 0xC000) && (addr <= 0xCFFF)) {
		WORD t = addr - 0xC000;
		return cpu->internalWorkingRam[t];
	}
	else if ((addr >= 0xD000) && (addr <= 0xDFFF)) {
		WORD t = addr - 0xD000;
		return cpu->internalWorkingRam[t + (cpu->currentInternalWRAMBank * 0x1000)];
	}
	else if ((addr >= 0xE000) && (addr < 0xFE00)) {
		return readMemory(cpu, addr - 0x2000);
	}
	else if (addr == 0xFF00)
        return getKeypad(cpu);
	/*TODO you should do the read functions for the color palettes*/

    return cpu->memory[addr];
}

/*This function is necessary for replicate the ECHO (E000-FDFF) area*/

void writeMemory(gb *cpu, WORD addr, BYTE data) {
    /*This part is mapped on the rom, so read-only.
     *If the game is trying to write in this area, it means
     *it wants to change the mapped rom bank*/
    if (addr < 0x8000) {
        cpu->changeBank(cpu, addr, data);
    }
    else if ((addr >= 0x8000) && (addr < 0x9FFF)) {
        WORD t = addr - 0x8000;
        cpu->videoRamBank[t + (cpu->currentVideoRamBank * 0x2000)] = data;
    }

    else if ((addr >= 0xA000) && (addr < 0xC000)) {
		if (cpu->RTCMapped == 1) {
			printf("Trying to modify RTC, ignoring it...\n");
		}
        if (cpu->isRAMEnable != 0) {
            WORD t = addr - 0xA000;
            cpu->RAMBank[t + (cpu->currentRAMBank * 0x2000)] = data;
        }
    }
	else if ((addr >= 0xC000) && (addr <= 0xCFFF)) {
		WORD t = addr - 0xC000;
		cpu->internalWorkingRam[t] = data;
	}
	else if ((addr >= 0xD000) && (addr <= 0xDFFF)) {
		WORD t = addr - 0xD000;
		cpu->internalWorkingRam[t + (cpu->currentInternalWRAMBank * 0x1000)] = data;
	}

    else if ((addr >= 0xE000) && (addr < 0xFE00)) {
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
	else if (addr == HDMA_SOURCE_HIGH) {
		cpu->memory[addr] = data;
	}
	else if (addr == HDMA_SOURCE_LOW) {
		cpu->memory[addr] = data & 0xF0;
	}
	else if (addr == HDMA_DESTINATION_HIGH) {
		//The first 3 bit must be set to 100 (the address is always in VRAM)
		cpu->memory[addr] = (data & 0x1F) | 0x80;
	}
	else if (addr == HDMA_DESTINATION_LOW) {
		cpu->memory[addr] = data & 0xF0;
	}
	else if (addr == HDMA_START) {
		if (cpu->isHDMAActive == 1 && (data & 0x80) == 0) {
			printf("Stopping HDMA\n");
			cpu->isHDMAActive = 0;
			cpu->memory[HDMA_START] = 0xFF;
			//Stop transfert and set to FF
		}
		else {
			if ((data & 0x80) == 0) {
				HDMAFullTransfert(cpu, data & 0x7f);
				cpu->memory[HDMA_START] = 0xFF;
			}
			else {
				cpu->memory[HDMA_START] = data & 0x7f;
				HDMASetupHBlankTransfert(cpu);
			}
		}
	}
    else if (addr == 0xFF4F){
        if(data != 0){
            cpu->currentVideoRamBank = 1;
            cpu->memory[addr] = data;
        } else {
            cpu->currentVideoRamBank = 0;
            cpu->memory[addr] = 0;
        }
        //printf("Changed vram to %x\n",data);
    }
	else if (addr == BGPD) {
		BYTE indexReg = readMemory(cpu, BGPI);
		BYTE index =  indexReg & 0x3F;
		cpu->colorBackgroundPalette[index] = data;
		if ((indexReg & 0x80) != 0) {
			writeMemory(cpu, BGPI, indexReg + 1);
		}
	}
	else if (addr == OBPD) {
		BYTE indexReg = readMemory(cpu, OBPI);
		BYTE index = indexReg & 0x3F;
		cpu->colorSpritePalette[index] = data;
		if ((indexReg & 0x80) != 0) {
			writeMemory(cpu, OBPI, indexReg + 1);
		}
	}
	else if (addr == SVBK) {
		if (cpu->is_cgb != 0) {
			BYTE newBank = data & 0x07;
			cpu->currentInternalWRAMBank = (newBank == 0 ? 1 : newBank);
			cpu->memory[addr] = 0xf8 | newBank;
		}
	}
	else if (addr == KEY1) {
		printf("CGB function %x not yet implemented!!\n", addr);
	}

    else {
        cpu->memory[addr] = data;
    }
}
