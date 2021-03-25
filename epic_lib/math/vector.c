#include "vector.h"

vecRef vecAlloc(unsigned long long length){
    vecRef tmp = (vecRef)malloc(sizeof(vec));
    tmp->length = length;
    tmp->arr = (Complex*)calloc(sizeof(Complex),length);
    return tmp;
}

void vecRelease(vecRef vector){
    free(vector->arr);
    free(vector);
}

void vadd(vecRef x, vecRef y, vecRef* output){

}

void vsubtrace(vecRef x, vecRef y, vecRef* output){

}

void vmultiply(vecRef x, vecRef y, vecRef* output){
    
}

void vdivide(vecRef x, vecRef y, vecRef* output){

}

void vaddScalar(vecRef x, Complex c, vecRef* output){

}

void vsubScalar(vecRef x, Complex c, vecRef* output){

}

void vmulScalar(vecRef x, Complex c, vecRef* output){

}

void vdivScalar(vecRef x, Complex c, vecRef* output){

}
