#include <stdio.h>

unsigned int test(unsigned char var){

    return var<<24|\
    var<<16|\
    var<<8|\
    var;
}

int main(){

    printf("0x%08x\n",test(0xff));

    return 0;
}