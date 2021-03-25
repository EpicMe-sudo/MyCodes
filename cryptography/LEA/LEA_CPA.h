#ifndef __LEA_CPA_H__
#define __LEA_CPA_H__

#include "LEA128.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>

#define _FOLD_ "/home/ubuntu/PowerConsumption/LEA/3/"
#define _1TraceFN "1trace.bin"
#define _2TraceFN "2trace.bin"
#define _3TraceFN "3trace.bin"
#define _4TraceFN "4trace.bin"
#define _5TraceFN "5trace.bin"
//#define AlignedTraceFN "AlignedTrace.bin"
#define _1Plaintext1FN "1textin.npy"
#define _2Plaintext1FN "2textin.npy"
#define _3Plaintext1FN "3textin.npy"
#define _4Plaintext1FN "4textin.npy"
#define _5Plaintext1FN "5textin.npy"

#define _1CiphertextFN "1textout.npy"
#define _1CiphertextFN "2textout.npy"
#define _1CiphertextFN "3textout.npy"
#define _1CiphertextFN "4textout.npy"
#define _1CiphertextFN "5textout.npy"

#define startpoint 0
#define endpoint 5999

double cov(float* x, float* y, int size);
double corr(float* x, float* y, int size);
void subalign(float* data1, float* data2, int windowsize, int stepsize, int threshold, int TraceLength);
void Alignment();
uint8_t KeyRecovery(uint8_t inferredkey,uint8_t number_of_RK);
void PCtest();
void CPA();

#endif /* LEA_CPA.h */