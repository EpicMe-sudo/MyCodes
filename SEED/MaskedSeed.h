#ifndef __MASKEDSEED_H__
#define __MASKEDSEED_H__

//#include "Mult.h"
#include "fips202.h"
#include "rng.h"
#include "MaskedSbox.h"
#include "MaskedFandG.h"
#include "Sbox.h"
#include "FandG.h"
#include "KeySchedule.h"
#include <string.h>
#include <math.h>
#include <assert.h>

#define SEED_VER 128

#if SEED_VER == 128

#define SEED_INPUT_WORD 4
#define SEED_OUTPUT_WORD 4
#define SEED_MK_WORD 4
#define SEED_RK_WORD 32

#elif SEED_VER == 192

#endif

void MaskedSeedEncryption(uint32_t* plaintext,uint32_t* ciphertext,uint32_t* RK);
void MaskedSeed(uint32_t* plaintext,uint32_t* ciphertext,uint32_t* MK,uint32_t* RK);

#endif /* MaskedSeed.h */