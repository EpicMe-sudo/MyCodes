#include <stdio.h>

typedef unsigned char u8;

u8 GeninvSbox(u8 s){

    u8 tmp =0;
    s ^= 0x63;

    if(s&1) tmp ^= 0x4a;
    if(s&2) tmp ^= 0x94;
    if(s&4) tmp ^= 0x29;
    if(s&8) tmp ^= 0x52;
    if(s&16) tmp ^= 0xa4;
    if(s&32) tmp ^= 0x49;
    if(s^64) tmp ^= 0x92;
    if(s^128) tmp ^= 0x25;

    return inv(tmp);
}

int main(){

    return 0;
}