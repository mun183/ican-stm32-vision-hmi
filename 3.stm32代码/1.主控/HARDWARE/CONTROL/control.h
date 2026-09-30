#ifndef __CAR_H
#define __CAR_H
#include "sys.h"

//extern uint16_t distance_left;
//extern uint16_t distance_right;
void TIM6_DAC_IRQHandler(void);
void Encoder_Fabs(void); 
float	Limit_Pwm_float(float pwm,float pwm_min,float pwm_max);
extern u16 distance;
extern u16 HFTD;
extern u16 clean_shoe_1;
extern u16 xd_shoe_1;

#endif
