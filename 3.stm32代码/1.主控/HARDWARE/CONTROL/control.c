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
#include "usart5dma.h"
#include "photoelectric.h"
#include "duoji.h" 
#include "usartdma.h"
#include "dianji.h"
#include "shoe.h"

#define diam    65.0    //轮子直径，单位mm
#define PI 3.14159
#define Fd_angle 1.8/16    //上步进电机的分频角 
const char *str = "JG";
const char *stra = "flagT";

int speed_bais=0;
int flag_steer=10;
float speed_yaw=0;
uint16_t speed_init;
float speed_sonic=0;
int steer_sonic;
int car_state=0;//车子目前的状态，和使用了那几个环有关
float yaw_C=2.00;
extern float yaw_2;
extern float yaw_init;
extern u16 GM_REC[9];
float enc_speed_1=0,enc_speed_2=0,enc_speed_3=0,enc_speed_4=0;//表示轮子当前转速，单位cm/s
extern int HIM_4[9];
extern u16 distance;
u16 clean_shoe_1=0;
u16 xd_shoe_1=0;

uint16_t delay_TIM7=0;


extern uint16_t distance_left;
extern uint16_t distance_right;

extern	uint16_t command1;
extern	uint16_t command2;
extern	uint16_t command3;

static uint8_t BJDJ = 0;//存放
static uint8_t QUCHU = 0;
static uint8_t XIAODU = 0;//消毒
static uint8_t QINGJIE = 0;//清洁
static uint8_t AUTO = 0;//自动模式（回家）
//static uint8_t AUTO_OUT = 0;//自动模式（出门）0x24
u16 HFTD = 0;//回风通道

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

