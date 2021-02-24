#ifndef __FANDG_H__
#define __FANDG_H__

#include "Sbox.h"
#include <stdio.h>
#include <stdint.h>

uint32_t G_function(uint32_t plaintext);
void F_function(uint32_t* plaintext,uint32_t* ciphertext,uint32_t* RK);

#endif /* FandG.h */