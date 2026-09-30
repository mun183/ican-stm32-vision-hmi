#ifndef __PID_H
#define __PID_H

#include "sys.h"


typedef struct
{
	float P;
	float pout;
	float I;
	float iout;
	float D;
	float dout;
	float integral;		   //积分项
	float err;       	   //偏差值
	float last_err;  	   //上次偏差值
	float Expected;  	   //期望值
	float PMAX;			   //P输出限幅值
	float IMAX;			   //I输出限幅值
	float DMAX;			   //D输出限幅值
	float PIDOUT;    	   //输出值
} PIDStru;
extern PIDStru left_home_yaw;
extern PIDStru left_home_sonic;
typedef struct
{
	float Angle;
	int   Distance;
	
} Expect;


void PID_Init(PIDStru *PID,float P,float I,float D);
float Limit_Pwm_float(float pwm,float pwm_min,float pwm_max);
int Control_left_home_yaw(float Expected,float observe_value);
int pid_lefthome_yaw(PIDStru *PID,float Expected,float observe_value);
int pid_lefthome_sonic(PIDStru *PID,float Expected,float observe_value);
int Control_left_home_sonic(float Expected,float observe_value);
#endif
/***************速度环*////////////////////////
//			 OLED_ShowString( 0,0,(void*)"ENA",12);	
//			 OLED_ShowNum(40,0,Encoder_Fabs_L1,6,12);	 
//			 Encoder_Fabs();
//			 TIM2->CNT=30000;
//       TIM3->CNT=30000;	 
//			 TIM4->CNT=30000;	
//			 TIM8->CNT=30000;	
//		 // Read_LaserDis(0x00, Temp_Data);
//			 speed=PID_Control4(&PID_velocity,203,Encoder_Fabs_L1);
//			 OLED_Show3FNum(40,40,speed,3,3,12);
//			 OLED_Refresh_Gram();//更新显示到OLED	 
//			       if(speed>3500)speed=3500;//限幅
//			       if(speed<-3500)speed=-3500;//限幅
//			 setspeed=3000;
//			
//		 
//			 MotorA_Ctrl(setspeed);
