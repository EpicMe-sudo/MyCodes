#include "MaskedSbox.h"

void GenMS2box(uint8_t* S2box,uint8_t* MS2box,uint8_t m0, uint8_t m2){

    uint8_t tmp;

    for(uint8_t i=0;i<0xff;i++){
        tmp = i+m0;
        MS2box[tmp] = S2box[i]^m2;
    }

}

void GenMS1box(uint8_t* S1box,uint8_t* MS1box, uint8_t m0,uint8_t m2){

    uint8_t tmp;

    for(uint8_t i=0;i<0xff;i++){
        tmp = i+m0;
        MS1box[tmp] = S1box[i]^m2;
    }
    

}

