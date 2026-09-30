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
u8 receive_count = 0;    // 新增定义

int main(void)
{ 
	//所有的刹车后自带400ms的延时，转动舵机后自带800ms的延时
	//刹车状态分别是4、18、21、23	
	//sonic1 43 sonic2 45 sonic3 61 sonic4 56	sonic5 111 sonic6 111	
	//TIM1、8--11是168M，2——7,12——14是84M
	 	SystemInit();//系统时钟等初始化
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
		delay_init(168);//初始化延时函数
		KEY_Init();     //按键初始化
		LED_Init();	    //LED初始化
		OLED_Init();    //OLED初始化
		stepper_init(0XFFFF, 84-1);
		USART3_Init(9600);//--------------------普通串口舵机------------------------//
		USART1_Init(9600);//--------------------串口屏幕------------------------//	
		USART2_Init(9600);//--------------------语音模块------------------------//	
    USART4_Init(230400);//--------------------激光测距------------------------//
		USART5_Init(230400);//--------------------板间通信------------------------//
		TIM7_Cnt_Init(1000-1,84-1);//------------记数定时器 1ms进一次中断-----------control--//

	
  while(1)
	{		
		//	create_t_ctrl_param1(10000,100,100,1200);//伸出机构   负数伸进去90000/3200

//---------------发送串口屏幕数据给从控板--------------//	
			if(USART_RX1_BUF[9]==0x10)//自动模式
			{
				usart5_CKPM();
				USART_RX1_BUF[9]=0;
			}
			if(USART_RX1_BUF[10]==0x11)//二级除尘
			{
				usart5_CKPM();
				USART_RX1_BUF[10]=0;
			}
			if(USART_RX1_BUF[11]==0x12)//清洗
			{
				usart5_CKPM();
				USART_RX1_BUF[11]=0;
			}
			if(USART_RX1_BUF[12]==0x13)//消毒
			{
				usart5_CKPM();
				USART_RX1_BUF[12]=0;
			}
			if(USART_RX1_BUF[13]==0x14)//一级除尘
			{
				usart5_CKPM();
				USART_RX1_BUF[13]=0;
			}
			if(USART_RX1_BUF[14]==0x15)//机械臂强制暂停
			{
				usart5_CKPM();
				USART_RX1_BUF[14]=0;
			}
			if(USART_RX1_BUF[15]==0x16)//功能暂停
			{
				usart5_CKPM();
				USART_RX1_BUF[15]=0;
			}
			if(USART_RX1_BUF[16]==0x17)//手机消毒
			{
				usart5_CKPM();
				USART_RX1_BUF[16]=0;
			}
			if(USART_RX1_BUF[21]==0x22)//自动运行
			{
				usart5_CKPM();
				USART_RX1_BUF[21]=0;
			}
			if(USART_RX1_BUF[22]==0x23)//手动运行
			{
				usart5_CKPM();
				USART_RX1_BUF[22]=0;
			}
//---------------发送串口屏幕数据给从控板--------------//


//--------风机开关(一个IO口对应两个风机)---//
			if(USART_RX5_BUF[12]==0x33)
			{
					fan1_open();
					fan2_open();
			}
			if(USART_RX5_BUF[12]==0x32)
			{
					fan1_close();
					fan2_close();
			}
//			fan1_open();
//			fan2_open();
//			huifengtongdao_open();
		}			        
}

