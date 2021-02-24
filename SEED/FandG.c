#include "FandG.h"

uint32_t G_function(uint32_t plaintext){
    
    uint8_t Y[4];
    uint8_t m0 = 0xfc, m1 = 0xf3, m2 = 0xcf, m3 = 0x3f;
    Y[0]=S1box[plaintext&0xff];
    Y[1]=S2box[(plaintext&0xff00)>>8];
    Y[2]=S1box[(plaintext&0xff0000)>>16];
    Y[3]=S2box[(plaintext&0xff000000)>>24];

    return (((Y[0]&m3)<<24)|((Y[0]&m2)<<16)|((Y[0]&m1)<<8)|((Y[0])&m0))^\
    (((Y[1]&m0)<<24)|((Y[1]&m3)<<16)|((Y[1]&m2))<<8|((Y[1])&m1))^\
    (((Y[2]&m1)<<24)|((Y[2]&m0)<<16)|((Y[2]&m3))<<8|((Y[2])&m2))^\
    (((Y[3]&m2)<<24)|((Y[3]&m1)<<16)|((Y[3]&m0))<<8|((Y[3])&m3));

}

void F_function(uint32_t* Left,uint32_t* Right,uint32_t* RK){

    uint32_t tmp[2];
    tmp[0] = (*Right)^(*RK);
    tmp[1] = (*(Right+1))^(*(RK+1));

    tmp[1] ^= tmp[0];
    
    tmp[1] = G_function(tmp[1]);
    tmp[0] += tmp[1];

    tmp[0] = G_function(tmp[0]);
    tmp[1] += tmp[0];

    tmp[1] = G_function(tmp[1]);
    tmp[0] += tmp[1];

    Left[0] ^= tmp[0];
    Left[1] ^= tmp[1];
}
/*

int main(){

    uint32_t Check = G_function((0x03020100 + 0x0b0a0908 -0x9e3779b9));

    printf("0x%08x\n",Check);
    return 0;
}
*/