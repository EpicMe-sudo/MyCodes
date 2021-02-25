#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "complex_num.h"

typedef struct _vec {
    unsigned long long length;
    Complex* arr;
} vec;
typedef vec* vecRef;

vecRef vecAlloc(unsigned long long length);
void vecRelease(vecRef* arr);

void vadd(vecRef x, vecRef y, vecRef* output);
void vsubtrace(vecRef x, vecRef y, vecRef* output);
void vmultiply(vecRef x, vecRef y, vecRef* output);
void vdivide(vecRef x, vecRef y, vecRef* output);

void vaddScalar(vecRef x, Complex c, vecRef* output);
void vsubScalar(vecRef x, Complex c, vecRef* output);
void vmulScalar(vecRef x, Complex c, vecRef* output);
void vdivScalar(vecRef x, Complex c, vecRef* output);

#endif /* vector.h */