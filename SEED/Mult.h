#ifndef __MULT_H__
#define __MULT_H__

#include <stdio.h>
#include <stdint.h>

#define MUL2(value) (value&0x80)?((value<<1)^0x63):(value<<1)
#define MUL3(value) (value^(MUL2(value)))
#define MUL4(value) (MUL2(MUL2(value)))

uint8_t MUL(uint8_t X,uint8_t Y);

#endif /* Mult.h */