#include "Mult.h"

uint8_t MUL(uint8_t X,uint8_t Y){

    uint8_t tmp=0;
    for(int i=0;i<8;i++){
        if(Y&1){
            tmp ^= X;
        }
        Y = Y>>1;
        X = (X&0x80)?(X<<1)^0x63:(X<<1);
    }

    return tmp;
}

/*
int main(){

    printf("%d\n",MUL(64,64));

    return 0;
}
*/