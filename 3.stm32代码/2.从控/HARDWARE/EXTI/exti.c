#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "stdio.h"
#include "usart.h"
#include "oled.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

////外部中断0服务程序
//void EXTI0_IRQHandler(void)
//{
//	delay_ms(10);	//消抖
//	if(WK_UP==1)	 
//	{
//		BEEP=!BEEP; //蜂鸣器翻转 
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
//}	
//外部中断2服务程序

int Front_cishu=1;
int Left_cishu=100;

int First_count=0;
int Second_count=0;

int First_count2=0;
int Second_count2=0;

int First_count3=0;
int Second_count3=0;

int First_count4=0;
int Second_count4=0;

int First_count5=0;
int Second_count5=0;

int First_count6=0;
int Second_count6=0;

int First_count7=0;
int First_count8=0;
int First_count9=0;
int First_count10=0;
int First_count11=0;
int First_count12=0;
int First_count13=0;
int First_count14=0;
int First_count15=0;
int First_count16=0;
int First_count17=0;
int First_count18=0;
int First_count19=0;
int First_count20=0;
int First_count21=0;
int First_count22=0;
int First_count23=0;
int First_count24=0;
int First_count25=0;
int First_count26=0;
int First_count27=0;
int First_count28=0;
int First_count29=0;
int First_count30=0;
int First_count31=0;
int First_count32=0;
int First_count33=0;
int First_count34=0;
int First_count35=0;
int First_count36=0;
int First_count37=0;
int First_count38=0;
int First_count39=0;
int First_count40=0;


int Second_count7=0;


extern int zd_site;
//void EXTI2_IRQHandler(void)
//{
//	delay_ms(10);	//消抖
//	if(KEY4==0)	  
//	{				 
//   GPIO_ResetBits(GPIOE,GPIO_Pin_6) ;//复位F9 点亮D1
//	 delay_ms(1000);	
//	 GPIO_SetBits(GPIOE,GPIO_Pin_6) ;//复位F9 点亮D1
//	 delay_ms(1000);	
//		
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
//}
////外部中断3服务程序


//void EXTI9_5_IRQHandler(void)
//{
//		static int flag1=0;
//    delay_ms(10);	//消抖
//	  if(flag1==1)
//	{
//	   gezi=1;
//	}
//	 flag1++;
//	 EXTI_ClearITPendingBit(EXTI_Line9); //清除LINE0上的中断标志位 
//}	


void EXTI3_IRQHandler(void)/////////////前中222
{
	static int flag2=0;
	delay_ms(20);	//消抖
  if(Left_cishu==1) 
	 {if(flag2==1)
			{
			  Second_count=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
	 }
	 }
	 
	if(Left_cishu==2)
	{	if(flag2==1)
			{
				Second_count4=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
			}
		}	
	
	if(Left_cishu==6)
	{	if(flag2==1)
			{
				First_count10=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
			}
		}
		if(Left_cishu==8)
	{
		if(flag2==1)
			{
				First_count13=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
			}
		}
		if(Left_cishu==11)
	{
		if(flag2==1)
			{
				First_count24=1;
				EXTIX2_Init(DISABLE);
				flag2=0;
			}
		}

		
	
		
   flag2++;	
	 EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE0上的中断标志位 
}	
	
