#include "pwm.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器PWM 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//***************************定时器2初始化 给电机提供PWM***************************//
// TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71  
//arr：自动重装寄存器，psc分频系数
//PWM的频率 = 72MHz/ARR/PCS 例如  20K = 72M/3600/1 =  20K
 
//=====初始化PWM 20KHZ 高频可以防止电机低频时的尖叫====
// ARR= 3599 时频率为20Khz
// STBY直接拉高
//arr：自动重装寄存器，psc分频系数
//PWM的频率 = 72MHz/ARR/PCS 例如  20K = 72M/3600/1 =  20K

void TIM2_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置	 
	
	GPIO_InitTypeDef GPIO_InitStructure;  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);    	//TIM2时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能GPIOA时钟	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);   //GPIOA0复用为定时器2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);   //GPIOA1复用为定时器2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);   //GPIOA2复用为定时器2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM2);   //GPIOA3复用为定时器2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;    //GPIOA1,2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;            //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	    //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);                   //初始化PA1,2
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;                  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;                     //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);            //初始化定时器2
	
	//初始化TIM2 Channel 2,3,4 ——PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;    //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2
  
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR3上的预装载寄存器
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR4上的预装载寄存器
 
 
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器3更新中断
 
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM8中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	

	 TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPE使能 
	
	 TIM_Cmd(TIM2, ENABLE);  //使能TIM14										  
}  
//定时器2中断服务函数


void TIM8_Steer_Init(u32 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);//TIM3时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOB时钟
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);//PC9复用为TIM8
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);//PC8复用为TIM8
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8);//PC8复用为TIM8 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);//PC8复用为TIM8
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=arr;
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCNIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCIdleState_Reset;
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM8,ENABLE);//允许在定时器工作时向ARR的缓冲器中写入新值，以便在更新事件发生时载入覆盖以前的值
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	TIM_Cmd(TIM8,ENABLE);
}

void TIM1_Pwm_Init(u32 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//TIM1时钟使能
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOB时钟
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);//PC9复用为TIM8
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1);//PC8复用为TIM8
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_TIM1);//PC8复用为TIM8 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);//PC8复用为TIM8
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=arr;
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCNIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCIdleState_Reset;
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);//允许在定时器工作时向ARR的缓冲器中写入新值，以便在更新事件发生时载入覆盖以前的值
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_Cmd(TIM1,ENABLE);
}



void TIM3_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置	 
	
	GPIO_InitTypeDef GPIO_InitStructure;  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);    	//TIM2时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能GPIOA时钟	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);   //GPIOA0复用为定时器2
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);   //GPIOA1复用为定时器2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;    //GPIOA1,2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;            //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	    //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   //初始化PA1,2
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;                  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;                     //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);            //初始化定时器2
	
	//初始化TIM2 Channel 2,3,4 ——PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;    //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2
	
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM2在CCR3上的预装载寄存器
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM2在CCR4上的预装载寄存器
 
 
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
 
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM8中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	

	 TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	
	 TIM_Cmd(TIM3, ENABLE);  //使能TIM14										  
}  


void TIM10_PWM_Init(u32 arr,u32 psc)
{		 					 
GPIO_InitTypeDef GPIO_InitStructure;  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);    	//TIM2时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能GPIOA时钟	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM10);   //GPIOA0复用为定时器2

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;    //GPIOA1,2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;            //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	    //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   //初始化PA1,2
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;                  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;                     //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	
	TIM_TimeBaseInit(TIM10,&TIM_TimeBaseStructure);            //初始化定时器2
	
	//初始化TIM2 Channel 2,3,4 ——PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;    //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM10, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2 
	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器


  TIM_ITConfig(TIM10,TIM_IT_Update,ENABLE); //允许定时器3更新中断

	 TIM_ARRPreloadConfig(TIM10,ENABLE);//ARPE使能 
	 TIM_CtrlPWMOutputs(TIM10,ENABLE);
	 TIM_Cmd(TIM10, ENABLE);  //使能TIM14										
} 


void TIM11_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);    	//TIM2时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能GPIOA时钟	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11);   //GPIOA0复用为定时器2

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    //GPIOA1,2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;            //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	    //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   //初始化PA1,2
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;                  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;                     //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);            //初始化定时器2
	
	//初始化TIM2 Channel 2,3,4 ——PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;    //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM11, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2 
	TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器


  TIM_ITConfig(TIM11,TIM_IT_Update,ENABLE); //允许定时器3更新中断

	 TIM_ARRPreloadConfig(TIM11,ENABLE);//ARPE使能 
	 TIM_CtrlPWMOutputs(TIM11,ENABLE);
	 TIM_Cmd(TIM11, ENABLE);  //使能TIM14			
} 



void TIM9_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置	 
	
	GPIO_InitTypeDef GPIO_InitStructure;  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);    	//TIM2时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能GPIOA时钟	
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);   //GPIOA0复用为定时器2
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);   //GPIOA1复用为定时器2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;    //GPIOA1,2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;            //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	    //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure);                   //初始化PA1,2
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;                  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;                     //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=0; 	
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);            //初始化定时器2
	
	//初始化TIM2 Channel 2,3,4 ——PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;    //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2 
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM输出使能
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC2Init(TIM9, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器


  TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE); //允许定时器3更新中断

	 TIM_ARRPreloadConfig(TIM9,ENABLE);//ARPE使能 
	 TIM_CtrlPWMOutputs(TIM9,ENABLE);
	 TIM_Cmd(TIM9, ENABLE);  //使能TIM14										  
}  
