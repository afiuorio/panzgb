#include "gb-impl.h"
#include "gb-opcode.h"
#include <stdint.h>

#define ROTATE_FLAG(cpu, bit, val)                                             \
    {                                                                          \
        if (bit == 0)                                                          \
            RESET_CFLAG(cpu);                                                  \
        else                                                                   \
            SET_CFLAG(cpu);                                                    \
        RESET_NFLAG(cpu);                                                      \
        RESET_HFLAG(cpu);                                                      \
        if (val == 0)                                                          \
            SET_ZFLAG(cpu);                                                    \
        else                                                                   \
            RESET_ZFLAG(cpu);                                                  \
    }                                                                          \
    while (0)

void LOAD_8BIT(BYTE *dest, BYTE src) {
    *dest = src;
}

void LOAD_16BIT(BYTE *destA, BYTE *destB, WORD src) {
    *destB = src & 0xFF;
    *destA = (src >> 8) & 0xFF;
}

void LDHL(gb *cpu) {
    uint32_t val;
    SIGNED_BYTE n;
    n = (SIGNED_BYTE)readMemory(cpu, cpu->progCounter);
    cpu->progCounter++;

    // GET_BYTE_PC(cpu, n);
    val = (SIGNED_WORD)cpu->stack + (SIGNED_WORD)n;
    RESET_ZFLAG(cpu);
    RESET_NFLAG(cpu);

    if (val > 0xFFFF)
        SET_CFLAG(cpu);
    else
        RESET_CFLAG(cpu);

    WORD h = (val & 0x8FF);
    h += (cpu->stack & 0x8FF);

    if (h > 0x8FF)
        SET_HFLAG(cpu);
    else
        RESET_HFLAG(cpu);

    /*TODO check the flags*/
    cpu->L = val & 0xFF;
    cpu->H = (val >> 8) & 0xFF;
}

void JMP(gb *cpu, WORD addr) {
    cpu->progCounter = addr;
}

void ADD_8BIT(gb *cpu, BYTE *regA, BYTE regB) {
    WORD value = (*regA) + regB;

    if (value > 255)
        SET_CFLAG(cpu);
    else
        RESET_CFLAG(cpu);

    value &= 0xFF;
    RESET_NFLAG(cpu);
    if (value == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);

    WORD h = ((*regA) & 0xF);
    h += (regB & 0xF);

    if (h > 0xF)
        SET_HFLAG(cpu);
    else
        RESET_HFLAG(cpu);
    *regA = value & 0xFF;
}

void ADDC_8BIT(gb *cpu, BYTE *regA, BYTE regB) {
    ADD_8BIT(cpu, regA, (BYTE)(regB + ((cpu->F & 0x10) ? 1 : 0)));
    /*	BYTE ret = regB + ((cpu->F &0x10)?1:0);
            WORD value = (*regA) + ret;
            //printf("(%x) %x +(%x) %x + %x (%x) = %x\n",i,*regA, (cpu->A),regB,
       ((cpu->F &0x10)?1:0), cpu->F, value&0xff );

                if(value > 0xff)
                    SET_CFLAG(cpu);
                else
                    RESET_CFLAG(cpu);

                value &= 0xFF;
                RESET_NFLAG(cpu);
                if(value == 0)
                    SET_ZFLAG(cpu);
                else
                    RESET_ZFLAG(cpu);

                WORD h = ((*(regA)) & 0xF) ;
                h += (ret & 0xF) ;

                if (h > 0xF)
                    SET_HFLAG(cpu);
                else
                    RESET_HFLAG(cpu);
                *regA = value & 0xFF;*/
}

void SUB_8BIT(gb *cpu, BYTE *regA, BYTE regB) {
    BYTE value = (*regA) - regB;
    SET_NFLAG(cpu);

    if ((*regA) < regB)
        SET_CFLAG(cpu);
    else
        RESET_CFLAG(cpu);

    value &= 0xFF;
    if (value == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);

    SIGNED_WORD h = ((*regA) & 0xF);
    h -= (regB & 0xF);

    if (h < 0)
        SET_HFLAG(cpu);
    else
        RESET_HFLAG(cpu);
    *regA = (BYTE)value;
}