void EXTI0_IRQHandler(void)//////////////////前右111
{
	static int flag1=0;
	delay_ms(20);	//消抖
 
	
	 
		
	
		if(Left_cishu==14)
		{
			if(flag1==1)
					{
						First_count37=0;
					}		
			if(flag1==3)
					{
						First_count37=1;
					}	
			if(flag1==5)
					{
						First_count37=2;
					}	
					if(flag1==7)
					{
						First_count37=3;
						EXTIX1_Init(DISABLE);
						flag1=0;
					}	
				}
		
//		if(Left_cishu==15)
//		{
//			if(flag1==1)
//					{
//						First_count39=0;
//					}		
//			if(flag1==3)
//					{
//						First_count39=1;
//					}	
//			if(flag1==5)
//					{
//						First_count39=2;
//					}	
//					if(flag1==7)
//					{
//						First_count39=3;
//					}	
//					if(flag1==9)
//					{
//						First_count39=4;
//					}	
//					if(flag1==11)
//					{
//						First_count39=5;
//						EXTIX1_Init(DISABLE);
//						flag1=0;
//					}	
//				}
				
				
				flag1++;	
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	

void EXTI2_IRQHandler(void)/////////////////////左前333
{
	static int flag3=0;
	delay_ms(20);	//消抖
		if(Left_cishu==1)
		{
			if(flag3==1)
					{
						Second_count2=1;
						EXTIX3_Init(DISABLE);
						flag3=0;				
					}		
		}
if(Left_cishu==6)	
		{
		
			if(flag3==1)
			{
				First_count18=1;
				EXTIX3_Init(DISABLE);
				flag3=0;
			}
		}
		 if(Left_cishu==8)	
		{
			
			if(flag3==1)
			{
				First_count20=1;
					EXTIX3_Init(DISABLE);
				flag3=0;
			}
		}
			if(Left_cishu==10)	
		{
			
			if(flag3==1)
			{
				First_count22=1;
				EXTIX3_Init(DISABLE);
				flag3=0;
			}
		} 			
		

		
		
   flag3++;	
	 EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE0上的中断标志位 
}	

void EXTI9_5_IRQHandler(void)//////////////////左中444
{
	static int flag4=0;
	delay_ms(20);	//消抖
if(Left_cishu==1)	
{
		if(flag4==1)
			{
				Second_count3=1;
				EXTIX4_Init(DISABLE);
				//EXTIX1_Init(ENABLE);
				flag4=0;
			}			
}	
if(Left_cishu==2)	
{
		if(flag4==1)
			{
				Second_count5=1;
				EXTIX4_Init(DISABLE);
				//EXTIX1_Init(ENABLE);
				flag4=0;
			}			
}	
if(Left_cishu==4)	
{
		if(flag4==1)
			{
				First_count31=1;
				EXTIX4_Init(DISABLE);
				//EXTIX1_Init(ENABLE);
				flag4=0;
			}			
}

if(Left_cishu==12)	
{
		if(flag4==1)
			{
				First_count26=1;
				EXTIX4_Init(DISABLE);
				//EXTIX1_Init(ENABLE);
				flag4=0;
			}			
}	

if(Left_cishu==14)
		{
			if(flag4==1)
					{		
						First_count38=1;
						EXTIX4_Init(DISABLE);
						flag4=0;
					}		
				}
if(Left_cishu==15)
		{
			if(flag4==1)
					{		
						First_count40=1;
						EXTIX4_Init(DISABLE);
						flag4=0;
					}		
				}		
   flag4++;	
	 EXTI_ClearITPendingBit(EXTI_Line9); //清除LINE0上的中断标志位 
	
}


void EXTI15_10_IRQHandler(void)////////////////左后555
{
	static int flag5=0;
	delay_ms(20);	//消抖
  if(Left_cishu==1)	
		{if(flag5==1)
			{
				First_count3=1;
				EXTIX5_Init(DISABLE);
				EXTIX4_Init(ENABLE);
				flag5=0;
			}
		}
		
		if(Left_cishu==2)
		{
			if(flag5==1)
					{
						Second_count4=0;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}		
			if(flag5==3)
					{
						Second_count4=1;
						EXTIX5_Init(DISABLE);
							zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==5)
					{
						Second_count4=2;
						EXTIX5_Init(DISABLE);
							zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==7)
			{
				Second_count4=3;
				EXTIX5_Init(DISABLE);
					zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
			}	
			if(flag5==9)
			{
				Second_count4=4;
				EXTIX5_Init(DISABLE);
					zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
			}
			if(flag5==11)
			{
			Second_count4=5;
				EXTIX5_Init(DISABLE);
					zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
			}
			if(flag5==13)
			{
				Second_count4=6;
				EXTIX5_Init(DISABLE);
				flag5=0;
			}		
		}	
		
		if(Left_cishu==4)
		{
			if(flag5==1)
					{
						First_count6=0;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}		
			if(flag5==3)
					{
						First_count6=1;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==5)
					{
						First_count6=2;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==7)
			{
				First_count6=3;
				EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
			}	
			if(flag5==9)
			{
			  First_count6=4;
				EXTIX5_Init(DISABLE);
				EXTIX4_Init(ENABLE);
				flag5=0;
			}
			
		}	
		
		 if(Left_cishu==5)	
		{if(flag5==1)
			{
				First_count17=1;
				EXTIX5_Init(DISABLE);
				flag5=0;
			}
		}	
		 
		  if(Left_cishu==7)	
		{
			if(flag5==1)
			{
				First_count19=1;
				EXTIX5_Init(DISABLE);
				flag5=0;
			}
		}
		
		 if(Left_cishu==9)	
		{
			if(flag5==1)
			{
				First_count21=1;
				EXTIX5_Init(DISABLE);
				flag5=0;
			}			
		}
		
		
	
			if(Left_cishu==12)
		{
			if(flag5==1)
					{
						First_count25=0;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}		
			if(flag5==3)
					{
						First_count25=1;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==5)
					{
						First_count25=2;
						EXTIX5_Init(DISABLE);
						zd_site=5;
						TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==7)
			{
				First_count25=3;
				EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
			}	
			if(flag5==9)
			{
				First_count25=4;
				EXTIX5_Init(DISABLE);
				flag5=0;	
			}	
		}	
		
			if(Left_cishu==100)
		{
			if(flag5==1)
					{
						First_count36=0;
					}		
			if(flag5==3)
					{
						First_count36=1;
						EXTIX5_Init(DISABLE);
						flag5=0;	
					}	
		}	
		
			if(Left_cishu==15)
		{
			if(flag5==1)
					{
						First_count39=0;
						EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
					}		
			if(flag5==3)
					{
						First_count39=1;
						EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
					}	
			if(flag5==5)
					{
						First_count39=2;
						EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
					}	
					if(flag5==7)
					{
						First_count39=3;
						EXTIX5_Init(DISABLE);
				zd_site=5;
				TIM_Cmd(TIM6,ENABLE);
					}	
					if(flag5==9)
					{
						First_count39=4;
					EXTIX5_Init(DISABLE);
						EXTIX4_Init(ENABLE);
						flag5=0;
					}	
					
				}
		
   flag5++;	
	 EXTI_ClearITPendingBit(EXTI_Line11); //清除LINE0上的中断标志位 
}	

void EXTI1_IRQHandler(void)/////////////////后左666
{
	static int flag6=0;
	delay_ms(20);	//消抖
	
		if(Left_cishu==1)
		{if(flag6==1)
		    {
			    First_count=0;
					GPIO_SetBits(GPIOE,GPIO_Pin_1) ;//复位F9 点亮D1
		    }
		if(flag6==3)
				{
					First_count=1;
				}
		if(flag6==5)
				{
					First_count=3;
						
				}		
	  if(flag6==7)
				{
					First_count=4;
				
				}		
				if(flag6==9)
				{
					First_count=5;
				
				}	
					if(flag6==11)
				{
					First_count=6;
					//First_count=6;
					EXTIX6_Init(DISABLE);
					//EXTIX2_Init(ENABLE);
					flag6=0;
				}		  	
			}	
	
	
	
	
	
	
	if(Left_cishu==2)	
	{	
	   
			if(flag6==1)
			{
				First_count4=0;
			}
		
			if(flag6==3)
			{
				First_count4=1;
				EXTIX6_Init(DISABLE);
				EXTIX2_Init(ENABLE);
				flag6=0;
			}
	}
	if(Left_cishu==3)	
		{
			if(flag6==1)
			{
				First_count5=0;
			}
		
			if(flag6==3)
			{
				First_count5=1;
			}
				if(flag6==5)
			{
				First_count5=2;
				EXTIX6_Init(DISABLE);
				//EXTIX2_Init(ENABLE);
				flag6=0;
			}
	 	}
	if(Left_cishu==11)	
		{
			if(flag6==1)
			{
				First_count23=0;
			}
		
			if(flag6==3)
			{
				First_count23=1;
				EXTIX6_Init(DISABLE);
				EXTIX2_Init(ENABLE);
				flag6=0;
			}

	 	}

	 	
   flag6++;	
	 EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位 
}	

//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX1_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;

	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 连接到中断线0
// 
//	/* 配置EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
//  EXTI_Init(&EXTI_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource0);//PA0 连接到中断线0
 
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}


void EXTIX2_Init(FunctionalState NewState)
{
	
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
//	KEY_Init(); //按键对应的IO口初始化

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource2);//PE2 连接到中断线2
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource3);//PE3 连接到中断线3
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource4);//PE4 连接到中断线4

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);//PA0 连接到中断线0
  /* 配置EXTI_Line0 */
//  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
//  EXTI_Init(&EXTI_InitStructure);//配置
	
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
//	
//	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	

//	
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
}

void EXTIX3_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;

	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 连接到中断线0
// 
//	/* 配置EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
//  EXTI_Init(&EXTI_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource2);//PA0 连接到中断线0
 
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}

void EXTIX4_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 连接到中断线0
// 
//	/* 配置EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
//  EXTI_Init(&EXTI_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 连接到中断线0
 
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}

void EXTIX5_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
  
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 连接到中断线0
// 
//	/* 配置EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
//  EXTI_Init(&EXTI_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource11);//PA0 连接到中断线0
 
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}

void EXTIX6_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;

	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 连接到中断线0
// 
//	/* 配置EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
//  EXTI_Init(&EXTI_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1);//PA0 连接到中断线0
 
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}






