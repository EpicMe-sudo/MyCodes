#ifndef __MASKEDFANDG_H__
#define __MASKEDFANDG_H__

#include "Sbox.h"
#include "fips202.h"
#include "rng.h"
#include "MaskedSbox.h"
#include "MaskingFunction.h"
#include <stdio.h>
#include <stdint.h>

void MG_function(uint32_t* plaintext,uint8_t* M,uint8_t* MS1box,uint8_t* MS2box);
void MF_function(uint32_t* Left,uint32_t* Right,uint32_t* RK,uint8_t* M,uint8_t* MS1box,uint8_t* MS2box);

#endif /* FandG.h */