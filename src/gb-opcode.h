#ifndef GBOPCODE_H
#define GBOPCODE_H

void LOAD_8BIT(BYTE *dest, BYTE src);
void LOAD_16BIT(BYTE *destA, BYTE *destB, WORD src);

void LDHL(gb *cpu);

void ADD_8BIT(gb *cpu, BYTE *regA, BYTE regB);
void ADDC_8BIT(gb *cpu, BYTE *regA, BYTE regB);

void SUB_8BIT(gb *cpu, BYTE *regA, BYTE regB);
void SUBC_8BIT(gb *cpu, BYTE *regA, BYTE regB);

void AND_8BIT(gb *cpu, BYTE *regA, BYTE regB);
void OR_8BIT(gb *cpu, BYTE *regA, BYTE regB);
void XOR_8BIT(gb *cpu, BYTE *regA, BYTE regB);

void CP_8BIT(gb *cpu, BYTE regB);

void INC_8BIT(gb *cpu, BYTE *reg);
void DEC_8BIT(gb *cpu, BYTE *reg);

void ADD_16BIT(gb *cpu, BYTE *regA, BYTE *regB, WORD src);

void INC_16BIT(BYTE *regA, BYTE *regB);
void DEC_16BIT(BYTE *regA, BYTE *regB);

void JMP(gb *cpu, WORD addr);

void ROTATE_LEFT(gb *cpu, BYTE *reg);
void ROTATE_RIGHT(gb *cpu, BYTE *reg);
void ROTATE_LEFT_CARRY(gb *cpu, BYTE *reg);
void ROTATE_RIGHT_CARRY(gb *cpu, BYTE *reg);

void SHIFT_LEFT(gb *cpu, BYTE *reg);
void SHIFT_RIGHT_ARITH(gb *cpu, BYTE *reg);
void SHIFT_RIGHT(gb *cpu, BYTE *reg);

void SWAP_NIBBLES(gb *cpu, BYTE *reg);
void TEST_BIT(gb *cpu, BYTE val, BYTE numBit);
void RESET_BIT(gb *cpu, BYTE *val, BYTE numBit);
void SET_BIT(gb *cpu, BYTE *val, BYTE numBit);

void DAA(gb *cpu);

#endif
