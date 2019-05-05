#include "gb-impl.h"

/* NB The word to copy are 0-offset!! */
void HDMAFullTransfert(gb* cpu, BYTE wordToCopy) {
	WORD src = (readMemory(cpu, HDMA_SOURCE_HIGH) << 8) | readMemory(cpu, HDMA_SOURCE_LOW);
	WORD dst = (readMemory(cpu, HDMA_DESTINATION_HIGH) << 8) | readMemory(cpu, HDMA_DESTINATION_LOW);
	WORD byteToCopy = (wordToCopy * 0x10) + 0x10;
	for (int i = 0; i < byteToCopy; i++) {
		writeMemory(cpu, dst + i, readMemory(cpu, src + i));
	}
}

void HDMASetupHBlankTransfert(gb* cpu) {
	WORD src = (readMemory(cpu, HDMA_SOURCE_HIGH) << 8) | readMemory(cpu, HDMA_SOURCE_LOW);
	WORD dst = (readMemory(cpu, HDMA_DESTINATION_HIGH) << 8) | readMemory(cpu, HDMA_DESTINATION_LOW);
	printf("Starting HDMA from %x to %x for %x words\n", src, dst, cpu->memory[HDMA_START]);
	cpu->currentHDMAPointer = src;
	cpu->currentDstPointer = dst;
	cpu->isHDMAActive = 1;
}

BYTE HDMAHBlankTransfert(gb* cpu) {
	if (cpu->isHDMAActive == 0) {
		return 0;
	}
	BYTE byteRemaining = readMemory(cpu, HDMA_START);
	WORD src = cpu->currentHDMAPointer;
	WORD dst = cpu->currentDstPointer;

	printf("Doing transfert from %x to %x (remains %x words)\n", src, dst, byteRemaining);

	for (int i = 0; i < 0x10; i++) {
		writeMemory(cpu, dst + i, readMemory(cpu, src + i));
	}
	cpu->currentHDMAPointer+=0x10;
	cpu->currentDstPointer+=0x10;

	if (byteRemaining == 0) {
		cpu->isHDMAActive = 0;
		cpu->memory[HDMA_START]= 0xFF;
	}
	else {
		cpu->memory[HDMA_START] = --byteRemaining;
	}
}