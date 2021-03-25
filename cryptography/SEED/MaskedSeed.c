#include "MaskedSeed.h"
#include <stdio.h>
#include "time.h"

void MaskedSeedEncryption(uint32_t* plaintext,uint32_t* ciphertext,uint32_t* RK){

    uint32_t tmp;

    ciphertext[0] = plaintext[0];
    ciphertext[1] = plaintext[1];
    ciphertext[2] = plaintext[2];
    ciphertext[3] = plaintext[3];
    uint8_t M[3];
    uint8_t MS1box[256],MS2box[256];

    //randombytes(M,3);
    //shake128(M,3,M,3);
    srand(time(NULL));
    M[0] = rand()&0xff;
    M[1] = rand()&0xff;
    M[2] = M[0]^M[1];
    //M[0] = 0xf0;
    //M[1] = 0x0f;
    //M[2] = M[0]^M[1];

    GenMS1box(S1box,MS1box,M[0],M[2]);
    GenMS2box(S2box,MS2box,M[0],M[2]);
    
    MF_function(ciphertext,ciphertext+2,RK,M,MS1box,MS2box);
    printf(" Round[ 01 ] : 0x%08x 0x%08x 0x%08x 0x%08x \n",ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);

    F_function(ciphertext+2,ciphertext,RK+2);
    printf(" Round[ 02 ] : 0x%08x 0x%08x 0x%08x 0x%08x \n",ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);

    for(int i=2;i<14;i+=2){
        F_function(ciphertext,ciphertext+2,RK+2*i);
        printf(" Round[ %02d ] : 0x%08x 0x%08x 0x%08x 0x%08x \n",i,ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);
        F_function(ciphertext+2,ciphertext,RK+2*(i+1));
        printf(" Round[ %02d ] : 0x%08x 0x%08x 0x%08x 0x%08x \n",i+1,ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);
    }

    F_function(ciphertext,ciphertext+2,RK+28);
    printf(" Round[ 14 ] : 0x%08x 0x%08x 0x%08x 0x%08x \n",ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);

    MF_function(ciphertext+2,ciphertext,RK+30,M,MS1box,MS2box);
    printf(" Round[ 15 ] : 0x%08x 0x%08x 0x%08x 0x%08x \n",ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);

    tmp = ciphertext[0];
    ciphertext[0] = ciphertext[2];
    ciphertext[2] = tmp;
    tmp = ciphertext[1];
    ciphertext[1] = ciphertext[3];
    ciphertext[3] = tmp;
}

void MaskedSeed(uint32_t* plaintext,uint32_t* ciphertext,uint32_t* MK,uint32_t* RK){

    KeySchedule(MK,RK);
    MaskedSeedEncryption(plaintext,ciphertext,RK);

}