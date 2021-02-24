#ifndef __KEYSCHEDULE_H__
#define __KEYSCHEDULE_H__

#include "FandG.h"

extern uint32_t KeyConstant[16];

void KeySchedule(uint32_t* MK,uint32_t* RK);

#endif /* KeySchedule.h */