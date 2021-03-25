#include "KeySchedule.h"

uint32_t KeyConstant[16] = {
    0x9e3779b9,0x3c6ef373,
    0x78dde6e6,0xf1bbcdcc,
    0xe3779b99,0xc6ef3733,
    0x8dde6e67,0x1bbcdccf,
    0x3779b99e,0x6ef3733c,
    0xdde6e678,0xbbcdccf1,
    0x779b99e3,0xef3733c6,
    0xde6e678d,0xbcdccf1b
};

void KeySchedule(uint32_t* MK,uint32_t* RK){

    uint8_t tmp = 0;

    for(int i=0;i<16;i++){
        RK[2*i]=G_function(MK[0]+MK[2]-KeyConstant[i]);
        RK[2*i+1]=G_function(MK[1]-MK[3]+KeyConstant[i]);
        if(!(i&0x1)){
            tmp = MK[1]&0xff;
            MK[1] = ((MK[0]&0xff)<<24)|((MK[1]>>8)&0x00ffffff);
            MK[0] = (tmp<<24)|((MK[0]>>8)&0x00ffffff);

        }
        else {
            tmp = ((MK[2]&0xff000000)>>24);
            MK[2] = ((MK[2]<<8)&0xffffff00) | ((MK[3]&0xff000000)>>24);
            MK[3] = ((MK[3]<<8)&0xffffff00)|tmp;
        }
    }

}