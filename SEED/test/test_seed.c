#include "../seed.h"

int main(){

    uint32_t plaintext[SEED_INPUT_WORD]={0,};
    uint32_t ciphertext[SEED_OUTPUT_WORD] ={0,};
    uint32_t MK[SEED_MK_WORD] = {0x00010203,0x04050607,0x08090a0b,0x0c0d0e0f};
    uint32_t RK[SEED_RK_WORD];
    
    Seed(plaintext,ciphertext,MK,RK);

    printf("0x%08x 0x%08x 0x%08x 0x%08x \n",RK[4],RK[5],RK[6],RK[7]);
    printf("0x%08x 0x%08x 0x%08x 0x%08x \n",ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);
    printf("tmp : 0x%02x%02x%02x%02x\n",S2box[0x9b],S1box[0xf9],S2box[0xc6],S1box[0x24]);
}