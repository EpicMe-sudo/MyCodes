#include "MaskedFandG.h"

void MG_function(uint32_t* plaintext,uint8_t* M,uint8_t* MS1box,uint8_t* MS2box){

    uint8_t Y[4];
    uint8_t m0 = 0xfc, m1 = 0xf3, m2 = 0xcf, m3 = 0x3f;

    Y[0]=MS1box[(*plaintext)&0xff];
    Y[1]=MS2box[((*plaintext)&0xff00)>>8];
    Y[2]=MS1box[((*plaintext)&0xff0000)>>16];
    Y[3]=MS2box[((*plaintext)&0xff000000)>>24];

    (*plaintext) = ((((Y[0]&m3)<<24)|((Y[0]&m2)<<16)|((Y[0]&m1)<<8)|((Y[0])&m0))^\
    (((Y[1]&m0)<<24)|((Y[1]&m3)<<16)|((Y[1]&m2))<<8|((Y[1])&m1))^\
    (((Y[2]&m1)<<24)|((Y[2]&m0)<<16)|((Y[2]&m3))<<8|((Y[2])&m2))^\
    (((Y[3]&m2)<<24)|((Y[3]&m1)<<16)|((Y[3]&m0))<<8|((Y[3])&m3)))^\
    ((M[0]<<24)|(M[0]<<16)|(M[0]<<8)|M[0]);

}

void MF_function(uint32_t* Left,uint32_t* Right,uint32_t* RK,uint8_t* M,uint8_t* MS1box,uint8_t* MS2box){

    uint32_t tmp[2];
    tmp[0] = (*Right)^(*RK)^(((*(M+1)))<<24|((*(M+1)))<<16|((*(M+1)))<<8|((*(M+1))));
    tmp[1] = (*(Right+1))^(*(RK+1))^(((*(M+2)))<<24|(*(M+2))<<16|(*(M+2))<<8|(*(M+2)));

    tmp[1] ^= tmp[0];

    BtoA8(tmp+1,M[0]);
    MG_function(tmp+1,M,MS1box,MS2box);
    tmp[1] ^= (M[2]<<24)|(M[2]<<16)|(M[2]<<8)|(M[2]);

    BtoA32(tmp,M[1]);
    BtoA32(tmp+1,M[0]);

    tmp[0] += tmp[1];
    tmp[0] -= (M[1]<<24)|(M[1]<<16)|(M[1]<<8)|(M[1]);

    RegCarry(tmp,M[0]);

    MG_function(tmp,M,MS1box,MS2box);
    BtoA32(tmp,M[1]);

    tmp[1] += tmp[0];
    tmp[1] -= (M[1]<<24)|(M[1]<<16)|(M[1]<<8)|(M[1]);

    RegCarry(tmp+1,M[0]);
    MG_function(tmp+1,M,MS1box,MS2box);
    
    Left[1] ^= tmp[1]^((M[1]<<24)|(M[1]<<16)|(M[1]<<8)|(M[1]));

    BtoA32(tmp+1,M[1]);
    Left[0] ^= (tmp[0] + tmp[1] -2*((M[1]<<24)|(M[1]<<16)|(M[1]<<8)|M[1]));

}
