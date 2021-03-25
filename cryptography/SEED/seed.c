#include "seed.h"

void SeedEncryption(uint32_t* plaintext,uint32_t* ciphertext,uint32_t* RK){

    uint32_t tmp;

    ciphertext[0] = plaintext[0];
    ciphertext[1] = plaintext[1];
    ciphertext[2] = plaintext[2];
    ciphertext[3] = plaintext[3];
    
    for(int i=0;i<16;i+=2){
        F_function(ciphertext,ciphertext+2,RK+2*i);
        printf(" Round[ %02d ] : 0x%08x 0x%08x 0x%08x 0x%08x \n",i,ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);
        F_function(ciphertext+2,ciphertext,RK+2*(i+1));
        printf(" Round[ %02d ] : 0x%08x 0x%08x 0x%08x 0x%08x \n",i+1,ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);
    }

    tmp = ciphertext[0];
    ciphertext[0] = ciphertext[2];
    ciphertext[2] = tmp;
    tmp = ciphertext[1];
    ciphertext[1] = ciphertext[3];
    ciphertext[3] = tmp;
}

void Seed(uint32_t* plaintext,uint32_t* ciphertext,uint32_t* MK,uint32_t* RK){

    KeySchedule(MK,RK);
    SeedEncryption(plaintext,ciphertext,RK);

}