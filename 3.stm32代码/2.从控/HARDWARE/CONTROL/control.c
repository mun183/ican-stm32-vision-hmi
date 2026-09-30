#include "control.h"
#include "encoder.h"
#include "pid.h"
#include "stdio.h"
#include "usart.h"
#include "led.h"
#include "motor.h"
#include "delay.h"
#include "math.h"
#include "mpu9250.h"
#include "oled.h"
#include "inv_mpu.h"
#include "key.h"
#include "sonic.h"
#include "filter.h"
#include "timer.h"
#include "adc.h"
#include "usartdma.h"
#include "usart4dma.h"
#include "usart2dma.h"
#include "usart3dma.h"
#include "usart5dma.h"
#include "photoelectric.h"
#include "duoji.h" 
#include "usartdma.h"
#include "dianji.h"
#define diam    65.0    //轮子直径，单位mm
#define PI 3.14159
#define Fd_angle 1.8/16    //上步进电机的分频角 
const char *str = "JG";
const char *stra = "flagT";


extern u16 distance;


uint16_t delay_TIM7=0;


extern uint16_t distance_left;
extern uint16_t distance_right;
extern uint8_t work_flag1;

extern	uint16_t command1;
extern	uint16_t command2;
extern	uint16_t command3;

//static uint8_t arm_right_left = 0;
//static uint8_t BJDJ1 = 0;
static uint8_t JXB = 0;
static uint8_t test = 0;

extern u8 Res;
extern uint8_t buf_board_final[9];
//*********************************小车走直线陀螺仪******************************************////

float	Limit_Pwm_float(float pwm,float pwm_min,float pwm_max)
{
	if(pwm > pwm_max)			 
    pwm =  pwm_max;
	if(pwm < pwm_min)	
    pwm =  pwm_min;
	return pwm;   
}


