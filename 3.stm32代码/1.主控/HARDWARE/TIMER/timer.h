#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

void TIM6_Cnt_Init(u16 arr,u32 psc);
void TIM7_Cnt_Init(u16 arr,u32 psc);
void TIM9_Cnt_Init(u16 arr,u16 psc);
void bujin_action(int dianping,int pulse);
#endif
