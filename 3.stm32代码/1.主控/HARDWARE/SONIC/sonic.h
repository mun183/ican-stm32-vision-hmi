/*
********************************************************************************************************************
*Filename              :UltrasonicWave.h
*Programmer(s)    :Lab 416
*Description          :UltrasonicWave function
********************************************************************************************************************
*/

#ifndef __sonic_H
#define	__sonic_H

#include "sys.h"


#define TIME_OUT 10000        //???????????


#define Trig1_on()  (GPIO_SetBits(GPIOE,GPIO_Pin_10))             //??Front_Trig
#define Trig1_off() (GPIO_ResetBits(GPIOE,GPIO_Pin_10)) 

#define Trig2_on()  (GPIO_SetBits(GPIOE,GPIO_Pin_11))             //??Front_Trig
#define Trig2_off() (GPIO_ResetBits(GPIOE,GPIO_Pin_11)) 

#define Trig3_on()  (GPIO_SetBits(GPIOE,GPIO_Pin_12))             //??Front_Trig
#define Trig3_off() (GPIO_ResetBits(GPIOE,GPIO_Pin_12)) 

#define Trig4_on()  (GPIO_SetBits(GPIOE,GPIO_Pin_13))             //??Front_Trig
#define Trig4_off() (GPIO_ResetBits(GPIOE,GPIO_Pin_13)) 

#define Trig5_on()  (GPIO_SetBits(GPIOE,GPIO_Pin_14))             //??Front_Trig
#define Trig5_off() (GPIO_ResetBits(GPIOE,GPIO_Pin_14)) 

#define Trig6_on()  (GPIO_SetBits(GPIOE,GPIO_Pin_15))             //??Front_Trig
#define Trig6_off() (GPIO_ResetBits(GPIOE,GPIO_Pin_15)) 

typedef struct 
{
	
	int A_1;
	int A_2;
	int A_3;
	int A_4;
	int A_5;
	int A_6;
//	float A_1;
//	float A_2;
//	float A_3;
//	float A_4;
//	float A_5;
//	float A_6;

}SonicDis;

extern SonicDis Sonic_Dis;


/*
******************************************************************************************************************
*                                            FUNCTION PROTOTYPES
******************************************************************************************************************
*/

void Ultra_Init(void);//???IO??????
void Ultrasonic_Trig_Start(void);
void Sonic_Get_Distance(void);//????

void TIM5_Sonic_Cap_Init(u32 arr,u16 psc);
void TIM3_Sonic_Cap_Init(u32 arr,u16 psc);
void TIM5_IRQHandler(void);
void TIM3_IRQHandler(void);
int Sonic_Length(float l1,float l2);
int Sonic_Length_l(float l1,float l2);


#endif 



