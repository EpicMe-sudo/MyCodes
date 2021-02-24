#include "MaskingFunction.h"

void GenCarryTable(uint8_t m,uint8_t* C1,uint8_t* C2,uint8_t R){

    for(int i=0;i<16;i++){
       
        if(i<(m&0xf)){
            C1[i] = R+1;
        }
        else{
            C1[i] = R;
        }

        if(i<((m>>4)&0xf)){
            C2[i] = R+1;
        }
        else if(i==((m>>4)&0xf)) {
            C2[i] = R+2;
        }
        else{
            C2[i] = R;
        }
    }
}

void RegCarry(uint32_t* var,uint8_t m){

    uint8_t carry,R;
    uint8_t C1[16],C2[16];
    uint32_t digit = 0x100;
    uint32_t tmp = (*var);
    //randombytes(&R,1);
    //shake128(&R,1,&R,1);
    R = (rand()&0xff);
    GenCarryTable(m,C1,C2,R);

    for(int i=0;i<3;i++){
        carry = C2[((tmp>>(i*8))&0xf0)>>4];
        if(carry == R+2){
            carry = C1[((tmp>>(i*8))&0x0f)];
        }
        (*var) -= carry*digit;
        (*var) += R*digit;
        digit *=0x100;
    }

}

void BtoA8(uint32_t* Mvar,uint8_t m){
    
    uint8_t R[4];
    uint8_t A,B;
    randombytes(R,4);
    shake128(R,4,R,4);
    //R[0] = rand();
    //R[1] = rand();
    //R[2] = rand();
    //R[3] = rand();

    //printf("R[0] : 0x%02x\n",R[0]);
    //printf("R[1] : 0x%02x\n",R[1]);
    //printf("R[2] : 0x%02x\n",R[2]);
    //printf("R[3] : 0x%02x\n",R[3]);

    for(int i=0;i<4;i++){
        if(R[i]&1){
            R[i]=0;
            B = R[i]^m;
            A = B^(((*Mvar)>>(i*8))&0xff);
            A = A + B;
            A = A - R[i];
            R[i] = A^R[i];
        }
        else{
            R[i]=-1;
            B = R[i]^m;
            A = B^(((*Mvar)>>(i*8))&0xff);
            A = A + B;
            A = A - R[i];
            R[i] = A^R[i];
        }
    }

    (*Mvar) = (R[3]<<24)|(R[2]<<16)|(R[1]<<8)|R[0];

}

void BtoA32(uint32_t* Mvar,uint8_t m){

    uint32_t R;
    uint32_t A,B,Ri;
    uint8_t tmp[4];
    randombytes(tmp,4);
    shake128(tmp,4,tmp,4);
    R = (tmp[3]<<24|tmp[2]<<16|tmp[1]<<8|tmp[0]);

    //R = rand();
    
    if(R&1){
        Ri=0;
        B = Ri^(m<<24|m<<16|m<<8|m);
        A = B^(*Mvar);
        A = A + B;
        A = A - Ri;
        (*Mvar) = A^Ri;
    }
    else{
        Ri=-1;
        B = Ri^(m<<24|m<<16|m<<8|m);
        A = B^(*Mvar);
        A = A + B;
        A = A - Ri;
        (*Mvar) = A^Ri;
    }

} 

void AtoB(uint32_t* var, uint8_t m){
    
}