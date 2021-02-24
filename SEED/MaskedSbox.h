#ifndef __MASKEDSBOX_H__
#define __MASKEDSBOX_H__

#include "Sbox.h"

void GenMS2box(uint8_t* S2box,uint8_t* MS2box,uint8_t m0, uint8_t m2);
void GenMS1box(uint8_t* S1box,uint8_t* MS1box, uint8_t m0,uint8_t m2);

#endif /* MaskedSbox.h */

