#ifndef __COMPLEX_NUM_H__
#define __COMPLEX_NUM_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double Real;

typedef struct _complex{
    Real re;
    Real im;
} Complex;

Real cAbsolute(Complex x);
Real cArgument(Complex x);
Complex cAdd(Complex x, Complex y);
Complex cSubtract(Complex x,Complex y);
Complex cMultiply(Complex x,Complex y);
Complex cDivide(Complex x,Complex y);
Complex cNegate(Complex x);
Complex cPolarToComplex(Real length,Real angle);

#endif /* complex_num.h */