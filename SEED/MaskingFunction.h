#ifndef __MASKINGFUNCTION_H__
#define __MASKINGFUNCTION_H__

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include "rng.h"
#include "fips202.h"

void GenCarryTable(uint8_t m,uint8_t* C1,uint8_t* C2,uint8_t R);
void RegCarry(uint32_t* var,uint8_t m);
void BtoA8(uint32_t* var,uint8_t m);
void BtoA32(uint32_t* var,uint8_t m);
void AtoB(uint32_t* var, uint8_t m);

#endif /* MaskingFunction.h */