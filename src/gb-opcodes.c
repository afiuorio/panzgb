#include <stdio.h>
#include "gb-impl.h"
#include "gb-opcode.h"

BYTE executeOpcode(gb *cpu, BYTE opcode) {
    BYTE val = 0;
    SIGNED_BYTE s_val = 0;
    WORD val_16 = 0;
    switch (opcode) {
    case 0x00:
        return 4;
    case 0x76:
        //cpu->cpuHalted = 0;
        return 4;
    case 0x06:
        GET_BYTE_PC(cpu, val)
        LOAD_8BIT(&(cpu->B), val);
        return 8;
    case 0x0E:
        GET_BYTE_PC(cpu, val)
        LOAD_8BIT(&(cpu->C), val);
        return 8;
    case 0x16:
        GET_BYTE_PC(cpu, val)
        LOAD_8BIT(&(cpu->D), val);
        return 8;
    case 0x1E:
        GET_BYTE_PC(cpu, val)
        LOAD_8BIT(&(cpu->E), val);
        return 8;
    case 0x26:
        GET_BYTE_PC(cpu, val)
        LOAD_8BIT(&(cpu->H), val);
        return 8;
    case 0x2E:
        GET_BYTE_PC(cpu, val)
        LOAD_8BIT(&(cpu->L), val);
        return 8;

    case 0x7F:
        LOAD_8BIT(&(cpu->A), cpu->A);
        return 4;
    case 0x78:
        LOAD_8BIT(&(cpu->A), cpu->B);
        return 4;
    case 0x79:
        LOAD_8BIT(&(cpu->A), cpu->C);
        return 4;
    case 0x7A:
        LOAD_8BIT(&(cpu->A), cpu->D);
        return 4;
    case 0x7B:
        LOAD_8BIT(&(cpu->A), cpu->E);
        return 4;
    case 0x7C:
        LOAD_8BIT(&(cpu->A), cpu->H);
        return 4;
    case 0x7D:
        LOAD_8BIT(&(cpu->A), cpu->L);
        return 4;
    case 0x7E:
        val = readMemory(cpu, getHL(cpu));
        LOAD_8BIT(&(cpu->A), val);
        return 8;
    case 0x40:
        LOAD_8BIT(&(cpu->B), cpu->B);
        return 4;
    case 0x41:
        LOAD_8BIT(&(cpu->B), cpu->C);
        return 4;
    case 0x42:
        LOAD_8BIT(&(cpu->B), cpu->D);
        return 4;
    case 0x43:
        LOAD_8BIT(&(cpu->B), cpu->E);
        return 4;
    case 0x44:
        LOAD_8BIT(&(cpu->B), cpu->H);
        return 4;
    case 0x45:
        LOAD_8BIT(&(cpu->B), cpu->L);
        return 4;
    case 0x46:
        val = readMemory(cpu, getHL(cpu));
        LOAD_8BIT(&(cpu->B), val);
        return 8;
    case 0x48:
        LOAD_8BIT(&(cpu->C), cpu->B);
        return 4;
    case 0x49:
        LOAD_8BIT(&(cpu->C), cpu->C);
        return 4;
    case 0x4A:
        LOAD_8BIT(&(cpu->C), cpu->D);
        return 4;
    case 0x4B:
        LOAD_8BIT(&(cpu->C), cpu->E);
        return 4;
    case 0x4C:
        LOAD_8BIT(&(cpu->C), cpu->H);
        return 4;
    case 0x4D:
        LOAD_8BIT(&(cpu->C), cpu->L);
        return 4;
    case 0x4E:
        val = readMemory(cpu, getHL(cpu));
        LOAD_8BIT(&(cpu->C), val);
        return 8;
    case 0x50:
        LOAD_8BIT(&(cpu->D), cpu->B);
        return 4;
    case 0x51:
        LOAD_8BIT(&(cpu->D), cpu->C);
        return 4;
    case 0x52:
        LOAD_8BIT(&(cpu->D), cpu->D);
        return 4;
    case 0x53:
        LOAD_8BIT(&(cpu->D), cpu->E);
        return 4;
    case 0x54:
        LOAD_8BIT(&(cpu->D), cpu->H);
        return 4;
    case 0x55:
        LOAD_8BIT(&(cpu->D), cpu->L);
        return 4;
    case 0x56:
        val = readMemory(cpu, getHL(cpu));
        LOAD_8BIT(&(cpu->D), val);
        return 8;
    case 0x58:
        LOAD_8BIT(&(cpu->E), cpu->B);
        return 4;
    case 0x59:
        LOAD_8BIT(&(cpu->E), cpu->C);
        return 4;
    case 0x5A:
        LOAD_8BIT(&(cpu->E), cpu->D);
        return 4;
    case 0x5B:
        LOAD_8BIT(&(cpu->E), cpu->E);
        return 4;
    case 0x5C:
        LOAD_8BIT(&(cpu->E), cpu->H);
        return 4;
    case 0x5D:
        LOAD_8BIT(&(cpu->E), cpu->L);
        return 4;
    case 0x5E:
        val = readMemory(cpu, getHL(cpu));
        LOAD_8BIT(&(cpu->E), val);
        return 8;
    case 0x60:
        LOAD_8BIT(&(cpu->H), cpu->B);
        return 4;
    case 0x61:
        LOAD_8BIT(&(cpu->H), cpu->C);
        return 4;
    case 0x62:
        LOAD_8BIT(&(cpu->H), cpu->D);
        return 4;
    case 0x63:
        LOAD_8BIT(&(cpu->H), cpu->E);
        return 4;
    case 0x64:
        LOAD_8BIT(&(cpu->H), cpu->H);
        return 4;
    case 0x65:
        LOAD_8BIT(&(cpu->H), cpu->L);
        return 4;
    case 0x66:
        val = readMemory(cpu, getHL(cpu));
        LOAD_8BIT(&(cpu->H), val);
        return 8;
    case 0x68:
        LOAD_8BIT(&(cpu->L), cpu->B);
        return 4;
    case 0x69:
        LOAD_8BIT(&(cpu->L), cpu->C);
        return 4;
    case 0x6A:
        LOAD_8BIT(&(cpu->L), cpu->D);
        return 4;
    case 0x6B:
        LOAD_8BIT(&(cpu->L), cpu->E);
        return 4;
    case 0x6C:
        LOAD_8BIT(&(cpu->L), cpu->H);
        return 4;
    case 0x6D:
        LOAD_8BIT(&(cpu->L), cpu->L);
        return 4;
    case 0x6E:
        val = readMemory(cpu, getHL(cpu));
        LOAD_8BIT(&(cpu->L), val);
        return 8;
    case 0x70:
        writeMemory(cpu, getHL(cpu), cpu->B);
        return 8;
    case 0x71:
        writeMemory(cpu, getHL(cpu), cpu->C);
        return 8;
    case 0x72:
        writeMemory(cpu, getHL(cpu), cpu->D);
        return 8;
    case 0x73:
        writeMemory(cpu, getHL(cpu), cpu->E);
        return 8;
    case 0x74:
        writeMemory(cpu, getHL(cpu), cpu->H);
        return 8;
    case 0x75:
        writeMemory(cpu, getHL(cpu), cpu->L);
        return 8;
    case 0x36:
        GET_BYTE_PC(cpu, val);
        writeMemory(cpu, getHL(cpu), val);
        return 12;

    case 0x0A:
        val = readMemory(cpu, getBC(cpu));
        LOAD_8BIT(&(cpu->A), val);
        return 8;
    case 0x1A:
        val = readMemory(cpu, getDE(cpu));
        cpu->A = val;
        return 8;
    case 0xFA:
        GET_WORD_PC(cpu, val_16);
        val = readMemory(cpu, val_16);
        LOAD_8BIT(&(cpu->A), val);
        return 16;
    case 0x3E:
        GET_BYTE_PC(cpu, val);
        LOAD_8BIT(&(cpu->A), val);
        return 8;

    case 0x47:
        LOAD_8BIT(&(cpu->B), cpu->A);
        return 4;
    case 0x4F:
        LOAD_8BIT(&(cpu->C), cpu->A);
        return 4;
    case 0x57:
        LOAD_8BIT(&(cpu->D), cpu->A);
        return 4;
    case 0x5F:
        LOAD_8BIT(&(cpu->E), cpu->A);
        return 4;
    case 0x67:
        LOAD_8BIT(&(cpu->H), cpu->A);
        return 4;
    case 0x6F:
        LOAD_8BIT(&(cpu->L), cpu->A);
        return 4;
    case 0x02:
        writeMemory(cpu, getBC(cpu), cpu->A);
        return 8;
    case 0x12:
        writeMemory(cpu, getDE(cpu), cpu->A);
        return 8;
    case 0x77:
        writeMemory(cpu, getHL(cpu), cpu->A);
        return 8;
    case 0xEA:
        GET_WORD_PC(cpu, val_16);
        writeMemory(cpu, val_16, cpu->A);
        return 16;

    case 0xF2:
        val = readMemory(cpu, 0xFF00 + cpu->C);
        LOAD_8BIT(&(cpu->A), val);
        return 8;
    case 0xE2:
        writeMemory(cpu, 0xFF00 + cpu->C, cpu->A);
        return 8;

    case 0x3A:
        val = readMemory(cpu, getHL(cpu));
        LOAD_8BIT(&(cpu->A), val);
        DEC_16BIT(&(cpu->H), &(cpu->L));
        return 8;
    case 0x32:
        writeMemory(cpu, getHL(cpu), cpu->A);
        DEC_16BIT(&(cpu->H), &(cpu->L));
        return 8;
    case 0x2A:
        val = readMemory(cpu, getHL(cpu));
        LOAD_8BIT(&(cpu->A), val);
        INC_16BIT(&(cpu->H), &(cpu->L));
        return 8;
    case 0x22:
        writeMemory(cpu, getHL(cpu), cpu->A);
        INC_16BIT(&(cpu->H), &(cpu->L));
        return 8;
    case 0xE0:
        GET_BYTE_PC(cpu, val);
        writeMemory(cpu, 0xFF00 + val, cpu->A);
        return 12;
    case 0xF0:
        GET_BYTE_PC(cpu, val);
        val = readMemory(cpu, 0xFF00 + val);
        LOAD_8BIT(&(cpu->A), val);
        return 12;

    case 0x01:
        GET_WORD_PC(cpu, val_16);
        LOAD_16BIT(&(cpu->B), &(cpu->C), val_16);
        return 12;
    case 0x11:
        GET_WORD_PC(cpu, val_16);
        LOAD_16BIT(&(cpu->D), &(cpu->E), val_16);
        return 12;
    case 0x21:
        GET_WORD_PC(cpu, val_16);
        LOAD_16BIT(&(cpu->H), &(cpu->L), val_16);
        return 12;
    case 0x31:
        GET_WORD_PC(cpu, val_16);
        cpu->stack = val_16;
        return 12;
    case 0xF9:
        cpu->stack = getHL(cpu);
        return 8;
    case 0xF8:
        GET_BYTE_PC(cpu, s_val);
        val_16 = cpu->stack + s_val;
        RESET_ZFLAG(cpu);
        RESET_NFLAG(cpu);

        if ((uint32_t)(cpu->stack + s_val) > 0xFFFF)
            SET_CFLAG(cpu);
        else
            RESET_CFLAG(cpu);

        if ((uint32_t)(cpu->stack + s_val) > 0x8FF)
            SET_HFLAG(cpu);
        else
            RESET_HFLAG(cpu);
        cpu->L = val_16 & 0xFF;
        cpu->H = ((val_16 >> 8) & 0xFF);

        return 12;
    case 0x08:
        GET_WORD_PC(cpu, val_16);
        writeMemory(cpu, val_16, cpu->stack & 0xFF);
        writeMemory(cpu, val_16 + 1, (cpu->stack >> 8) & 0xFF);
        return 20;
    case 0xF5:
        PUSH(cpu, cpu->stack, getAF(cpu));
        return 16;
    case 0xC5:
        PUSH(cpu, cpu->stack, getBC(cpu));
        return 16;
    case 0xD5:
        PUSH(cpu, cpu->stack, getDE(cpu));
        return 16;
    case 0xE5:
        PUSH(cpu, cpu->stack, getHL(cpu));
        return 16;
    case 0xF1:
        POP(cpu, cpu->stack, val_16);
        cpu->A = (val_16 >> 8) & 0xFF;
        cpu->F = val_16 & 0xFF;
        cpu->F &= ~0xF;
        return 12;
    case 0xC1:
        POP(cpu, cpu->stack, val_16);
        cpu->B = (val_16 >> 8) & 0xFF;
        cpu->C = val_16 & 0xFF;
        return 12;
    case 0xD1:
        POP(cpu, cpu->stack, val_16);
        cpu->D = (val_16 >> 8) & 0xFF;
        cpu->E = val_16 & 0xFF;
        return 12;
    case 0xE1:
        POP(cpu, cpu->stack, val_16);
        cpu->H = (val_16 >> 8) & 0xFF;
        cpu->L = val_16 & 0xFF;
        return 12;

    case 0x87:
        ADD_8BIT(cpu, &(cpu->A), cpu->A);
        return 4;
    case 0x80:
        ADD_8BIT(cpu, &(cpu->A), cpu->B);
        return 4;
    case 0x81:
        ADD_8BIT(cpu, &(cpu->A), cpu->C);
        return 4;
    case 0x82:
        ADD_8BIT(cpu, &(cpu->A), cpu->D);
        return 4;
    case 0x83:
        ADD_8BIT(cpu, &(cpu->A), cpu->E);
        return 4;
    case 0x84:
        ADD_8BIT(cpu, &(cpu->A), cpu->H);
        return 4;
    case 0x85:
        ADD_8BIT(cpu, &(cpu->A), cpu->L);
        return 4;
    case 0x86:
        val = readMemory(cpu, getHL(cpu));
        ADD_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0xC6:
        GET_BYTE_PC(cpu, val);
        ADD_8BIT(cpu, &(cpu->A), val);
        return 8;

    case 0x8F:
        ADDC_8BIT(cpu, &(cpu->A), cpu->A);
        return 4;
    case 0x88:
        ADDC_8BIT(cpu, &(cpu->A), cpu->B);
        return 4;
    case 0x89:
        ADDC_8BIT(cpu, &(cpu->A), cpu->C);
        return 4;
    case 0x8A:
        ADDC_8BIT(cpu, &(cpu->A), cpu->D);
        return 4;
    case 0x8B:
        ADDC_8BIT(cpu, &(cpu->A), cpu->E);
        return 4;
    case 0x8C:
        ADDC_8BIT(cpu, &(cpu->A), cpu->H);
        return 4;
    case 0x8D:
        ADDC_8BIT(cpu, &(cpu->A), cpu->L);
        return 4;
    case 0x8E:
        val = readMemory(cpu, getHL(cpu));
        ADDC_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0xCE:
        GET_BYTE_PC(cpu, val);
        ADDC_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0x97:
        SUB_8BIT(cpu, &(cpu->A), cpu->A);
        return 4;
    case 0x90:
        SUB_8BIT(cpu, &(cpu->A), cpu->B);
        return 4;
    case 0x91:
        SUB_8BIT(cpu, &(cpu->A), cpu->C);
        return 4;
    case 0x92:
        SUB_8BIT(cpu, &(cpu->A), cpu->D);
        return 4;
    case 0x93:
        SUB_8BIT(cpu, &(cpu->A), cpu->E);
        return 4;
    case 0x94:
        SUB_8BIT(cpu, &(cpu->A), cpu->H);
        return 4;
    case 0x95:
        SUB_8BIT(cpu, &(cpu->A), cpu->L);
        return 4;
    case 0x96:
        val = readMemory(cpu, getHL(cpu));
        SUB_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0x9F:
        SUBC_8BIT(cpu, &(cpu->A), cpu->A);
        return 4;
    case 0x98:
        SUBC_8BIT(cpu, &(cpu->A), cpu->B);
        return 4;
    case 0x99:
        SUBC_8BIT(cpu, &(cpu->A), cpu->C);
        return 4;
    case 0x9A:
        SUBC_8BIT(cpu, &(cpu->A), cpu->D);
        return 4;
    case 0x9B:
        SUBC_8BIT(cpu, &(cpu->A), cpu->E);
        return 4;
    case 0x9C:
        SUBC_8BIT(cpu, &(cpu->A), cpu->H);
        return 4;
    case 0x9D:
        SUBC_8BIT(cpu, &(cpu->A), cpu->L);
        return 4;
    case 0x9E:
        val = readMemory(cpu, getHL(cpu));
        SUBC_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0xD6:
        GET_BYTE_PC(cpu, val);
        SUB_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0xDE:
        GET_BYTE_PC(cpu, val);
        SUBC_8BIT(cpu, &(cpu->A), val);
        return 8;

    case 0xA7:
        AND_8BIT(cpu, &(cpu->A), cpu->A);
        return 4;
    case 0xA0:
        AND_8BIT(cpu, &(cpu->A), cpu->B);
        return 4;
    case 0xA1:
        AND_8BIT(cpu, &(cpu->A), cpu->C);
        return 4;
    case 0xA2:
        AND_8BIT(cpu, &(cpu->A), cpu->D);
        return 4;
    case 0xA3:
        AND_8BIT(cpu, &(cpu->A), cpu->E);
        return 4;
    case 0xA4:
        AND_8BIT(cpu, &(cpu->A), cpu->H);
        return 4;
    case 0xA5:
        AND_8BIT(cpu, &(cpu->A), cpu->L);
        return 4;
    case 0xA6:
        val = readMemory(cpu, getHL(cpu));
        AND_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0xE6:
        GET_BYTE_PC(cpu, val);
        AND_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0xB7:
        OR_8BIT(cpu, &(cpu->A), cpu->A);
        return 4;
    case 0xB0:
        OR_8BIT(cpu, &(cpu->A), cpu->B);
        return 4;
    case 0xB1:
        OR_8BIT(cpu, &(cpu->A), cpu->C);
        return 4;
    case 0xB2:
        OR_8BIT(cpu, &(cpu->A), cpu->D);
        return 4;
    case 0xB3:
        OR_8BIT(cpu, &(cpu->A), cpu->E);
        return 4;
    case 0xB4:
        OR_8BIT(cpu, &(cpu->A), cpu->H);
        return 4;
    case 0xB5:
        OR_8BIT(cpu, &(cpu->A), cpu->L);
        return 4;
    case 0xB6:
        val = readMemory(cpu, getHL(cpu));
        OR_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0xF6:
        val = readMemory(cpu, cpu->progCounter);
        cpu->progCounter++;
        OR_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0xAF:
        XOR_8BIT(cpu, &(cpu->A), cpu->A);
        return 4;
    case 0xA8:
        XOR_8BIT(cpu, &(cpu->A), cpu->B);
        return 4;
    case 0xA9:
        XOR_8BIT(cpu, &(cpu->A), cpu->C);
        return 4;
    case 0xAA:
        XOR_8BIT(cpu, &(cpu->A), cpu->D);
        return 4;
    case 0xAB:
        XOR_8BIT(cpu, &(cpu->A), cpu->E);
        return 4;
    case 0xAC:
        XOR_8BIT(cpu, &(cpu->A), cpu->H);
        return 4;
    case 0xAD:
        XOR_8BIT(cpu, &(cpu->A), cpu->L);
        return 4;
    case 0xAE:
        val = readMemory(cpu, getHL(cpu));
        XOR_8BIT(cpu, &(cpu->A), val);
        return 8;
    case 0xEE:
        val = readMemory(cpu, cpu->progCounter);
        cpu->progCounter++;
        XOR_8BIT(cpu, &(cpu->A), val);
        return 8;

    case 0xBF:
        CP_8BIT(cpu, cpu->A);
        return 4;
    case 0xB8:
        CP_8BIT(cpu, cpu->B);
        return 4;
    case 0xB9:
        CP_8BIT(cpu, cpu->C);
        return 4;
    case 0xBA:
        CP_8BIT(cpu, cpu->D);
        return 4;
    case 0xBB:
        CP_8BIT(cpu, cpu->E);
        return 4;
    case 0xBC:
        CP_8BIT(cpu, cpu->H);
        return 4;
    case 0xBD:
        CP_8BIT(cpu, cpu->L);
        return 4;
    case 0xBE:
        val = readMemory(cpu, getHL(cpu));
        CP_8BIT(cpu, val);
        return 8;
    case 0xFE:
        GET_BYTE_PC(cpu, val)
        CP_8BIT(cpu, val);
        return 8;

    case 0x3C:
        INC_8BIT(cpu, &(cpu->A));
        return 4;
    case 0x04:
        INC_8BIT(cpu, &(cpu->B));
        return 4;
    case 0x0C:
        INC_8BIT(cpu, &(cpu->C));
        return 4;
    case 0x14:
        INC_8BIT(cpu, &(cpu->D));
        return 4;
    case 0x1C:
        INC_8BIT(cpu, &(cpu->E));
        return 4;
    case 0x24:
        INC_8BIT(cpu, &(cpu->H));
        return 4;
    case 0x2C:
        INC_8BIT(cpu, &(cpu->L));
        return 4;
    case 0x34:
        val = readMemory(cpu, getHL(cpu));
        INC_8BIT(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 12;

    case 0x3D:
        DEC_8BIT(cpu, &(cpu->A));
        return 4;
    case 0x05:
        DEC_8BIT(cpu, &(cpu->B));
        return 4;
    case 0x0D:
        DEC_8BIT(cpu, &(cpu->C));
        return 4;
    case 0x15:
        DEC_8BIT(cpu, &(cpu->D));
        return 4;
    case 0x1D:
        DEC_8BIT(cpu, &(cpu->E));
        return 4;
    case 0x25:
        DEC_8BIT(cpu, &(cpu->H));
        return 4;
    case 0x2D:
        DEC_8BIT(cpu, &(cpu->L));
        return 4;
    case 0x35:
        val = readMemory(cpu, getHL(cpu));
        DEC_8BIT(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 12;

    /*16BIT operations*/

    case 0x09:
        ADD_16BIT(cpu, &(cpu->H), &(cpu->L), getBC(cpu));
        return 8;
    case 0x19:
        ADD_16BIT(cpu, &(cpu->H), &(cpu->L), getDE(cpu));
        return 8;
    case 0x29:
        ADD_16BIT(cpu, &(cpu->H), &(cpu->L), getHL(cpu));
        return 8;
    case 0x39:
        ADD_16BIT(cpu, &(cpu->H), &(cpu->L), cpu->stack);
        return 8;

    case 0x03:
        INC_16BIT(&(cpu->B), &(cpu->C));
        return 8;
    case 0x13:
        INC_16BIT(&(cpu->D), &(cpu->E));
        return 8;
    case 0x23:
        INC_16BIT(&(cpu->H), &(cpu->L));
        return 8;
    case 0x33:
        cpu->stack++;
        return 8;
    case 0x0B:
        DEC_16BIT(&(cpu->B), &(cpu->C));
        return 8;
    case 0x1B:
        DEC_16BIT(&(cpu->D), &(cpu->E));
        return 8;
    case 0x2B:
        DEC_16BIT(&(cpu->H), &(cpu->L));
        return 8;
    case 0x3B:
        cpu->stack--;
        return 8;

    case 0xE8:
        GET_BYTE_PC(cpu, s_val);
        val_16 = cpu->stack + s_val;
        RESET_ZFLAG(cpu);
        RESET_NFLAG(cpu);

        if ((uint32_t)(cpu->stack + s_val) > 0xFFFF)
            SET_CFLAG(cpu);
        else
            RESET_CFLAG(cpu);

        if (((cpu->stack) & 0x8ff + (s_val)) > 0x8FF)
            SET_HFLAG(cpu);
        else
            RESET_HFLAG(cpu);
        cpu->stack = val_16;
        return 16;

    case 0xCB:
        GET_BYTE_PC(cpu, val);
        return extendedOpcodes(cpu, val);

    case 0x27:
        DAA(cpu);
        return 4;

    case 0x2F:
        SET_NFLAG(cpu);
        SET_HFLAG(cpu);
        cpu->A = ~cpu->A;
        return 4;
    case 0x3F:
        RESET_NFLAG(cpu);
        RESET_HFLAG(cpu);
        val = (cpu->F & 0x10) >> 4;
        if (val == 0)
            cpu->F |= 0x10;
        else
            cpu->F &= ~(0x10);
        return 4;
    case 0x37:
        RESET_NFLAG(cpu);
        RESET_HFLAG(cpu);
        SET_CFLAG(cpu);
        return 4;

    case 0x07:
        ROTATE_LEFT(cpu, &(cpu->A));
        SET_ZFLAG(cpu);
        return 4;
    case 0x0F:
        ROTATE_RIGHT(cpu, &(cpu->A));
        SET_ZFLAG(cpu);
        return 4;
    case 0x17:
        ROTATE_LEFT_CARRY(cpu, &(cpu->A));
        SET_ZFLAG(cpu);
        return 4;
    case 0x1f:
        ROTATE_RIGHT_CARRY(cpu, &(cpu->A));
        SET_ZFLAG(cpu);
        return 4;

    case 0xF3:
        cpu->whenDisableInterrupts = 2;
        cpu->enable_interr = 0;
        return 4;
    case 0xFB:
        cpu->whenDisableInterrupts = 2;
        cpu->enable_interr = 1;
        return 4;

    case 0xC3:
        GET_WORD_PC(cpu, val_16);
        JMP(cpu, val_16);
        return 12;
    case 0xC2:
        val = cpu->F & 0x80;
        GET_WORD_PC(cpu, val_16);
        if (val == 0)
            JMP(cpu, val_16);
        return 12;
    case 0xCA:
        val = cpu->F & 0x80;
        GET_WORD_PC(cpu, val_16);
        if (val != 0)
            JMP(cpu, val_16);
        return 12;
    case 0xD2:
        val = cpu->F & 0x10;
        GET_WORD_PC(cpu, val_16);
        if (val == 0)
            JMP(cpu, val_16);
        return 12;
    case 0xDA:
        val = cpu->F & 0x10;
        GET_WORD_PC(cpu, val_16);
        if (val != 0)
            JMP(cpu, val_16);
        return 12;
    case 0xE9:
        cpu->progCounter = getHL(cpu);
        return 4;
    case 0x18:
        GET_BYTE_PC(cpu, s_val);
        cpu->progCounter += s_val;
        return 8;

    case 0x20:
        GET_BYTE_PC(cpu, s_val);
        val = cpu->F & 0x80;
        if (val == 0)
            cpu->progCounter += s_val;
        return 8;
    case 0x28:
        GET_BYTE_PC(cpu, s_val);
        val = cpu->F & 0x80;
        if (val != 0) {
            cpu->progCounter += s_val;
        }
        return 8;
    case 0x30:
        GET_BYTE_PC(cpu, s_val);
        val_16 = cpu->F & 0x10;
        if (val_16 == 0)
            cpu->progCounter += s_val;
        return 8;
    case 0x38:
        GET_BYTE_PC(cpu, s_val);
        val_16 = cpu->F & 0x10;
        if (val_16 != 0)
            cpu->progCounter += s_val;
        return 8;

    case 0xCD:
        GET_WORD_PC(cpu, val_16);
        PUSH(cpu, cpu->stack, cpu->progCounter);
        cpu->progCounter = val_16;
        return 24;
    case 0xC4:
        GET_WORD_PC(cpu, val_16);
        val = cpu->F & 0x80;
        if (val == 0) {
            PUSH(cpu, cpu->stack, cpu->progCounter);
            cpu->progCounter = val_16;
        }
        return 12;
    case 0xCC:
        GET_WORD_PC(cpu, val_16);
        val = cpu->F & 0x80;
        if (val != 0) {
            PUSH(cpu, cpu->stack, cpu->progCounter);
            cpu->progCounter = val_16;
        }
        return 12;
    case 0xD4:
        GET_WORD_PC(cpu, val_16);
        val = cpu->F & 0x10;
        if (val == 0) {
            PUSH(cpu, cpu->stack, cpu->progCounter);
            cpu->progCounter = val_16;
        }
        return 12;
    case 0xDC:
        GET_WORD_PC(cpu, val_16);
        val = cpu->F & 0x10;
        if (val != 0) {
            PUSH(cpu, cpu->stack, cpu->progCounter);
            cpu->progCounter = val_16;
        }
        return 12;
    case 0xC7:
        PUSH(cpu, cpu->stack, cpu->progCounter);
        cpu->progCounter = 0x0;
        return 32;
    case 0xCF:
        PUSH(cpu, cpu->stack, cpu->progCounter);
        cpu->progCounter = 0x8;
        return 32;
    case 0xD7:
        PUSH(cpu, cpu->stack, cpu->progCounter);
        cpu->progCounter = 0x10;
        return 32;
    case 0xDF:
        PUSH(cpu, cpu->stack, cpu->progCounter);
        cpu->progCounter = 0x18;
        return 32;
    case 0xE7:
        PUSH(cpu, cpu->stack, cpu->progCounter);
        cpu->progCounter = 0x20;
        return 32;
    case 0xEF:
        PUSH(cpu, cpu->stack, cpu->progCounter);
        cpu->progCounter = 0x28;
        return 32;
    case 0xF7:
        PUSH(cpu, cpu->stack, cpu->progCounter);
        cpu->progCounter = 0x30;
        return 32;
    case 0xFF:
        PUSH(cpu, cpu->stack, cpu->progCounter);
        cpu->progCounter = 0x38;
        return 32;
    case 0xC9:
        POP(cpu, cpu->stack, val_16);
        cpu->progCounter = val_16;
        return 8;
    case 0xC0:
        val = cpu->F & 0x80;
        if (val == 0) {
            POP(cpu, cpu->stack, val_16);
            cpu->progCounter = val_16;
        }
        return 8;
    case 0xC8:
        val = cpu->F & 0x80;
        if (val != 0) {
            POP(cpu, cpu->stack, val_16);
            cpu->progCounter = val_16;
        }
        return 8;
    case 0xD0:
        val = cpu->F & 0x10;
        if (val == 0) {
            POP(cpu, cpu->stack, val_16);
            cpu->progCounter = val_16;
        }
        return 8;
    case 0xD8:
        val = cpu->F & 0x10;
        if (val != 0) {
            POP(cpu, cpu->stack, val_16);
            cpu->progCounter = val_16;
        }
        return 8;
    case 0xD9:
        POP(cpu, cpu->stack, val_16);
        cpu->progCounter = val_16;
        cpu->master_interr_switch = 1;
        return 8;
    default:
        fprintf(stderr, "Can't decode %x opcode (PC = %x)\n", opcode,
                cpu->progCounter);
        return 1;
    }
    return 1;
}

unsigned int extendedOpcodes(gb *cpu, BYTE opcode) {
    BYTE val = 0;
    switch (opcode) {
    /*TODO You should check this*/
    case 0x00:
        ROTATE_LEFT(cpu, &(cpu->B));
        return 8;
    case 0x01:
        ROTATE_LEFT(cpu, &(cpu->C));
        return 8;
    case 0x02:
        ROTATE_LEFT(cpu, &(cpu->D));
        return 8;
    case 0x03:
        ROTATE_LEFT(cpu, &(cpu->E));
        return 8;
    case 0x04:
        ROTATE_LEFT(cpu, &(cpu->H));
        return 8;
    case 0x05:
        ROTATE_LEFT(cpu, &(cpu->L));
        return 8;
    case 0x06:
        val = readMemory(cpu, getHL(cpu));
        ROTATE_LEFT(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x07:
        ROTATE_LEFT(cpu, &(cpu->A));
        return 8;

    case 0x08:
        ROTATE_RIGHT(cpu, &(cpu->B));
        return 8;
    case 0x09:
        ROTATE_RIGHT(cpu, &(cpu->C));
        return 8;
    case 0x0A:
        ROTATE_RIGHT(cpu, &(cpu->D));
        return 8;
    case 0x0B:
        ROTATE_RIGHT(cpu, &(cpu->E));
        return 8;
    case 0x0C:
        ROTATE_RIGHT(cpu, &(cpu->H));
        return 8;
    case 0x0D:
        ROTATE_RIGHT(cpu, &(cpu->L));
        return 8;
    case 0x0E:
        val = readMemory(cpu, getHL(cpu));
        ROTATE_RIGHT(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x0F:
        ROTATE_LEFT(cpu, &(cpu->A));
        return 8;

    case 0x10:
        ROTATE_LEFT_CARRY(cpu, &(cpu->B));
        return 8;
    case 0x11:
        ROTATE_LEFT_CARRY(cpu, &(cpu->C));
        return 8;
    case 0x12:
        ROTATE_LEFT_CARRY(cpu, &(cpu->D));
        return 8;
    case 0x13:
        ROTATE_LEFT_CARRY(cpu, &(cpu->E));
        return 8;
    case 0x14:
        ROTATE_LEFT_CARRY(cpu, &(cpu->H));
        return 8;
    case 0x15:
        ROTATE_LEFT_CARRY(cpu, &(cpu->L));
        return 8;
    case 0x16:
        val = readMemory(cpu, getHL(cpu));
        ROTATE_LEFT_CARRY(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x17:
        ROTATE_LEFT_CARRY(cpu, &(cpu->A));
        return 8;
    case 0x18:
        ROTATE_RIGHT_CARRY(cpu, &(cpu->B));
        return 8;
    case 0x19:
        ROTATE_RIGHT_CARRY(cpu, &(cpu->C));
        return 8;
    case 0x1A:
        ROTATE_RIGHT_CARRY(cpu, &(cpu->D));
        return 8;
    case 0x1B:
        ROTATE_RIGHT_CARRY(cpu, &(cpu->E));
        return 8;
    case 0x1C:
        ROTATE_RIGHT_CARRY(cpu, &(cpu->H));
        return 8;
    case 0x1D:
        ROTATE_RIGHT_CARRY(cpu, &(cpu->L));
        return 8;
    case 0x1E:
        val = readMemory(cpu, getHL(cpu));
        ROTATE_RIGHT_CARRY(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x1F:
        ROTATE_RIGHT_CARRY(cpu, &(cpu->A));
        return 8;

    case 0x20:
        SHIFT_LEFT(cpu, &(cpu->B));
        return 8;
    case 0x21:
        SHIFT_LEFT(cpu, &(cpu->C));
        return 8;
    case 0x22:
        SHIFT_LEFT(cpu, &(cpu->D));
        return 8;
    case 0x23:
        SHIFT_LEFT(cpu, &(cpu->E));
        return 8;
    case 0x24:
        SHIFT_LEFT(cpu, &(cpu->H));
        return 8;
    case 0x25:
        SHIFT_LEFT(cpu, &(cpu->L));
        return 8;
    case 0x26:
        val = readMemory(cpu, getHL(cpu));
        SHIFT_LEFT(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 8;
    case 0x27:
        SHIFT_LEFT(cpu, &(cpu->A));
        return 16;
    case 0x28:
        SHIFT_RIGHT_ARITH(cpu, &(cpu->B));
        return 8;
    case 0x29:
        SHIFT_RIGHT_ARITH(cpu, &(cpu->C));
        return 8;
    case 0x2A:
        SHIFT_RIGHT_ARITH(cpu, &(cpu->D));
        return 8;
    case 0x2B:
        SHIFT_RIGHT_ARITH(cpu, &(cpu->E));
        return 8;
    case 0x2C:
        SHIFT_RIGHT_ARITH(cpu, &(cpu->H));
        return 8;
    case 0x2D:
        SHIFT_RIGHT_ARITH(cpu, &(cpu->L));
        return 8;
    case 0x2E:
        val = readMemory(cpu, getHL(cpu));
        SHIFT_RIGHT_ARITH(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 8;
    case 0x2F:
        SHIFT_RIGHT_ARITH(cpu, &(cpu->A));
        return 16;

    case 0x30:
        SWAP_NIBBLES(cpu, &(cpu->B));
        return 8;
    case 0x31:
        SWAP_NIBBLES(cpu, &(cpu->C));
        return 8;
    case 0x32:
        SWAP_NIBBLES(cpu, &(cpu->D));
        return 8;
    case 0x33:
        SWAP_NIBBLES(cpu, &(cpu->E));
        return 8;
    case 0x34:
        SWAP_NIBBLES(cpu, &(cpu->H));
        return 8;
    case 0x35:
        SWAP_NIBBLES(cpu, &(cpu->L));
        return 8;
    case 0x36:
        val = readMemory(cpu, getHL(cpu));
        SWAP_NIBBLES(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x37:
        SWAP_NIBBLES(cpu, &(cpu->A));
        return 8;
    case 0x38:
        SHIFT_RIGHT(cpu, &(cpu->B));
        return 8;
    case 0x39:
        SHIFT_RIGHT(cpu, &(cpu->C));
        return 8;
    case 0x3A:
        SHIFT_RIGHT(cpu, &(cpu->D));
        return 8;
    case 0x3B:
        SHIFT_RIGHT(cpu, &(cpu->E));
        return 8;
    case 0x3C:
        SHIFT_RIGHT(cpu, &(cpu->H));
        return 8;
    case 0x3D:
        SHIFT_RIGHT(cpu, &(cpu->L));
        return 8;
    case 0x3E:
        val = readMemory(cpu, getHL(cpu));
        SHIFT_RIGHT(cpu, &val);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x3F:
        SHIFT_RIGHT(cpu, &(cpu->A));
        return 8;

    case 0x40:
        TEST_BIT(cpu, cpu->B, 0);
        return 8;
    case 0x41:
        TEST_BIT(cpu, cpu->C, 0);
        return 8;
    case 0x42:
        TEST_BIT(cpu, cpu->D, 0);
        return 8;
    case 0x43:
        TEST_BIT(cpu, cpu->E, 0);
        return 8;
    case 0x44:
        TEST_BIT(cpu, cpu->H, 0);
        return 8;
    case 0x45:
        TEST_BIT(cpu, cpu->L, 0);
        return 8;
    case 0x46:
        val = readMemory(cpu, getHL(cpu));
        TEST_BIT(cpu, val, 0);
        return 16;
    case 0x47:
        TEST_BIT(cpu, cpu->A, 0);
        return 8;
    case 0x48:
        TEST_BIT(cpu, cpu->B, 1);
        return 8;
    case 0x49:
        TEST_BIT(cpu, cpu->C, 1);
        return 8;
    case 0x4A:
        TEST_BIT(cpu, cpu->D, 1);
        return 8;
    case 0x4B:
        TEST_BIT(cpu, cpu->E, 1);
        return 8;
    case 0x4C:
        TEST_BIT(cpu, cpu->H, 1);
        return 8;
    case 0x4D:
        TEST_BIT(cpu, cpu->L, 1);
        return 8;
    case 0x4E:
        val = readMemory(cpu, getHL(cpu));
        TEST_BIT(cpu, val, 1);
        return 16;
    case 0x4F:
        TEST_BIT(cpu, cpu->A, 1);
        return 8;
    case 0x50:
        TEST_BIT(cpu, cpu->B, 2);
        return 8;
    case 0x51:
        TEST_BIT(cpu, cpu->C, 2);
        return 8;
    case 0x52:
        TEST_BIT(cpu, cpu->D, 2);
        return 8;
    case 0x53:
        TEST_BIT(cpu, cpu->E, 2);
        return 8;
    case 0x54:
        TEST_BIT(cpu, cpu->H, 2);
        return 8;
    case 0x55:
        TEST_BIT(cpu, cpu->L, 2);
        return 8;
    case 0x56:
        val = readMemory(cpu, getHL(cpu));
        TEST_BIT(cpu, val, 2);
        return 16;
    case 0x57:
        TEST_BIT(cpu, cpu->A, 2);
        return 8;
    case 0x58:
        TEST_BIT(cpu, cpu->B, 3);
        return 8;
    case 0x59:
        TEST_BIT(cpu, cpu->C, 3);
        return 8;
    case 0x5A:
        TEST_BIT(cpu, cpu->D, 3);
        return 8;
    case 0x5B:
        TEST_BIT(cpu, cpu->E, 3);
        return 8;
    case 0x5C:
        TEST_BIT(cpu, cpu->H, 3);
        return 8;
    case 0x5D:
        TEST_BIT(cpu, cpu->L, 3);
        return 8;
    case 0x5E:
        val = readMemory(cpu, getHL(cpu));
        TEST_BIT(cpu, val, 3);
        return 16;
    case 0x5F:
        TEST_BIT(cpu, cpu->A, 3);
        return 8;
    case 0x60:
        TEST_BIT(cpu, cpu->B, 4);
        return 8;
    case 0x61:
        TEST_BIT(cpu, cpu->C, 4);
        return 8;
    case 0x62:
        TEST_BIT(cpu, cpu->D, 4);
        return 8;
    case 0x63:
        TEST_BIT(cpu, cpu->E, 4);
        return 8;
    case 0x64:
        TEST_BIT(cpu, cpu->H, 4);
        return 8;
    case 0x65:
        TEST_BIT(cpu, cpu->L, 4);
        return 8;
    case 0x66:
        val = readMemory(cpu, getHL(cpu));
        TEST_BIT(cpu, val, 4);
        return 16;
    case 0x67:
        TEST_BIT(cpu, cpu->A, 4);
        return 8;
    case 0x68:
        TEST_BIT(cpu, cpu->B, 5);
        return 8;
    case 0x69:
        TEST_BIT(cpu, cpu->C, 5);
        return 8;
    case 0x6A:
        TEST_BIT(cpu, cpu->D, 5);
        return 8;
    case 0x6B:
        TEST_BIT(cpu, cpu->E, 5);
        return 8;
    case 0x6C:
        TEST_BIT(cpu, cpu->H, 5);
        return 8;
    case 0x6D:
        TEST_BIT(cpu, cpu->L, 5);
        return 8;
    case 0x6E:
        val = readMemory(cpu, getHL(cpu));
        TEST_BIT(cpu, val, 5);
        return 16;
    case 0x6F:
        TEST_BIT(cpu, cpu->A, 5);
        return 8;
    case 0x70:
        TEST_BIT(cpu, cpu->B, 6);
        return 8;
    case 0x71:
        TEST_BIT(cpu, cpu->C, 6);
        return 8;
    case 0x72:
        TEST_BIT(cpu, cpu->D, 6);
        return 8;
    case 0x73:
        TEST_BIT(cpu, cpu->E, 6);
        return 8;
    case 0x74:
        TEST_BIT(cpu, cpu->H, 6);
        return 8;
    case 0x75:
        TEST_BIT(cpu, cpu->L, 6);
        return 8;
    case 0x76:
        val = readMemory(cpu, getHL(cpu));
        TEST_BIT(cpu, val, 6);
        return 16;
    case 0x77:
        TEST_BIT(cpu, cpu->A, 6);
        return 8;
    case 0x78:
        TEST_BIT(cpu, cpu->B, 7);
        return 8;
    case 0x79:
        TEST_BIT(cpu, cpu->C, 7);
        return 8;
    case 0x7A:
        TEST_BIT(cpu, cpu->D, 7);
        return 8;
    case 0x7B:
        TEST_BIT(cpu, cpu->E, 7);
        return 8;
    case 0x7C:
        TEST_BIT(cpu, cpu->H, 7);
        return 8;
    case 0x7D:
        TEST_BIT(cpu, cpu->L, 7);
        return 8;
    case 0x7E:
        val = readMemory(cpu, getHL(cpu));
        TEST_BIT(cpu, val, 7);
        return 16;
    case 0x7F:
        TEST_BIT(cpu, cpu->A, 7);
        return 8;

    case 0x80:
        RESET_BIT(cpu, &(cpu->B), 0);
        return 8;
    case 0x81:
        RESET_BIT(cpu, &(cpu->C), 0);
        return 8;
    case 0x82:
        RESET_BIT(cpu, &(cpu->D), 0);
        return 8;
    case 0x83:
        RESET_BIT(cpu, &(cpu->E), 0);
        return 8;
    case 0x84:
        RESET_BIT(cpu, &(cpu->H), 0);
        return 8;
    case 0x85:
        RESET_BIT(cpu, &(cpu->L), 0);
        return 8;
    case 0x86:
        val = readMemory(cpu, getHL(cpu));
        RESET_BIT(cpu, &val, 0);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x87:
        RESET_BIT(cpu, &(cpu->A), 0);
        return 8;
    case 0x88:
        RESET_BIT(cpu, &(cpu->B), 1);
        return 8;
    case 0x89:
        RESET_BIT(cpu, &(cpu->C), 1);
        return 8;
    case 0x8A:
        RESET_BIT(cpu, &(cpu->D), 1);
        return 8;
    case 0x8B:
        RESET_BIT(cpu, &(cpu->E), 1);
        return 8;
    case 0x8C:
        RESET_BIT(cpu, &(cpu->H), 1);
        return 8;
    case 0x8D:
        RESET_BIT(cpu, &(cpu->L), 1);
        return 8;
    case 0x8E:
        val = readMemory(cpu, getHL(cpu));
        RESET_BIT(cpu, &val, 1);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x8F:
        RESET_BIT(cpu, &(cpu->A), 1);
        return 8;
    case 0x90:
        RESET_BIT(cpu, &(cpu->B), 2);
        return 8;
    case 0x91:
        RESET_BIT(cpu, &(cpu->C), 2);
        return 8;
    case 0x92:
        RESET_BIT(cpu, &(cpu->D), 2);
        return 8;
    case 0x93:
        RESET_BIT(cpu, &(cpu->E), 2);
        return 8;
    case 0x94:
        RESET_BIT(cpu, &(cpu->H), 2);
        return 8;
    case 0x95:
        RESET_BIT(cpu, &(cpu->L), 2);
        return 8;
    case 0x96:
        val = readMemory(cpu, getHL(cpu));
        RESET_BIT(cpu, &val, 2);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x97:
        RESET_BIT(cpu, &(cpu->A), 2);
        return 8;
    case 0x98:
        RESET_BIT(cpu, &(cpu->B), 3);
        return 8;
    case 0x99:
        RESET_BIT(cpu, &(cpu->C), 3);
        return 8;
    case 0x9A:
        RESET_BIT(cpu, &(cpu->D), 3);
        return 8;
    case 0x9B:
        RESET_BIT(cpu, &(cpu->E), 3);
        return 8;
    case 0x9C:
        RESET_BIT(cpu, &(cpu->H), 3);
        return 8;
    case 0x9D:
        RESET_BIT(cpu, &(cpu->L), 3);
        return 8;
    case 0x9E:
        val = readMemory(cpu, getHL(cpu));
        RESET_BIT(cpu, &val, 3);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0x9F:
        RESET_BIT(cpu, &(cpu->A), 3);
        return 8;
    case 0xA0:
        RESET_BIT(cpu, &(cpu->B), 4);
        return 8;
    case 0xA1:
        RESET_BIT(cpu, &(cpu->C), 4);
        return 8;
    case 0xA2:
        RESET_BIT(cpu, &(cpu->D), 4);
        return 8;
    case 0xA3:
        RESET_BIT(cpu, &(cpu->E), 4);
        return 8;
    case 0xA4:
        RESET_BIT(cpu, &(cpu->H), 4);
        return 8;
    case 0xA5:
        RESET_BIT(cpu, &(cpu->L), 4);
        return 8;
    case 0xA6:
        val = readMemory(cpu, getHL(cpu));
        RESET_BIT(cpu, &val, 4);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xA7:
        RESET_BIT(cpu, &(cpu->A), 4);
        return 8;
    case 0xA8:
        RESET_BIT(cpu, &(cpu->B), 5);
        return 8;
    case 0xA9:
        RESET_BIT(cpu, &(cpu->C), 5);
        return 8;
    case 0xAA:
        RESET_BIT(cpu, &(cpu->D), 5);
        return 8;
    case 0xAB:
        RESET_BIT(cpu, &(cpu->E), 5);
        return 8;
    case 0xAC:
        RESET_BIT(cpu, &(cpu->H), 5);
        return 8;
    case 0xAD:
        RESET_BIT(cpu, &(cpu->L), 5);
        return 8;
    case 0xAE:
        val = readMemory(cpu, getHL(cpu));
        RESET_BIT(cpu, &val, 5);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xAF:
        RESET_BIT(cpu, &(cpu->A), 5);
        return 8;
    case 0xB0:
        RESET_BIT(cpu, &(cpu->B), 6);
        return 8;
    case 0xB1:
        RESET_BIT(cpu, &(cpu->C), 6);
        return 8;
    case 0xB2:
        RESET_BIT(cpu, &(cpu->D), 6);
        return 8;
    case 0xB3:
        RESET_BIT(cpu, &(cpu->E), 6);
        return 8;
    case 0xB4:
        RESET_BIT(cpu, &(cpu->H), 6);
        return 8;
    case 0xB5:
        RESET_BIT(cpu, &(cpu->L), 6);
        return 8;
    case 0xB6:
        val = readMemory(cpu, getHL(cpu));
        RESET_BIT(cpu, &val, 6);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xB7:
        RESET_BIT(cpu, &(cpu->A), 6);
        return 8;
    case 0xB8:
        RESET_BIT(cpu, &(cpu->B), 7);
        return 8;
    case 0xB9:
        RESET_BIT(cpu, &(cpu->C), 7);
        return 8;
    case 0xBA:
        RESET_BIT(cpu, &(cpu->D), 7);
        return 8;
    case 0xBB:
        RESET_BIT(cpu, &(cpu->E), 7);
        return 8;
    case 0xBC:
        RESET_BIT(cpu, &(cpu->H), 7);
        return 8;
    case 0xBD:
        RESET_BIT(cpu, &(cpu->L), 7);
        return 8;
    case 0xBE:
        val = readMemory(cpu, getHL(cpu));
        RESET_BIT(cpu, &val, 7);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xBF:
        RESET_BIT(cpu, &(cpu->A), 7);
        return 8;

    case 0xC0:
        SET_BIT(cpu, &(cpu->B), 0);
        return 8;
    case 0xC1:
        SET_BIT(cpu, &(cpu->C), 0);
        return 8;
    case 0xC2:
        SET_BIT(cpu, &(cpu->D), 0);
        return 8;
    case 0xC3:
        SET_BIT(cpu, &(cpu->E), 0);
        return 8;
    case 0xC4:
        SET_BIT(cpu, &(cpu->H), 0);
        return 8;
    case 0xC5:
        SET_BIT(cpu, &(cpu->L), 0);
        return 8;
    case 0xC6:
        val = readMemory(cpu, getHL(cpu));
        SET_BIT(cpu, &val, 0);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xC7:
        SET_BIT(cpu, &(cpu->A), 0);
        return 8;
    case 0xC8:
        SET_BIT(cpu, &(cpu->B), 1);
        return 8;
    case 0xC9:
        SET_BIT(cpu, &(cpu->C), 1);
        return 8;
    case 0xCA:
        SET_BIT(cpu, &(cpu->D), 1);
        return 8;
    case 0xCB:
        SET_BIT(cpu, &(cpu->E), 1);
        return 8;
    case 0xCC:
        SET_BIT(cpu, &(cpu->H), 1);
        return 8;
    case 0xCD:
        SET_BIT(cpu, &(cpu->L), 1);
        return 8;
    case 0xCE:
        val = readMemory(cpu, getHL(cpu));
        SET_BIT(cpu, &val, 1);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xCF:
        SET_BIT(cpu, &(cpu->A), 1);
        return 8;
    case 0xD0:
        SET_BIT(cpu, &(cpu->B), 2);
        return 8;
    case 0xD1:
        SET_BIT(cpu, &(cpu->C), 2);
        return 8;
    case 0xD2:
        SET_BIT(cpu, &(cpu->D), 2);
        return 8;
    case 0xD3:
        SET_BIT(cpu, &(cpu->E), 2);
        return 8;
    case 0xD4:
        SET_BIT(cpu, &(cpu->H), 2);
        return 8;
    case 0xD5:
        SET_BIT(cpu, &(cpu->L), 2);
        return 8;
    case 0xD6:
        val = readMemory(cpu, getHL(cpu));
        SET_BIT(cpu, &val, 2);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xD7:
        SET_BIT(cpu, &(cpu->A), 2);
        return 8;
    case 0xD8:
        SET_BIT(cpu, &(cpu->B), 3);
        return 8;
    case 0xD9:
        SET_BIT(cpu, &(cpu->C), 3);
        return 8;
    case 0xDA:
        SET_BIT(cpu, &(cpu->D), 3);
        return 8;
    case 0xDB:
        SET_BIT(cpu, &(cpu->E), 3);
        return 8;
    case 0xDC:
        SET_BIT(cpu, &(cpu->H), 3);
        return 8;
    case 0xDD:
        SET_BIT(cpu, &(cpu->L), 3);
        return 8;
    case 0xDE:
        val = readMemory(cpu, getHL(cpu));
        SET_BIT(cpu, &val, 3);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xDF:
        SET_BIT(cpu, &(cpu->A), 3);
        return 8;
    case 0xE0:
        SET_BIT(cpu, &(cpu->B), 4);
        return 8;
    case 0xE1:
        SET_BIT(cpu, &(cpu->C), 4);
        return 8;
    case 0xE2:
        SET_BIT(cpu, &(cpu->D), 4);
        return 8;
    case 0xE3:
        SET_BIT(cpu, &(cpu->E), 4);
        return 8;
    case 0xE4:
        SET_BIT(cpu, &(cpu->H), 4);
        return 8;
    case 0xE5:
        SET_BIT(cpu, &(cpu->L), 4);
        return 8;
    case 0xE6:
        val = readMemory(cpu, getHL(cpu));
        SET_BIT(cpu, &val, 4);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xE7:
        SET_BIT(cpu, &(cpu->A), 4);
        return 8;
    case 0xE8:
        SET_BIT(cpu, &(cpu->B), 5);
        return 8;
    case 0xE9:
        SET_BIT(cpu, &(cpu->C), 5);
        return 8;
    case 0xEA:
        SET_BIT(cpu, &(cpu->D), 5);
        return 8;
    case 0xEB:
        SET_BIT(cpu, &(cpu->E), 5);
        return 8;
    case 0xEC:
        SET_BIT(cpu, &(cpu->H), 5);
        return 8;
    case 0xED:
        SET_BIT(cpu, &(cpu->L), 5);
        return 8;
    case 0xEE:
        val = readMemory(cpu, getHL(cpu));
        SET_BIT(cpu, &val, 5);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xEF:
        SET_BIT(cpu, &(cpu->A), 5);
        return 8;
    case 0xF0:
        SET_BIT(cpu, &(cpu->B), 6);
        return 8;
    case 0xF1:
        SET_BIT(cpu, &(cpu->C), 6);
        return 8;
    case 0xF2:
        SET_BIT(cpu, &(cpu->D), 6);
        return 8;
    case 0xF3:
        SET_BIT(cpu, &(cpu->E), 6);
        return 8;
    case 0xF4:
        SET_BIT(cpu, &(cpu->H), 6);
        return 8;
    case 0xF5:
        SET_BIT(cpu, &(cpu->L), 6);
        return 8;
    case 0xF6:
        val = readMemory(cpu, getHL(cpu));
        SET_BIT(cpu, &val, 6);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xF7:
        SET_BIT(cpu, &(cpu->A), 6);
        return 8;
    case 0xF8:
        SET_BIT(cpu, &(cpu->B), 7);
        return 8;
    case 0xF9:
        SET_BIT(cpu, &(cpu->C), 7);
        return 8;
    case 0xFA:
        SET_BIT(cpu, &(cpu->D), 7);
        return 8;
    case 0xFB:
        SET_BIT(cpu, &(cpu->E), 7);
        return 8;
    case 0xFC:
        SET_BIT(cpu, &(cpu->H), 7);
        return 8;
    case 0xFD:
        SET_BIT(cpu, &(cpu->L), 7);
        return 8;
    case 0xFE:
        val = readMemory(cpu, getHL(cpu));
        SET_BIT(cpu, &val, 7);
        writeMemory(cpu, getHL(cpu), val);
        return 16;
    case 0xFF:
        SET_BIT(cpu, &(cpu->A), 7);
        return 8;

    default:
        fprintf(stderr, "Can't decode CB %x opcode (PC = %x)\n", opcode,
                cpu->progCounter);
        return 1;
    }
}