void SUBC_8BIT(gb *cpu, BYTE *regA, BYTE regB) {
    SUB_8BIT(cpu, regA, (BYTE)(regB + ((cpu->F & 0x10) ? 1 : 0)));
    /*BYTE ret = regB + (SIGNED_BYTE)((cpu->F &0x10)?1:0);
    int32_t value = (*regA) - ret;

    //	printf("%x - %x - %x = %x\n",*regA, regB, ((cpu->F &0x10)?1:0), value );

        SET_NFLAG(cpu);

        if(value <0 ){
            SET_CFLAG(cpu);
            value+=256;
        }
        else
            RESET_CFLAG(cpu);

       value &=0xFF;
        if(value == 0)
            SET_ZFLAG(cpu);
        else
            RESET_ZFLAG(cpu);

        SIGNED_WORD h = (*regA & 0x0F) ;
        h -= (ret & 0x0F) ;

        if ((ret & 0x0F) > (*regA & 0x0F) )
            SET_HFLAG(cpu);
        else
            RESET_HFLAG(cpu);
        *regA = value&0xff;*/
}

void AND_8BIT(gb *cpu, BYTE *regA, BYTE regB) {
    BYTE val = *regA & regB;
    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    RESET_NFLAG(cpu);
    SET_HFLAG(cpu);
    RESET_CFLAG(cpu);
    *regA = val;
}

void OR_8BIT(gb *cpu, BYTE *regA, BYTE regB) {
    BYTE val = (*regA) | regB;
    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    RESET_NFLAG(cpu);
    RESET_HFLAG(cpu);
    RESET_CFLAG(cpu);
    *regA = val;
}

void XOR_8BIT(gb *cpu, BYTE *regA, BYTE regB) {
    BYTE val = (*regA) ^ regB;
    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    RESET_NFLAG(cpu);
    RESET_HFLAG(cpu);
    RESET_CFLAG(cpu);
    *regA = val;
}

void CP_8BIT(gb *cpu, BYTE regB) {
    BYTE temp = cpu->A;
    SUB_8BIT(cpu, &(cpu->A), regB);
    cpu->A = temp;
}

void INC_8BIT(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    val++;
    if (((*reg) & 0xF) == 0)
        SET_HFLAG(cpu);
    else
        RESET_HFLAG(cpu);
    RESET_NFLAG(cpu);
    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    *reg = val;
}

void DEC_8BIT(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    val--;
    if (((*reg) & 0xF) == 0)
        SET_HFLAG(cpu);
    else
        RESET_HFLAG(cpu);
    SET_NFLAG(cpu);
    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    *reg = val;
}

void INC_16BIT(BYTE *regA, BYTE *regB) {
    WORD value = ((*regA) << 8) | (*regB);
    value++;
    *regA = (value >> 8) & 0xFF;
    *regB = value & 0xFF;
}

void DEC_16BIT(BYTE *regA, BYTE *regB) {
    WORD value = ((*regA) << 8) | (*regB);
    value--;
    *regA = (value >> 8) & 0xFF;
    *regB = value & 0xFF;
}

void SWAP_NIBBLES(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    val = ((val << 4) & 0xF0) | ((val >> 4) & 0xF);
    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    RESET_NFLAG(cpu);
    RESET_HFLAG(cpu);
    RESET_CFLAG(cpu);
    *reg = val;
}

