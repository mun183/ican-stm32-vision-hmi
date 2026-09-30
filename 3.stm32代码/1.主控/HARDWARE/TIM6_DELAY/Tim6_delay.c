#include "tim6_delay.h"
//#include "sys.h"
int flag_Tim6;
static unsigned int MS300=0;
#include "stm32f4xx.h"                  // Device header
#include "usart2dma.h"
void Tim_delay800(void)
{		
	flag_Tim6=1;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
		while(flag_Tim6==1)
		{}	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}

void Tim_delay400(void)
{		
	flag_Tim6=2;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
		while(flag_Tim6==2)
		{}	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}

void Tim_delay600(void)
{		
	flag_Tim6=3;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
		while(flag_Tim6==3)
		{}	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}
void Tim_delay200(void)
{		
	flag_Tim6=4;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
		while(flag_Tim6==4)
		{}	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}
void Tim_delay201(void)
{		
	flag_Tim6=5;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
    USART_SendData(USART2,0x15);
		while(flag_Tim6==5)
		{}	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}
void Tim_delay202(void)
{		
	flag_Tim6=5;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
    USART_SendData(USART2,0x16);
		while(flag_Tim6==5)
		{}	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}
void Tim_delay203(void)
{		
	flag_Tim6=5;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
    USART_SendData(USART2,0x17);
		while(flag_Tim6==5)
		{}	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}
void Tim_delay300(void)
{		
	flag_Tim6=6;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
		while(flag_Tim6==6)
		{
			if(Res_2==17)
			{flag_Tim6=0;
		 MS300=0;
				break;}
		
		}	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}
void Tim_delay100(void)
{		
	flag_Tim6=7;	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
		while(flag_Tim6==7)
		{}	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,DISABLE);
}
void TIM6_DAC_IRQHandler(void)          
{
static unsigned int MS800=0,MS400=0,MS600=0,MS200=0,MS20=0,MS100=0;
	if(TIM_GetFlagStatus(TIM6, TIM_IT_Update) != RESET)   //时间到了
	{ 
   if(flag_Tim6==1)
   {MS800++;}	
   if(flag_Tim6==2)
   {MS400++;}	
   if(flag_Tim6==3)
   {MS600++;}	 
	 if(flag_Tim6==4)
   {MS200++;}
	 if(flag_Tim6==5)
   {MS20++;}
	 if(flag_Tim6==6)
   {MS300++;}
	 if(flag_Tim6==7)
   {MS100++;}	 
	  if(MS800>800)
	  {
		 flag_Tim6=0;
		 MS800=0;
	  }
	 
	  if(MS400>400)
	  {
		 flag_Tim6=0;
		 MS400=0;
	  }
	  if(MS600>600)
	  {
		 flag_Tim6=0;
		 MS600=0;
	  }
		if(MS200>200)
	  {
		 flag_Tim6=0;
		 MS200=0;
	  }
    if(MS20>20)
	  {
		 flag_Tim6=0;
		 MS20=0;
	  }
		if(MS300>300)
	  {
		 flag_Tim6=0;
		 MS300=0;
	  }
		if(MS100>100)
	  {
		 flag_Tim6=0;
		 MS100=0;
	  }
	 TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);//清中断	
		
    }	
		 
}
