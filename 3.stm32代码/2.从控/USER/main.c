#include "sys.h"					//STM32F407开发板的系统初始化底层函数
#include "delay.h"				//delay
#include "usart.h"				//串口
#include "led.h"					//LED
#include "key.h"					//按键
#include "oled.h"					//OLED
#include "motor.h"				//
#include "pwm.h"					//PWM
#include "control.h"			//控制函数
#include "shoe.h"					//2025年智能家居刷鞋机构				
#include "pid.h"					//PID	
#include "encoder.h"			//编码器
#include "timer.h"				//定时器
#include "exti.h"					//EXTI
#include "duoji.h"				//舵机
#include "sonic.h"				//超声波
#include "adc.h"
#include "math.h"
#include "stdio.h"
#include "usartdma.h"			//串口1
#include "usart2dma.h"		//串口2
#include "usart3DMA.h"		//串口3
#include "usart4dma.h"		//串口4
#include "usart5dma.h"		//串口5
#include "photoelectric.h"//光电管
#include "dianji.h"				//


//7.98v 11.68v
extern uint16_t speeda,speedb,speedc,speedd;//四个定义舵机状态的变量
extern float speed_yaw;
LobotServo servos[6];
u8 receive_count = 0;    // 新增定义

int main(void)
{ 
	//TIM1、8--11是168M，2——7,12——14是84M
	 	SystemInit();//系统时钟等初始化
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
		delay_init(168);//初始化延时函数
		KEY_Init();     //按键初始化
		LED_Init();	    //LED初始化
		OLED_Init();    //OLED初始化
		stepper_init(0XFFFF, 84-1);
//--------------------串口总线舵机------------------------//
		USART3_Init(9600);//维特智能3
		servos[0].ID = 1;	//设置舵机ID
		servos[1].ID = 2;
		servos[2].ID = 3;
		servos[3].ID = 4;	
		servos[4].ID = 5;
		servos[5].ID = 6;
//--------------------串口总线舵机------------------------//
	
		USART1_Init(9600);					//--------------------下摄像头------------------------//		
		USART2_Init(9600);					//--------------------上摄像头------------------------//		
    USART4_Init(230400);				//--------------------板间通信------------------------//	
		TIM7_Cnt_Init(1000-1,84-1); //------------control//记数定时器 1ms进一次中断 ---------//
		GUANGDIAN_GPIO_Init();
	
  while(1)
	{		
		usart_board_senddata();
//---------------回风通道--------------//
		if(USART_RX4_BUF[10]==0x99)
		{		
			clean_open();
		}
		if(USART_RX4_BUF[10]==0x88)
		{		
			clean_close();
		}
		if(USART_RX4_BUF[11]==0x77)
		{		
			Ultraviolet_down_on();
		}
		if(USART_RX4_BUF[11]==0x66)
		{		
			Ultraviolet_down_off();
		}			
//---------------回风通道--------------//

		
//		
		if(USART_RX4_BUF[7]==0x17)//放入
		{
				USART_RX4_BUF[7]=0;
				runActionGroup(7,1);
//				runActionGroup(5,1);					
//				runActionGroup(9,1);	//回零	
//				clothes_data=0x33;
//				usart_board_senddata();
//				Ultraviolet_up_on();
//				create_t_ctrl_param1(200000,50,50,240);
//				create_t_ctrl_param2(200000,50,50,240);
//				create_t_ctrl_param4(224000,50,50,240);
		}	
		
//				Ultraviolet_up_on();

		if(!GUANGDIAN1||!GUANGDIAN2||!GUANGDIAN3||!GUANGDIAN4)
		{
			delay_s(2);
			Ultraviolet_middle_on();
		}
		else
		{
			Ultraviolet_middle_off();
		}
	}
}
