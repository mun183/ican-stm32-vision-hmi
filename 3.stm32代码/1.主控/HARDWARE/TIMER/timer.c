#include "timer.h"
#include "exti.h"


int zd_site=0;

void TIM7_Cnt_Init(u16 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/***********************Clock initial****************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE); //??TIM5??
	
	/***********************Timer initial****************************************/	 
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//???TIM5
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //?????5????0.................................................
	TIM_Cmd(TIM7,ENABLE); //?????6
	
	 /***********************NVIC initial****************************************/
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //???5??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/*******************************************步进调速2，不分频，不用专属定时器*/////////////////////////////////////////////
/*******************************************不调速就很简单，同思路  400转一圈*/////////////////////////////////////////////

/*******************************************步进调速3，不分频，用专属定时器*14       */////////////////////////////////////////////
void TIM6_Cnt_Init(u16 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/***********************Clock initial****************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE); //??TIM5??
	
	/***********************Timer initial****************************************/	 
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//???TIM5
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //?????5????0.................................................
	TIM_Cmd(TIM6,ENABLE); //?????6
	
	 /***********************NVIC initial****************************************/
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; //???5??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

//void TIM6_DAC_IRQHandler(void)          
//{
//	

//}
