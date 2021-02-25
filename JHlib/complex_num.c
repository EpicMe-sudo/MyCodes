#include "complex_num.h"

Real cAbsolute(Complex x){
    return sqrt((x.re*x.re)+(x.im*x.im));
}

Real cArgument(Complex x){
    return atan(x.im/x.re);
}

Complex cAdd(Complex x, Complex y){
    Complex tmp;
    tmp.re = x.re + y.re;
    tmp.im = x.im + y.im;
    return tmp;
}

Complex cSubtract(Complex x,Complex y){
    Complex tmp;
    tmp.re = x.re - y.re;
    tmp.im = x.im - y.im;
    return tmp;
}

Complex cMultiply(Complex x,Complex y){
    Complex tmp;
    tmp.re = x.re*y.re - x.im*y.im;
    tmp.im = x.re*y.im + x.im*y.re;
    return tmp;
}

Complex cDivide(Complex x,Complex y){ // x/y
    Complex tmp;
    tmp.re = (x.re*y.re+x.im*y.im)/(y.re*y.re + y.im*y.im);
    tmp.im = (x.im*y.re - x.re*y.im)/(y.re*y.re + y.im*y.im);
    return tmp;
}

Complex cNegate(Complex x){
    x.re = -x.re;
    x.im = -x.im;
    return x;
}

Complex cConjugate(Complex x){
    x.im = -x.im;
    return x;
}

Complex cPolarToComplex(Real length,Real angle){
    Complex tmp;
    tmp.re = length*cos(angle);
    tmp.im = length*sin(angle);
    return tmp;
}