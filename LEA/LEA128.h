#ifndef __LEA128_H__
#define __LEA128_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NumberOfBit_Word 32
#define NumberOfBit_Byte 8
#define NumberOfBit_Bit 1

typedef unsigned int WORD;
typedef unsigned char BYTE;

extern unsigned int delta[8];

typedef struct _RoundKey {
   WORD RK[6];
} RoundKey;

extern WORD RotationLeft(WORD word, const unsigned int NumberOfBitToShift);
extern WORD RotationRight(WORD word, const unsigned int NumberOfBitToShift);

extern void LeaKeySchedule128(BYTE MK[16], RoundKey RoundKey[24]);
extern void Round(unsigned int* Plaintext, unsigned int* Ciphertext, RoundKey* RoundKey);
extern void LEA_Encryption128(unsigned int* Plaintext, unsigned int* Ciphertext, RoundKey* RoundKey);

#endif