#ifndef _PWM_H
#define _PWM_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/6/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//步进电机方向和使能控制io口定义
//DIR_1,ENA_1 ----摆线电机控制
//DIR_2,ENA_2 ----自摆电机控制
//DIR_1,DIR_2 ----为0时，电机上拉；为1时，电机下拉
//ENA_1,ENA_2 ----为0时，电机失能可以转动；为1时，电机使能不可转动

//#define DIR_1 PBout(12)	  
//#define DIR_2 PAout(9)	 
//#define ENA_1 PBout(13)	 
//#define ENA_2 PAout(10)	

//void DIR_Init(void);


#define ES08_X_(yuntai) TIM_SetCompare2(TIM2,yuntai);    ///改变括号里面的值就可以改变输出的量     //*云台旋转      min--1750       max--1950
#define ES08_Z_(zhijia) TIM_SetCompare4(TIM3,zhijia);    ///改变括号里面的值就可以改变输出的量     //*支架转动      min--1747   max--1947
void TIM11_PWM_Init(u32 arr,u32 psc);
void TIM9_PWM_Init(u32 arr,u32 psc);
void TIM10_PWM_Init(u32 arr,u32 psc);
void TIM2_PWM_Init(u32 arr,u32 psc);
void TIM3_PWM_Init(u32 arr,u32 psc);
void TIM8_Steer_Init(u32 arr,u32 psc);
void TIM1_Pwm_Init(u32 arr,u32 psc);

#endif