int	Limit_Pwm_moter(int pwm,int min_range,int max_range)
{
	if(pwm > 7000)			 
    pwm =  7000;
	if(pwm > speed_bais+max_range)			 
    pwm =  speed_bais+max_range;	
	if(pwm < 0)	
    pwm =  0;
	if(pwm < speed_bais-min_range)	
    pwm =  speed_bais-min_range;	
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
////------------------------鞋子自动清理流程(出门)-----------------------------//
//	 	if(USART_RX1_BUF[23]==0x24)
//		{
//			
//		}


//------------------------鞋子自动清理流程(回家)-----------------------------//
		if(USART_RX1_BUF[7]==0x08)
		{
				if(MS2>0&&AUTO==0)
				{
								AUTO=1;
								create_t_ctrl_param4(2400,30,30,80);//鞋架转动90
								create_t_ctrl_param1(-32000,50,50,240);//上下机构   负数上升32000/3200   10圈
								OLED_ShowNum(36,0,1,2,12);
								MS2=2;
				}
				if(MS2>=6000&&AUTO==1)
				{
								AUTO=2;
								create_t_ctrl_param3(90000,100,100,1200);//伸出机构   正数伸出90000/3200   
								MS2=6000;
				}	
				if(MS2>=13000&&AUTO==2)
				{
								AUTO=3;
								create_t_ctrl_param1(32000,50,50,240); //上下机构   正数下降32000/3200   10圈
								MS2=13000;
				}
				if(MS2>=23000&&AUTO==3)
				{
								AUTO=4;
								create_t_ctrl_param1(-90000,50,50,240);//上下机构   负数上升32000/3200   10圈
								MS2=23000;
				}
				if(MS2>=34000&&AUTO==4)
				{
								AUTO=5;
								create_t_ctrl_param3(-88000,100,100,1200);//伸出机构   负数伸进去90000/3200
								MS2=34000;
				}	
				if(MS2>=45000&&AUTO==5)
				{
								AUTO=6;
								create_t_ctrl_param1(90000,50,50,240); //上下机构   正数下降90000/3200   
								MS2=45000;
				}
				if(MS2>=55000&&AUTO==6)
				{
								AUTO=7;
								create_t_ctrl_param4(-2400,30,30,80);//鞋架转动		
								MS2=55000;
				}
				if(MS2>58000&&AUTO==7)
				{	
					AUTO=8;
					create_t_ctrl_param4(-2400,30,30,80);//鞋架转动		
					MS2=58000;
				}
				if(MS2>68000&&AUTO==8)
				{	
					AUTO=9;
					create_t_ctrl_param4(-2400,30,30,80);//鞋架转动		
					MS2=68000;
				}	
				if(MS2>78000&&AUTO==9)
				{	
					AUTO=0;
					create_t_ctrl_param4(4800,30,30,80);//鞋架转动		
					MS2=0;
					USART_RX1_BUF[7]=0;
				}				
		}
//------------------------回家之后换鞋子（存放）----------------------//
		if(USART_RX1_BUF[3]==0x04)
		{
				if(MS2>0&&BJDJ==0)
				{
								BJDJ=1;
								create_t_ctrl_param4(2400,50,50,120);//鞋架转动90
								create_t_ctrl_param1(-32000,100,100,200);//上下机构   负数上升32000/3200   10圈
								OLED_ShowNum(36,0,1,2,12);
								MS2=2;
				}
				if(MS2>=4500&&BJDJ==1)
				{
								BJDJ=2;
								create_t_ctrl_param3(90000,100,100,1200);//伸出机构   正数伸出90000/3200   
								OLED_ShowNum(36,12,2,2,12);
								MS2=4500;
				}	
				if(MS2>=11500&&BJDJ==2)
				{
								BJDJ=3;
								create_t_ctrl_param1(32000,100,100,500); //上下机构   正数下降32000/3200   10圈
								OLED_ShowNum(36,24,3,2,12);
								MS2=11500;
				}
				if(MS2>=16500&&BJDJ==3)
				{
								BJDJ=4;
								create_t_ctrl_param1(-90000,100,100,1000);//上下机构   负数上升32000/3200   10圈
								OLED_ShowNum(72,0,1,2,12);
								MS2=16500;
				}
				if(MS2>=23500&&BJDJ==4)
				{
								BJDJ=5;
								create_t_ctrl_param3(-88000,100,100,1200);//伸出机构   负数伸进去90000/3200
								OLED_ShowNum(72,12,2,2,12);
								MS2=23500;
				}	
				if(MS2>=31000&&BJDJ==5)
				{
								BJDJ=6;
								create_t_ctrl_param1(90000,100,100,1000); //上下机构   正数下降90000/3200   
								OLED_ShowNum(72,24,3,2,12);
								MS2=31000;
				}
				if(MS2>=37000&&BJDJ==6)
				{
								USART_RX1_BUF[3]=0;
								BJDJ=0;
								create_t_ctrl_param4(-2400,50,50,100);//鞋架转动		
								MS2=0;
				}
		}
//--------------------消毒---------------------------//		
//--------------------消毒---------------------------//		
//--------------------消毒---------------------------//		
		if(USART_RX1_BUF[5]==0x06||USART_RX2_BUF[4]==0x05)//******改
		{
			if(MS2>2&&XIAODU==0)
			{	
				HFTD=1;
				XIAODU=1;
				create_t_ctrl_param4(-2400,30,30,80);//鞋架转动	
				xd_shoe_1=0x77;		
				huifengtongdao_open();
				if(xd_shoe_1==0x77)
				{
					usart5_CKPM();
					xd_shoe_1=0x66;
				}					
				MS2=2;
			}
			if(MS2>10000&&XIAODU==1)
			{	
				XIAODU=2;
				MS2=10000;
				create_t_ctrl_param4(2400,30,30,80);//鞋架转动	
			
			}
			if(MS2>11000&&XIAODU==2)
			{	
				HFTD=0;
				XIAODU=0;
				MS2=0;
				huifengtongdao_close();
				if(xd_shoe_1==0x66)
				{
					usart5_CKPM();
					xd_shoe_1=0;
				}
				USART_RX1_BUF[5]=0;
				USART_RX2_BUF[4]=0;
			}
		}
//--------------------消毒---------------------------//		
//////////////////////////////////////////////////////		
		
		
//--------------------清洁---------------------------//		
//--------------------清洁---------------------------//		
		if(USART_RX1_BUF[4]==0x05)
		{
			if(MS2>2&&QINGJIE==0)
			{	
				QINGJIE=1;
				clean_shoe_1=0x99;
				create_t_ctrl_param2(6400,30,30,80);//上升		
				create_t_ctrl_param4(-4800,30,30,80);//鞋架转动	
				MS2=2;
			}
			if(MS2>5000&&QINGJIE==1)
			{
				QINGJIE=2;
				
				create_t_ctrl_param2(-6300,30,30,80);//下降
				Clean_down();
				if(clean_shoe_1==0x99)
				{
					usart5_CKPM();
					clean_shoe_1=0x88;
				}
				MS2=5000;
			}
			if(MS2>12000&&QINGJIE==2)
			{
				QINGJIE=3;
				Clean_middle();
				if(clean_shoe_1==0x88)
				{
					usart5_CKPM();
					clean_shoe_1=0;
				}
				create_t_ctrl_param2(6400,30,30,80);//上升	
				create_t_ctrl_param4(4800,30,30,80);//鞋架转动					
				MS2=12000;
			}
			if(MS2>18000&&QINGJIE==3)
			{
				QINGJIE=0;
				create_t_ctrl_param2(-6400,30,30,80);//下降	
				OLED_ShowNum(0,36,12,2,12);
				USART_RX1_BUF[4]=0;
				MS2=0;
			}
		}
	
//--------------------清洁---------------------------//		
//--------------------清洁---------------------------//		

		
		
//---------------------取出/出门---------------------------//			
		if(USART_RX1_BUF[6]==0x07||USART_RX1_BUF[23]==0x24)
		{
			if(MS2>2&&QUCHU==0)
			{	
				QUCHU=1;
				create_t_ctrl_param4(2400,30,30,80);//鞋架转动		
				MS2=2;
			}
			if(MS2>3000&&QUCHU==1)
			{	
				QUCHU=2;
				create_t_ctrl_param1(-90000,50,50,240);//上下机构   负数上升32000/3200   10圈
				MS2=3000;
			}
			if(MS2>13000&&QUCHU==2)
			{	
				QUCHU=3;
				create_t_ctrl_param3(90000,100,100,1200);//伸出机构   正数伸出90000/3200   
				MS2=13000;
			}
			if(MS2>20000&&QUCHU==3)
			{	
				QUCHU=4;
				create_t_ctrl_param1(90000,50,50,240); //上下机构   正数下降32000/3200   10圈
				MS2=20000;
			}
			
			
			if(MS2>35000&&QUCHU==4)
			{	
				QUCHU=5;
				create_t_ctrl_param1(-32000,30,30,120); //上下机构   负数上升32000/3200   10圈
				MS2=35000;
			}
			
			
			if(MS2>42000&&QUCHU==5)
			{	
				QUCHU=6;
				create_t_ctrl_param3(-88000,100,100,1200);//伸出机构   负数伸进90000/3200   
				MS2=42000;
			}
			
			if(MS2>49000&&QUCHU==6)
			{	
				QUCHU=7;
				create_t_ctrl_param1(32000,50,50,240); //上下机构  +down  32000/3200   10圈
				MS2=49000;
			}
			
			if(MS2>53000&&QUCHU==7)
			{	
				QUCHU=0;
				create_t_ctrl_param4(-2400,30,30,80);//鞋架转动		
				MS2=0;
				USART_RX1_BUF[6]=0;
			}
		}
//---------------------取出---------------------------//	
		
		
		if(MS21>=2)
		{ 


		MS21=0;
		}	
//OLED调试屏        
		if(MS22>=20)
		{ 				
//------------------激光测距模块---------------------//			
//				OLED_ShowString(0,0,(const u8*)str,12);
					OLED_ShowNum(0,12,distance,4,12);
//					OLED_ShowHexNum(0,24,USART_RX1_BUF[0],2,12);
//				OLED_ShowNum(0,24,distance_left,4,12);
//				OLED_ShowNum(0,36,distance_right,4,12);

//-------------主控板向从控板发送的数据---------------------//			
//				OLED_ShowString(0,0,(const u8*)str,12);
//				OLED_ShowNum(24,12,command1,4,12);
//				OLED_ShowNum(24,24,command2,4,12);
//				OLED_ShowNum(24,36,command3,4,12);			

//-------------主控板接受的串口屏的数据--------------------//
//				OLED_ShowHexNum(12,12,USART_RX1_BUF[0],4,12);
//				OLED_ShowHexNum(12,24,USART_RX1_BUF[1],4,12);
//				OLED_ShowHexNum(12,36,USART_RX1_BUF[2],4,12);	

//----------------------语音模块测试---------------------//
//				OLED_ShowHexNum(100,12,USART_RX2_BUF[0],2,12);
//				OLED_ShowHexNum(100,24,USART_RX2_BUF[1],2,12);
//				OLED_ShowHexNum(100,36,USART_RX2_BUF[2],2,12);
//				OLED_ShowHexNum(100,48,USART_RX2_BUF[3],2,12);

//				OLED_ShowHexNum(72,48,USART_RX2_BUF[3],4,12);
//				OLED_ShowHexNum(72,60,USART_RX2_BUF[4],4,12);

//----------------------视觉模块测试---------------------//
			//------------------男士拖鞋------------------//
//				OLED_ShowHexNum(36,12,USART_RX5_BUF[0],2,12);
//				OLED_ShowHexNum(36,24,USART_RX5_BUF[1],2,12);
//			//------------------男士皮鞋------------------//
//				OLED_ShowHexNum(36,36,USART_RX5_BUF[2],2,12);
//				OLED_ShowHexNum(36,48,USART_RX5_BUF[3],2,12);
				
//			//------------------女士拖鞋------------------//
//				OLED_ShowHexNum(55,12,USART_RX5_BUF[4],2,12);
//				OLED_ShowHexNum(55,24,USART_RX5_BUF[5],2,12);
//			//------------------女士鞋------------------//
//				OLED_ShowHexNum(55,36,USART_RX5_BUF[6],2,12);
//				OLED_ShowHexNum(55,48,USART_RX5_BUF[7],2,12);
//				
			//------------------儿童拖鞋------------------//
//				OLED_ShowHexNum(72,12,USART_RX5_BUF[8],2,12);
//				OLED_ShowHexNum(72,24,USART_RX5_BUF[9],2,12);
//			//------------------儿童鞋------------------//
//				OLED_ShowHexNum(72,36,USART_RX5_BUF[10],2,12);
//				OLED_ShowHexNum(72,48,USART_RX5_BUF[11],2,12);

//----------------------视觉模块测试---------------------//
					 
//----------------------串口屏幕测试---------------------//
				OLED_ShowHexNum(30,12,USART_RX1_BUF[0],2,12);
				OLED_ShowHexNum(30,24,USART_RX1_BUF[1],2,12);
				OLED_ShowHexNum(30,36,USART_RX1_BUF[2],2,12);
				OLED_ShowHexNum(30,48,USART_RX1_BUF[3],2,12);
				OLED_ShowHexNum(50,12,USART_RX1_BUF[4],2,12);
				OLED_ShowHexNum(50,24,USART_RX1_BUF[5],2,12);
				OLED_ShowHexNum(50,36,USART_RX1_BUF[6],2,12);
				OLED_ShowHexNum(50,48,USART_RX1_BUF[7],2,12);
				OLED_ShowHexNum(70,12,USART_RX1_BUF[8],2,12);
				OLED_ShowHexNum(70,24,USART_RX1_BUF[9],2,12);
				OLED_ShowHexNum(70,36,USART_RX1_BUF[10],2,12);
				OLED_ShowHexNum(70,48,USART_RX1_BUF[11],2,12);	
				
				OLED_ShowHexNum(90,12,clean_shoe_1,2,12);
				OLED_ShowHexNum(90,36,USART_RX5_BUF[12],2,12);

//				OLED_ShowHexNum(90,24,USART_RX1_BUF[13],2,12);
//				OLED_ShowHexNum(90,36,USART_RX1_BUF[14],2,12);
//				OLED_ShowHexNum(90,48,USART_RX1_BUF[15],2,12);
//				OLED_ShowHexNum(110,12,USART_RX1_BUF[16],2,12);
//				OLED_ShowHexNum(110,24,USART_RX1_BUF[17],2,12);
//				OLED_ShowHexNum(110,36,USART_RX1_BUF[18],2,12);
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

