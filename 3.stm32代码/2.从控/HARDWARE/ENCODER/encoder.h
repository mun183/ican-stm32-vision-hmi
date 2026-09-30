#ifndef  _ENCODER_H
#define  _ENCODER_H

#include "sys.h"



#define ENCODER_TIM_PERIOD (u16)(65535)   // number of pulses per revolution
extern int Encoder_Length_L1,Encoder_Length_R1,Encoder_Length_L2,Encoder_Length_R2;
typedef struct
{
	int Lf1;
	int Lf2;
	int Rt1;
	int Rt2;
}EncoderStru;

void Timer3_Init(u32 arr,int psc);
void MOTO_PWM_Init(u32 arr, int psc);
void MOTO_PWM_Out(u16 moto_r, u16 moto_l);
//void TIM6_PWM_Init(u32 arr,u32 psc);
void Timer6_Init(void);
void Read_Encoder(void);
void TIM3_Encoder_Init(u16 arr,u16 psc);
void TIM4_Encoder_Init(u16 arr,u16 psc);
void Encoder_Init_TIM4(void);
void TIM1_Encoder_Init(u16 arr,u16 psc);
void TIM2_Encoder_Init(u16 arr,u16 psc);
void TIM8_Encoder_Init(u16 arr,u16 psc);
void Encoder_Real(void);
#endif