void TEST_BIT(gb *cpu, BYTE val, BYTE numBit) {
    BYTE val2 = (val >> numBit) & 0x1;
    if (val2 == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    RESET_NFLAG(cpu);
    SET_HFLAG(cpu);
}

void RESET_BIT(gb *cpu, BYTE *val, BYTE numBit) {
    BYTE v = (*val) & (~(0x1 << numBit));
    *val = v;
}

void SET_BIT(gb *cpu, BYTE *val, BYTE numBit) {
    BYTE v = (*val) | (0x1 << numBit);
    *val = v;
}

void ADD_16BIT(gb *cpu, BYTE *regA, BYTE *regB, WORD src) {
    uint32_t val = (((*regA) << 8)) | ((*regB) & 0xFF);
    // uint32_t val = (((*regA)<<8)) | ((*regB) &0xFF);
    val += src;
    RESET_NFLAG(cpu);

    if (val > 0xFFFF)
        SET_CFLAG(cpu);
    else
        RESET_CFLAG(cpu);

    WORD h = (((((*regA) << 8)) | ((*regB) & 0xFF)) & 0x8FF);
    h += (src & 0x8FF);

    if (h > 0x8FF)
        SET_HFLAG(cpu);
    else
        RESET_HFLAG(cpu);

    *regA = (val >> 8) & 0xFF;
    *regB = (val & 0xFF);
}

void ROTATE_LEFT(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    BYTE msb = (val >> 7) & 0x1;
    val <<= 1;
    val |= msb;
    cpu->F = 0;
    if (msb) {
        SET_CFLAG(cpu);
    } else {
        RESET_CFLAG(cpu);
    }
    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);

    *reg = val;
}

void ROTATE_RIGHT(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    BYTE msb = (val & 0x1);
    cpu->F = 0;
    val >>= 1;
    if (msb) {
        val |= 0x80;
        SET_CFLAG(cpu);
    } else {
        val &= 0x7f;
        RESET_CFLAG(cpu);
    }
    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    *reg = val;
}

void ROTATE_LEFT_CARRY(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    BYTE msb = (val >> 7) & 0x1;
    val <<= 1;
    if (cpu->F & 0x10)
        val |= 0x1;
    if (msb)
        SET_CFLAG(cpu);
    else
        RESET_CFLAG(cpu);

    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    *reg = val;
}

void ROTATE_RIGHT_CARRY(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    BYTE msb = val & 0x1;
    val >>= 1;
    if ((cpu->F & 0x10) != 0)
        val |= 0x80;
    else
        val &= 0x7f;
    if (msb)
        SET_CFLAG(cpu);
    else
        RESET_CFLAG(cpu);

    if (val == 0)
        SET_ZFLAG(cpu);
    else
        RESET_ZFLAG(cpu);
    *reg = val;
}

void SHIFT_LEFT(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    BYTE msb = (val >> 7) & 0x1;

    val <<= 1;

    ROTATE_FLAG(cpu, msb, val);
    *reg = val;
}

void SHIFT_RIGHT_ARITH(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    BYTE lsb = (val)&0x1;
    BYTE msb = (val >> 7) & 0x1;

    val >>= 1;
    val |= ((msb << 7));

    ROTATE_FLAG(cpu, lsb, val);
    *reg = val;
}

void SHIFT_RIGHT(gb *cpu, BYTE *reg) {
    BYTE val = *reg;
    BYTE lsb = (val)&0x1;

    val >>= 1;

    ROTATE_FLAG(cpu, lsb, val);
    *reg = val;
}

void DAA(gb *cpu) {
    uint32_t a = cpu->A;

    if (!(cpu->F & 0x40)) {
        if ((cpu->F & 0x20) || (a & 0xF) > 9)
            a += 0x06;
        if ((cpu->F & 0x10) || a > 0x9F)
            a += 0x60;
    } else {
        if ((cpu->F & 0x20) != 0)
            a -= 0x06;

        if ((cpu->F & 0x10) != 0)
            a -= 0x60;
    }

    cpu->F &= ~(0x20 | 0x80);
    if ((a & 0x100) == 0x100)
        SET_CFLAG(cpu);

    a &= 0xFF;

    if (a == 0)
        SET_ZFLAG(cpu);
    cpu->A = (BYTE)a;
}