void TIM7_IRQHandler(void)       
{ 
	static unsigned int MS2=0,MS10=0,MS21=0,MS22=0,MS11=0,MS1=0,MS1000=0;    
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //
   {  
    MS1++;
	  MS2++;
	  MS10++;
		MS21++;
	  MS22++;
		MS11++;
		MS1000++;
		 
		 
//		if(USART_RX4_BUF[7]==0x17)//放入	
//		{
//			if(MS2>2&&test==0)
//			{
//				test=1;
//				runActionGroup(6,1);
//				MS2=2;
//			}
//			if(MS2>10000&&test==1)
//			{
//				test=2;
//				runActionGroup(9,1);
//				MS2=10000;
//			}
//			if(MS2>15000&&test==2)
//			{
//				test=0;
//				runActionGroup(7,1);
//				MS2=0;
//				USART_RX4_BUF[7]=0;
//			}
//		}

		if(USART_RX4_BUF[0]==0x10)
		{
//			USART_RX4_BUF[0]=0;
			if(MS2>2&&JXB==0)
			{
				JXB=1;//预备夹取
				runActionGroup(1,1);
				MS2=2;
			}
			if(MS2>4000&&JXB==1)
			{
				JXB=2;//步进电机下降
				create_t_ctrl_param1(-22400,50,50,240);//机械臂向下运动
				create_t_ctrl_param2(-22400,50,50,240);//机械臂向下运动
				MS2=4000;
			}
			if(MS2>9000&&JXB==2)
			{
				JXB=3;//夹取
				runActionGroup(2,1);
				MS2=9000;
			}
			if(MS2>12000&&JXB==3)
			{
				JXB=4;//步进电机上升
				create_t_ctrl_param1(22400,50,50,240);//机械臂向上
				create_t_ctrl_param2(22400,50,50,240);//机械臂向上
				MS2=12000;
			}
			if(MS2>16000&&JXB==4)
			{
				JXB=5;//步进电机向右运动
				create_t_ctrl_param4(224000,150,150,500);
				MS2=16000;
			}
			if(MS2>26000&&JXB==5)
			{
				JXB=6;//预备擦拭
				runActionGroup(3,1);		
				MS2=26000;
			}
			if(MS2>32000&&JXB==6)
			{
				JXB=7;//步进电机下降
				create_t_ctrl_param1(-22400,50,50,240);//机械臂向下运动
				create_t_ctrl_param2(-22400,50,50,240);//机械臂向下运动
				MS2=32000;
			}
			if(MS2>36000&&JXB==7)
			{
				JXB=8;//擦除
				runActionGroup(4,1);		
				MS2=36000;
			}
			if(MS2>44000&&JXB==8)
			{
				JXB=9;//放置纸巾
				runActionGroup(5,1);	
//				OLED_ShowNum(96,0,12,2,12);				
				MS2=44000;
			}
			if(MS2>47000&&JXB==9)
			{
				JXB=10;//预备夹取
				runActionGroup(6,1);		
				MS2=47000;
			}
			
			if(MS2>53000&&JXB==10)
			{
				JXB=11;//下降
				create_t_ctrl_param1(-5000,50,50,240);
				create_t_ctrl_param2(-5000,50,50,240);
				MS2=53000;
			}
			if(MS2>56000&&JXB==11)
			{
				JXB=12;
				runActionGroup(9,1);		
				MS2=56000;
			}
			if(MS2>58000&&JXB==12)
			{
				JXB=13;//步进电机上升
				create_t_ctrl_param1(22400,50,50,240);//机械臂向上
				create_t_ctrl_param2(22400,50,50,240);//机械臂向上		
				MS2=58000;
			}
			if(MS2>63000&&JXB==13)
			{
				JXB=14;
				//除尘与消毒
				//消毒
				Ultraviolet_up_on();
				//除尘
				clothes_data=0x33;
				usart_board_senddata();
				
				MS2=63000;
			}
			if(MS2>71000&&JXB==14)
			{
				JXB=15;//
				clothes_data=0x32;
				usart_board_senddata();
				
				Ultraviolet_up_off();		
				runActionGroup(7,1);	//放下	
				MS2=71000;
			}
			if(MS2>74000&&JXB==15)
			{
				JXB=16;
				runActionGroup(8,1);	//回零	
				MS2=74000;
			}
			if(MS2>76000&&JXB==16)
			{
				JXB=17;//步进电机向左
				create_t_ctrl_param4(-224000,50,50,240);
				MS2=76000;
			}
			if(MS2>93000&&JXB==17)
			{
				JXB=0;//步进电机向左
				clothes_data=0;
				create_t_ctrl_param1(5000,50,50,240);//机械臂向上
				create_t_ctrl_param2(5000,50,50,240);//机械臂向上				MS2=0;
				USART_RX4_BUF[0]=0;
				MS2=0;
			}
		}
		
		
		
		if(USART_RX4_BUF[1]==0x11)
		{
			USART_RX4_BUF[1]=0;

		}
		if(USART_RX4_BUF[2]==0x12)
		{
			USART_RX4_BUF[2]=0;

		}
		
		
		if(USART_RX4_BUF[5]==0x15)
		{
			USART_RX4_BUF[5]=0;
		}
		
		if(MS21>=2)
		{ 


		MS21=0;
		}	
//OLED调试屏        
		if(MS22>=20)
		{ 
//----------------------下摄像头---------------------//
//			
//				OLED_ShowHexNum(84,0,USART_RX1_BUF[0],2,12);
//				OLED_ShowHexNum(84,12,USART_RX1_BUF[1],2,12);
//												
//				OLED_ShowHexNum(84,24,USART_RX1_BUF[2],2,12);
//				OLED_ShowHexNum(84,36,USART_RX1_BUF[3],2,12);	
//												
//				OLED_ShowHexNum(96,0,USART_RX1_BUF[4],2,12);
//				OLED_ShowHexNum(96,12,USART_RX1_BUF[5],2,12);	
//												
//				OLED_ShowHexNum(96,24,USART_RX1_BUF[6],2,12);
//				OLED_ShowHexNum(96,36,USART_RX1_BUF[7],2,12);	
//												
//				OLED_ShowHexNum(108,0,USART_RX1_BUF[8],2,12);
//				OLED_ShowHexNum(108,12,USART_RX1_BUF[9],2,12);				
//												
//				OLED_ShowHexNum(108,24,USART_RX1_BUF[10],2,12);
//				OLED_ShowHexNum(108,36,USART_RX1_BUF[11],2,12);
//----------------------下摄像头---------------------//



//---------------------板件通信------------------------//
//				OLED_ShowNum(72,0,USART_RX4_BUF[0],2,12);
//				OLED_ShowNum(72,12,USART_RX4_BUF[1],2,12);
//				OLED_ShowNum(72,24,USART_RX4_BUF[2],2,12);
				
//--------------------板件通信串口屏幕------------------//
				OLED_ShowHexNum(0,0,USART_RX4_BUF[0],2,12);
				OLED_ShowHexNum(0,12,USART_RX4_BUF[1],2,12);
												
				OLED_ShowHexNum(0,24,USART_RX4_BUF[2],2,12);
				OLED_ShowHexNum(0,36,USART_RX4_BUF[3],2,12);	
												
				OLED_ShowHexNum(24,0,USART_RX4_BUF[4],2,12);
				OLED_ShowHexNum(24,12,USART_RX4_BUF[5],2,12);	
			
				OLED_ShowHexNum(24,24,USART_RX4_BUF[6],2,12);
				OLED_ShowHexNum(24,36,USART_RX4_BUF[7],2,12);	
												
				OLED_ShowHexNum(48,0,USART_RX4_BUF[8],2,12);
				OLED_ShowHexNum(48,12,USART_RX4_BUF[9],2,12);				
												
				OLED_ShowHexNum(48,24,USART_RX4_BUF[10],2,12);
				OLED_ShowHexNum(48,36,USART_RX4_BUF[11],2,12);


//----------------------上摄像头---------------------//
			
//				OLED_ShowHexNum(72,0,USART_RX2_BUF[0],2,12);
//				OLED_ShowHexNum(72,12,USART_RX2_BUF[1],2,12);											
//				OLED_ShowHexNum(72,24,USART_RX2_BUF[2],2,12);
//				OLED_ShowHexNum(72,36,USART_RX2_BUF[3],2,12);	
					OLED_ShowNum(72,0,GUANGDIAN1,2,12);	
					OLED_ShowNum(72,12,GUANGDIAN2,2,12);								
					OLED_ShowNum(72,24,GUANGDIAN3,2,12);								
					OLED_ShowNum(72,36,GUANGDIAN4,2,12);								
					
//----------------------上摄像头---------------------//

				OLED_Refresh_Gram();			
				MS22=0;
		}	 	 
if(MS11>=20)
{	
  Ultrasonic_Trig_Start();	
  Sonic_Get_Distance();	
	MS11=0;
}
if(MS1000>=1000)
{
	LED1=!LED1;
	MS1000=0;
}


	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);        
}
		

delay_TIM7++;
}

