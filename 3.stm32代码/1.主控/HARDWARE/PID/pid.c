
#include "pid.h"
#include "motor.h"


Expect  Expectation;//期望结构体PIDStru PID_velocity;//进场结构体
PIDStru left_home_yaw;
PIDStru left_home_sonic;
float speedA, speedB, speedC, speedD;

//float Limit_Pwm_float(float pwm,float pwm_min,float pwm_max)
//{
//	if(pwm > pwm_max)			 
//    pwm =  pwm_max;
//	if(pwm < pwm_min)	
//    pwm =  pwm_min;
//	return pwm;   //返回
//}

int PID_Control4(PIDStru *PID,float Expected,float observe_value)
{
	PID->Expected = Expected;
	PID->err      = observe_value - PID->Expected;
	PID->pout     = PID->P * PID->err;
	PID->integral = 0.8f*PID->integral;//一阶低通滤波
	PID->integral+= PID->err;
	PID->integral = Limit_Pwm_float(PID->integral,-80,80);//积分项限幅(防止退饱和慢)
	PID->iout     = PID->I * PID->integral;
	PID->iout     = Limit_Pwm_float(PID->iout,-300,300);   //限幅(防止退饱和慢)
	PID->dout	    = PID->D * (PID->err - PID->last_err);
	PID->last_err = PID->err;
	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
	PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-500,500);
	return (int)PID->PIDOUT;
}

int PID_Control5(PIDStru *PID,float Expected,float observe_value)
{
PID->Expected = Expected;
	PID->err      = observe_value - PID->Expected;
	PID->pout     = PID->P * PID->err;
	PID->integral+= PID->err;
	PID->integral = Limit_Pwm_float(PID->integral,-PID->IMAX,PID->IMAX);//积分项限幅(防止退饱和慢)
	PID->iout     = PID->I * PID->integral;
	PID->dout	    = PID->D * (PID->err - PID->last_err);
	PID->last_err = PID->err;
	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
  PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-120,120);
	return (int)PID->PIDOUT;
}




//**************************************编码器速度环***********************************************//
//1.增量式pid

    //int      SetPoint;                                 //设定目标 Desired Value

//定义PID相关宏
// 这三个参数设定对电机运行影响非常大
/*************************************/
//#define  P_DATA      0.6                             //P参数
//#define  I_DATA      0.1                              //I参数
//#define  D_DATA      0                            //D参数
//	static double   Proportion_L=8;                               //比例常数 Proportional Const
//	static double   Integral_L=0.2;                                 //积分常数 Integral Const
//	static double   Derivative_L=0;  

/********************增量式PID控制设计************************************/
//NextPoint当前输出值
//SetPoint设定值
//当前速度单位为rad/s  定时50ms
//3.14159*encoder/156 rad/s


//*************************************************************循迹位置环*********************************************************************//

//**************************************************************编码器增量式pid*****************************************************************//

		
#define Motor_MAX 7200

#define Motor_MAX_Distance 4000





#define Distance_Kp2 2
#define Distance_Ki2 0
#define Distance_Kd2 0


//**************************************************************编码器增量式pid*****************************************************************//

//**************************************************************陀螺仪pid*****************************************************************//






/******************************************************************************************************************
*                              void PID_Init(PIDStru *PID,float P,float I,float D)
*
*Author      : Jianfeng Zhang 
*Description : PID初始化函数
*Arguments   : PIDStru *PID            所要初始化的PID结构体的指针
               float P          	   比例系数
			   float I     			   积分系数
			   float D				   微分系数
*Returns     : none                  
*Notes       : Lab416 for 2019国赛
*******************************************************************************************************************
*/	
void PID_Init(PIDStru *PID,float P,float I,float D)
{
	PID->P 			= P;
	PID->I 			= I;
	PID->D 			= D;
	PID->integral  = 0.0f;
	PID->pout 		= 0.0f;
	PID->iout 		= 0.0f;
	PID->dout 		= 0.0f;
	PID->IMAX   	= 1000.0f;
	PID->PMAX   	= 10000.0f;
	PID->DMAX   	= 10000.0f;
	PID->Expected 	= 0.0f;
	PID->err		= 0.0f;
	PID->last_err	= 0.0f;
}


int pid_lefthome_yaw(PIDStru *PID,float Expected,float observe_value)
{
	PID->Expected = Expected;
	PID->err      = observe_value - PID->Expected;
	PID->pout     = PID->P * PID->err;
	PID->integral = PID->integral;//一阶低通滤波
	PID->integral+= PID->err*0.2f;
	PID->integral = Limit_Pwm_float(PID->integral,-100,100);//积分项限幅(防止退饱和慢)
	PID->iout     = PID->I * PID->integral;
	PID->iout     = Limit_Pwm_float(PID->iout,-400,400);   //限幅(防止退饱和慢)
	PID->dout	    = PID->D * (PID->err - PID->last_err);
	PID->last_err = PID->err;
	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
  PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-220,220);
	return (int)PID->PIDOUT;
}

int pid_lefthome_sonic(PIDStru *PID,float Expected,float observe_value)
{
	PID->Expected = Expected;
	PID->err      = observe_value - PID->Expected;
	PID->pout     = PID->P * PID->err;
	PID->integral = PID->integral;//一阶低通滤波
	PID->integral+= PID->err*0.2f;
	PID->integral = Limit_Pwm_float(PID->integral,-100,100);//积分项限幅(防止退饱和慢)
	PID->iout     = PID->I * PID->integral;
	PID->iout     = Limit_Pwm_float(PID->iout,-400,400);   //限幅(防止退饱和慢)
	PID->dout	    = PID->D * (PID->err - PID->last_err);
	PID->last_err = PID->err;
	PID->PIDOUT   = PID->pout + PID->iout + PID->dout;
  PID->PIDOUT   = Limit_Pwm_float(PID->PIDOUT,-220,220);
	return (int)PID->PIDOUT;
}
int Control_left_home_yaw(float Expected,float observe_value)
{
return 	pid_lefthome_yaw(&left_home_yaw,Expected,observe_value);

}

int Control_left_home_sonic(float Expected,float observe_value)
{
return 	pid_lefthome_sonic(&left_home_sonic,Expected,observe_value);

}
