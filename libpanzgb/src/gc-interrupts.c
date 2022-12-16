#include <stdio.h>
#include "gb-impl.h"

void setTimerFreq(gb *cpu) {
    BYTE freq = readMemory(cpu, TIMER_CONTROLLER) & 0x3;
    switch (freq) {
    case 0:
        cpu->clockBeforeTimer = 1024;
        break; // freq 4096
    case 1:
        cpu->clockBeforeTimer = 16;
        break; // freq 262144
    case 2:
        cpu->clockBeforeTimer = 64;
        break; // freq 65536
    case 3:
        cpu->clockBeforeTimer = 256;
        break; // freq 16382
    }
}

void handleDividerTimer(gb *cpu, BYTE clocks) {
    cpu->clockBeforeDividerTimer -= clocks;
    if (cpu->clockBeforeDividerTimer <= 0) {
        cpu->clockBeforeDividerTimer = 255;
        cpu->memory[DIVIDER_TIMER]++;
    }
}

void increaseTimer(gb *cpu, BYTE clocks) {
    handleDividerTimer(cpu, clocks);
    /*Timer is enabled ?*/
    if ((readMemory(cpu, TIMER_CONTROLLER) & 0x4) != 0) {
        cpu->clockBeforeTimer -= clocks;
        if (cpu->clockBeforeTimer <= 0) {
            BYTE currentTimer = readMemory(cpu, TIMER_ADDR);

            setTimerFreq(cpu);
            /*The timer should overflow ?*/
            if (currentTimer == 255) {
                writeMemory(cpu, TIMER_ADDR, readMemory(cpu, TIMER_DEFAULT));
                raiseInterrupt(cpu, 2);
            } else
                writeMemory(cpu, TIMER_ADDR, currentTimer + 1);
        }
    }
}

void raiseInterrupt(gb *cpu, BYTE code) {
    BYTE interruptRequest = readMemory(cpu, INTERRUPT_REQUEST_ADDR);
    interruptRequest |= (0x1 << code);
    writeMemory(cpu, INTERRUPT_REQUEST_ADDR, interruptRequest);
    cpu->cpuHalted = 1;
}

void executeInterrupt(gb *cpu, BYTE bit) {
    cpu->master_interr_switch = 0;
    BYTE inter_mask = readMemory(cpu, INTERRUPT_REQUEST_ADDR);
    inter_mask &= ~(0x1 << bit);
    writeMemory(cpu, INTERRUPT_REQUEST_ADDR, inter_mask);

    WORD currentPC = cpu->progCounter;
    PUSH(cpu, cpu->stack, currentPC);

    switch (bit) {
    case 0:
        cpu->progCounter = 0x40;
        break;
    case 1:
        cpu->progCounter = 0x48;
        break;
    case 2:
        cpu->progCounter = 0x50;
        break;
    case 4:
        cpu->progCounter = 0x60;
        break;
    }
}

void handleInterrupts(gb *cpu) {
    BYTE req = readMemory(cpu, INTERRUPT_REQUEST_ADDR);
    BYTE enabled = readMemory(cpu, INTERRUPT_ENABLED_ADDR);

    BYTE mask = req & enabled;

    if (cpu->master_interr_switch != 0) {
        /*Interrupts are enabled, let's see if there are some interrupts
         * waiting*/
        if (mask != 0) { /*An interrupt is enabled and set*/
            BYTE i;
            for (i = 0; i < 5; i++) {
                if ((mask & (0x1 << i)) != 0)
                    executeInterrupt(cpu, i);
            }
        }
    }
}
