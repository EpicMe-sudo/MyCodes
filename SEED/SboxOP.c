#include "SboxOP.h"

uint8_t S1box(uint8_t input){
    
    uint8_t output = 169;// b1
    uint8_t tmp =  input;
    tmp = MUL(tmp,tmp);  // tmp^2 4
    tmp = MUL(tmp,input);// tmp^3 8
    tmp = MUL(tmp,tmp);  // tmp^6 64
    tmp = MUL(tmp,input);// tmp^7 128
    tmp = MUL(tmp,tmp);  // tmp^14 100
    tmp = MUL(tmp,input);// tmp^15 200
    tmp = MUL(tmp,tmp);  // tmp^30 61 
    tmp = MUL(tmp,tmp);  // tmp^60 221
    tmp = MUL(tmp,input);// tmp^61 217
    tmp = MUL(tmp,tmp);  // tmp^122 95
    tmp = MUL(tmp,input);// tmp^123 190
    tmp = MUL(tmp,tmp);  // tmp^246 188
    tmp = MUL(tmp,input);// tmp^247 27

    if(tmp&0x01){ output ^= 0x2c;}
    if(tmp&0x02){ output ^= 0xd0;}
    if(tmp&0x04){ output ^= 0x69;}
    if(tmp&0x08){ output ^= 0xa2;}
    if(tmp&0x10){ output ^= 0x41;}
    if(tmp&0x20){ output ^= 0x44;}
    if(tmp&0x40){ output ^= 0x58;}
    if(tmp&0x80){ output ^= 0xe2;}

    return output;
}

uint8_t S2box(uint8_t input){

    uint8_t output = 56; // b2
    uint8_t tmp =  input;
    tmp = MUL(tmp,tmp);  // tmp^2
    tmp = MUL(tmp,input);// tmp^3
    tmp = MUL(tmp,tmp);  // tmp^6
    tmp = MUL(tmp,input);// tmp^7
    tmp = MUL(tmp,tmp);  // tmp^14
    tmp = MUL(tmp,input);// tmp^15
    tmp = MUL(tmp,tmp);  // tmp^30
    tmp = MUL(tmp,input);// tmp^31
    tmp = MUL(tmp,tmp);  // tmp^62
    tmp = MUL(tmp,tmp);  // tmp^124
    tmp = MUL(tmp,input);// tmp^125
    tmp = MUL(tmp,tmp);  // tmp^250
    tmp = MUL(tmp,input);// tmp^251

    if(tmp&0x01){ output ^= 0xd0;}
    if(tmp&0x02){ output ^= 0x2a;}
    if(tmp&0x04){ output ^= 0xe1;}
    if(tmp&0x08){ output ^= 0x2c;}
    if(tmp&0x10){ output ^= 0x21;}
    if(tmp&0x20){ output ^= 0x30;}
    if(tmp&0x40){ output ^= 0xa2;}
    if(tmp&0x80){ output ^= 0x6c;}

    return output;

}


int main(){

    S1box(2);

    for(int i=0;i<256;i++){
        printf("%4d   ",S2box(i));
        if((i+1)%8==0){
            printf("\n");
        }
    }

    return 0;
}
