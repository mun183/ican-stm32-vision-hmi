

/*
********************************************************************************************************************
*Filename        :Ultrasonic.c
*Programmer(s)   :Lab 416
*Description     :2017????:UltrasonicWave??

									TRIG--PB10
									ECHO--PB11
							
	TIM5_Sonic_Cap_Init(0XFFFFFFFF,84-1);
	TIM2_Sonic_Cap_Init(0XFFFFFFFF,84-1);		
********************************************************************************************************************
*/

/*
F T5C3
B T2C4
R1 T5C4
R2 T2C3
L1 T5C2
L2 T5C1
*/
#include "sonic.h"
#include "delay.h"
#include "filter.h"
#include "oled.h"
#include "math.h"
#include "usartdma.h"

/*
******************************************************************************************************************
*                                            CONSTANTS & MACROS
******************************************************************************************************************
*/


u8     TIM5CH1_CAPTURE_STA=0;	//??????		    				
u32	 TIM5CH1_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)
u8     TIM5CH2_CAPTURE_STA=0;	//??????		    				
u32	 TIM5CH2_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)
u8     TIM5CH3_CAPTURE_STA=0;	//??????		    				
u32	 TIM5CH3_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)
u8     TIM5CH4_CAPTURE_STA=0;	//??????		    				
u32	 TIM5CH4_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)

u8     TIM3CH3_CAPTURE_STA=0;	//??????		    				
u32	 TIM3CH3_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)
u8     TIM3CH4_CAPTURE_STA=0;	//??????		    				
u32	 TIM3CH4_CAPTURE_VAL=0;	//?????(TIM2/TIM5?32?)




long long temp1=0;//?
long long temp2=0;//?
long long temp3=0;
long long temp4=0;
long long temp5=0;
long long temp6=0;

int TEMPA_1=0;
int TEMPA_2=0;
int TEMPA_3=0;
int TEMPA_4=0;
int TEMPA_5=0;
int TEMPA_6=0;
int last_c1=0;
int last_c2=0;
int last_c3=0;
int last_c4=0;
int last_c5=0;
int last_c6=0;
SonicDis Sonic_Dis_init={0,0,0,0,0,0};
SonicDis Sonic_Dis={0,0,0,0,0,0};

Filter_Struct SonicA1_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA2_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA3_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA4_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA5_Filter = {0,0,0,0,{0}};
Filter_Struct SonicA6_Filter = {0,0,0,0,{0}};

void Ultra_Init(void)
{
  GPIO_InitTypeDef    GPIO_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);//
	 /***********************GPIO initial****************************************/
		 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_10|GPIO_Pin_11;//TRIG1、2、3、4、5、6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz        
  GPIO_Init(GPIOE, &GPIO_InitStructure);//GPIOE
	
  GPIO_ResetBits(GPIOE,GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_10|GPIO_Pin_11);//TRIG=0
	
	
//	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);//
//	 /***********************GPIO initial****************************************/
//		 
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;//TRIG1、2、3、4、5、6
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//
//  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz        
//  GPIO_Init(GPIOD, &GPIO_InitStructure);
//	
//  GPIO_ResetBits(GPIOD,GPIO_Pin_14|GPIO_Pin_15);//TRIG=0
	
}

/***************************************************************************************
F  T5C3   5??
B  T2C4   1
R2 T2C3   3
L2 T5C1   2
R1 T5C4   4
L1 T5C2
***************************************************************************************/
int flag_sonic;
void Sonic_Get_Distance()
{	
	if(flag_sonic==1)
	{flag_sonic=0;
last_c1=110;
 last_c2=110;
 last_c3=110;
 last_c4=110;
 last_c5=110;
 last_c6=110;	
	}
 else{last_c1=Sonic_Dis.A_1;
 last_c2=Sonic_Dis.A_2;
 last_c3=Sonic_Dis.A_3;
 last_c4=Sonic_Dis.A_4;
 last_c5=Sonic_Dis.A_5;
 last_c6=Sonic_Dis.A_6;}
if(TIM5CH1_CAPTURE_STA&0X80){
		temp1=TIM5CH1_CAPTURE_STA&0X3F*65535; 
//		tempB*=0XFFFFFFFF;         //??????
		temp1+=TIM5CH1_CAPTURE_VAL;//?????????
		TIM5CH1_CAPTURE_STA=0;     //???????
	}
	TEMPA_1=(temp1*340/200)/10*0.3+TEMPA_1*0.7; //??????cm
	Enaverage_Filter(&SonicA1_Filter,TEMPA_1,15, &Sonic_Dis.A_1);

	
	if(TIM5CH2_CAPTURE_STA&0X80){
		temp2=TIM5CH2_CAPTURE_STA&0X3F*65535;
//		tempF*=0XFFFFFFFF;         //??????
		temp2+=TIM5CH2_CAPTURE_VAL;//?????????
		TIM5CH2_CAPTURE_STA=0;     //???????
	}
	TEMPA_2=(temp2*340/200)/10*0.3+TEMPA_2*0.7; //??????mm
	Enaverage_Filter(&SonicA2_Filter,TEMPA_2,15, &Sonic_Dis.A_2);

	
	if(TIM5CH3_CAPTURE_STA&0X80){
		temp3=TIM5CH3_CAPTURE_STA&0X3F*65535; 
		temp3+=TIM5CH3_CAPTURE_VAL;//?????????
		TIM5CH3_CAPTURE_STA=0;     //???????
	}
	TEMPA_3=(temp3*340/200)/10*0.3+TEMPA_3*0.7; //??????mm
	Enaverage_Filter(&SonicA3_Filter,TEMPA_3,15, &Sonic_Dis.A_3);

	
	if(TIM5CH4_CAPTURE_STA&0X80){
		temp4=TIM5CH4_CAPTURE_STA&0X3F*65535; 
		temp4+=TIM5CH4_CAPTURE_VAL;//?????????
		TIM5CH4_CAPTURE_STA=0;     //???????
	}
	TEMPA_4=(temp4*340/200)/10*0.3+TEMPA_4*0.7; //??????mm
	Enaverage_Filter(&SonicA4_Filter,TEMPA_4,15, &Sonic_Dis.A_4);
	
	
	if(TIM3CH3_CAPTURE_STA&0X80){
		temp5=TIM3CH3_CAPTURE_STA&0X3F*65535; 
		temp5+=TIM3CH3_CAPTURE_VAL;//?????????
		TIM3CH3_CAPTURE_STA=0;     //???????
	}
	TEMPA_5=(temp5*340/200)/10*0.3+TEMPA_5*0.7; //??????mm
	Enaverage_Filter(&SonicA5_Filter,TEMPA_5,15, &Sonic_Dis.A_5);
	if(TIM3CH4_CAPTURE_STA&0X80){
		temp6=TIM3CH4_CAPTURE_STA&0X3F*65535; 
		temp6+=TIM3CH4_CAPTURE_VAL;//?????????
		TIM3CH4_CAPTURE_STA=0;     //???????
	}
	TEMPA_6=(temp6*340/200)/10*0.3+TEMPA_6*0.7; //??????mm
	Enaverage_Filter(&SonicA6_Filter,TEMPA_6,15, &Sonic_Dis.A_6);
	
		if(Sonic_Dis.A_1>250)
			Sonic_Dis.A_1=last_c1;
		else if (Sonic_Dis.A_1==0)
			Sonic_Dis.A_1=110;
		else
			Sonic_Dis.A_1=Sonic_Dis.A_1;
		
		if(Sonic_Dis.A_2>250)
			Sonic_Dis.A_2=last_c2;
		else if (Sonic_Dis.A_2==0)
			Sonic_Dis.A_2=110;
		else
			Sonic_Dis.A_2=Sonic_Dis.A_2;
		
		if(Sonic_Dis.A_3>250)
			Sonic_Dis.A_3=last_c3;
				else if (Sonic_Dis.A_3==0)
			Sonic_Dis.A_3=110;
		else
			Sonic_Dis.A_3=Sonic_Dis.A_3;
		
		if(Sonic_Dis.A_4>250)
			Sonic_Dis.A_4=last_c4;
				else if (Sonic_Dis.A_4==0)
			Sonic_Dis.A_4=110;
		else
			Sonic_Dis.A_4=Sonic_Dis.A_4;
		
		if(Sonic_Dis.A_5>250)
			Sonic_Dis.A_5=last_c5;
				else if (Sonic_Dis.A_5==0)
			Sonic_Dis.A_5=110;
		else
			Sonic_Dis.A_5=Sonic_Dis.A_5;
	
		if(Sonic_Dis.A_6>250)
			Sonic_Dis.A_6=last_c6;
		else if (Sonic_Dis.A_6==0)
			Sonic_Dis.A_6=110;
		else
			Sonic_Dis.A_6=Sonic_Dis.A_6;
}



/******************************************************************************************************************
*                                 TIM5_Tim_Init(u32 arr,u16 psc)
*
*Description : ???5???,???1ms
*Arguments   : arr:????   psc:?????
*Returns     : none
*Notes       : ???????????:Tout=((arr+1)*(psc+1))/Ft us.  
               Ft=???????,??:Mhz
*******************************************************************************************************************
*/


void TIM5_Sonic_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM5_ICInitStructure;
	
	/***********************Clock initial****************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);      
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/***********************GPIO initial****************************************/	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0|GPIO_Pin_1 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//????????
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;//????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//????100MHz 
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0|GPIO_Pin_1);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
	
	 /***********************Timer initial****************************************/	 
	TIM_TimeBaseStructure.TIM_Prescaler=psc;//?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//??????
	TIM_TimeBaseStructure.TIM_Period=arr;//??????
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	
	
	//???TIM2??????
//	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1;//CC1S=04,????? IC4???TI1?
    TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//?????
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//???TI1?
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//??????,??? 
    TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ??????? ???
//    TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);//?????? ,??CC4IE????		
	TIM_ITConfig(TIM5,TIM_IT_CC3,ENABLE);						// ?????? ,??CC2IE????	
	TIM_ITConfig(TIM5,TIM_IT_CC4,ENABLE);						// ?????? ,??CC2IE????	
	TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);						// ?????? ,??CC2IE????	
	TIM_ITConfig(TIM5,TIM_IT_CC2,ENABLE);
	
    TIM_Cmd(TIM5,ENABLE );//?????5
	
  /***********************NVIC initial****************************************/
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;//????2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQ????
	NVIC_Init(&NVIC_InitStructure);//??????????VIC???	
}

void TIM3_Sonic_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM3_ICInitStructure;
	
	/***********************Clock initial****************************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);      
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	/***********************GPIO initial****************************************/	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7 ;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//    GPIO_Init(GPIOA,&GPIO_InitStructure);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
	
	 /***********************Timer initial****************************************/	 
	TIM_TimeBaseStructure.TIM_Prescaler=psc;//?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//??????
	TIM_TimeBaseStructure.TIM_Period=arr;//??????
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	
	//???TIM2??????
//	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1;//CC1S=04,????? IC4???TI1?
    TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//?????
    TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//???TI1?
    TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//??????,??? 
    TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ??????? ???
    TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
//	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1;
//	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
//	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2;
//	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
//	TIM_ITConfig(TIM3,TIM_IT_CC1,ENABLE);
//	TIM_ITConfig(TIM3,TIM_IT_CC2,ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_CC3,ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_CC4,ENABLE);
	
    TIM_Cmd(TIM3,ENABLE );//?????5
	
  /***********************NVIC initial****************************************/
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;//????2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQ????
	NVIC_Init(&NVIC_InitStructure);//??????????VIC???	
}



/*
********************************************************************************************************************
*                  void TIM5_IRQHandler(void)
*
*Description    :???5?????? 
*Arguments   : none
*Returns     : TRIGx  ???x
*Notes       : none
*F  T5C3   5??
 B  T2C4   1
 R2 T2C3   3
 L2 T5C1   2
 R1 T5C4   4
 L1 T5C2
********************************************************************************************************************
*/

void TIM5_IRQHandler(void)
{
	if((TIM5CH1_CAPTURE_STA&0X80)==0)//??????	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//??
		{
			if(TIM5CH1_CAPTURE_STA&0X40)        //?????????
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//??????
				{
					TIM5CH1_CAPTURE_STA|=0X80;	      //?????????
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//????4??????
		{
			if(TIM5CH1_CAPTURE_STA&0X40)//???????? 		
			{
				TIM5CH1_CAPTURE_STA|=0X80;	//??????????????
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//????????.
				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ????????
			}else //????,????????
			{
				TIM5CH1_CAPTURE_STA=0;	//??
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//?????????
				TIM_Cmd(TIM5,DISABLE ); 	//?????2
				TIM_SetCounter(TIM5,0);
				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);	//CC1P=1 ????????
				TIM_Cmd(TIM5,ENABLE ); 	//?????2
			}
		}
	}
	
	if((TIM5CH2_CAPTURE_STA&0X80)==0)//??????	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//??
		{
			if(TIM5CH2_CAPTURE_STA&0X40)        //?????????
			{
				if((TIM5CH2_CAPTURE_STA&0X3F)==0X3F)//??????
				{
					TIM5CH2_CAPTURE_STA|=0X80;	      //?????????
					TIM5CH2_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH2_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)//????4??????
		{
			if(TIM5CH2_CAPTURE_STA&0X40)//???????? 		
			{
				TIM5CH2_CAPTURE_STA|=0X80;	//??????????????
				TIM5CH2_CAPTURE_VAL=TIM_GetCapture2(TIM5);//????????.
				TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ????????
			}else //????,????????
			{
				TIM5CH2_CAPTURE_STA=0;	//??
				TIM5CH2_CAPTURE_VAL=0;
				TIM5CH2_CAPTURE_STA|=0X40;		//?????????
				TIM_Cmd(TIM5,DISABLE); 	//?????2
				TIM_SetCounter(TIM5,0);
				TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);	//CC1P=1 ????????
				TIM_Cmd(TIM5,ENABLE ); 	//?????2
			}
		}
	}
	if((TIM5CH3_CAPTURE_STA&0X80)==0)//??????	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//??
		{
			if(TIM5CH3_CAPTURE_STA&0X40)        //?????????
			{
				if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//??????
				{
					TIM5CH3_CAPTURE_STA|=0X80;	      //?????????
					TIM5CH3_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH3_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)//????4??????
		{
			if(TIM5CH3_CAPTURE_STA&0X40)//???????? 		
			{
				TIM5CH3_CAPTURE_STA|=0X80;	//??????????????
				TIM5CH3_CAPTURE_VAL=TIM_GetCapture3(TIM5);//????????.
				TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ????????
			}else //????,????????
			{
				TIM5CH3_CAPTURE_STA=0;	//??
				TIM5CH3_CAPTURE_VAL=0;
				TIM5CH3_CAPTURE_STA|=0X40;		//?????????
				TIM_Cmd(TIM5,DISABLE); 	//?????2
				TIM_SetCounter(TIM5,0);
				TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling);	//CC1P=1 ????????
				TIM_Cmd(TIM5,ENABLE ); 	//?????2
			}
		}
	}
	
	if((TIM5CH4_CAPTURE_STA&0X80)==0)//??????	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//??
		{
			if(TIM5CH4_CAPTURE_STA&0X40)        //?????????
			{
				if((TIM5CH4_CAPTURE_STA&0X3F)==0X3F)//??????
				{
					TIM5CH4_CAPTURE_STA|=0X80;	      //?????????
					TIM5CH4_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH4_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)//????4??????
		{
			if(TIM5CH4_CAPTURE_STA&0X40)//???????? 		
			{
				TIM5CH4_CAPTURE_STA|=0X80;	//??????????????
				TIM5CH4_CAPTURE_VAL=TIM_GetCapture4(TIM5);//????????.
				TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ????????
			}else //????,????????
			{
				TIM5CH4_CAPTURE_STA=0;	//??
				TIM5CH4_CAPTURE_VAL=0;
				TIM5CH4_CAPTURE_STA|=0X40;		//?????????
				TIM_Cmd(TIM5,DISABLE); 	//?????2
				TIM_SetCounter(TIM5,0);
				TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Falling);	//CC1P=1 ????????
				TIM_Cmd(TIM5,ENABLE ); 	//?????2
			}
		}
	}
	
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //???????
}

void TIM3_IRQHandler(void)
{
		
	
		
	
	if((TIM3CH3_CAPTURE_STA&0X80)==0)//??????	
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//??
		{
			if(TIM3CH3_CAPTURE_STA&0X40)        //?????????
			{
				if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//??????
				{
					TIM3CH3_CAPTURE_STA|=0X80;	      //?????????
					TIM3CH3_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM3CH3_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)//????4??????
		{
			if(TIM3CH3_CAPTURE_STA&0X40)//???????? 		
			{
				TIM3CH3_CAPTURE_STA|=0X80;	//??????????????
				TIM3CH3_CAPTURE_VAL=TIM_GetCapture3(TIM3);//????????.
				TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 ????????
			}else //????,????????
			{
				TIM3CH3_CAPTURE_STA=0;	//??
				TIM3CH3_CAPTURE_VAL=0;
				TIM3CH3_CAPTURE_STA|=0X40;		//?????????
				TIM_Cmd(TIM3,DISABLE ); 	//?????2
				TIM_SetCounter(TIM3,0);
				TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling);	//CC1P=1 ????????
				TIM_Cmd(TIM3,ENABLE ); 	//?????2
			}
		}
	}
	
	if((TIM3CH4_CAPTURE_STA&0X80)==0)//??????	
	{
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//??
		{
			if(TIM3CH4_CAPTURE_STA&0X40)        //?????????
			{
				if((TIM3CH4_CAPTURE_STA&0X3F)==0X3F)//??????
				{
					TIM3CH4_CAPTURE_STA|=0X80;	      //?????????
					TIM3CH4_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM3CH4_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)//????4??????
		{
			if(TIM3CH4_CAPTURE_STA&0X40)//???????? 		
			{
				TIM3CH4_CAPTURE_STA|=0X80;	//??????????????
				TIM3CH4_CAPTURE_VAL=TIM_GetCapture4(TIM3);//????????.
				TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 ????????
			}else //????,????????
			{
				TIM3CH4_CAPTURE_STA=0;	//??
				TIM3CH4_CAPTURE_VAL=0;
				TIM3CH4_CAPTURE_STA|=0X40;		//?????????
				TIM_Cmd(TIM3,DISABLE); 	//?????2
				TIM_SetCounter(TIM3,0);
				TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Falling);	//CC1P=1 ????????
				TIM_Cmd(TIM3,ENABLE ); 	//?????2
			}
		}
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //???????
}

void Ultrasonic_Trig_Start(void)
{
	Trig1_on(); //F_Right_Trig_on()
	delay_us(20);  //??10us??
	Trig1_off(); //F_Right_Trig_off()
	
	Trig2_on(); //F_Right_Trig_on()
	delay_us(20);  //??10us??
	Trig2_off(); //F_Right_Trig_off()
	
	Trig3_on(); //F_Right_Trig_on()
	delay_us(20);  //??10us??
	Trig3_off(); //F_Right_Trig_off()
	
	Trig4_on(); //F_Right_Trig_on()
	delay_us(20);  //??10us??
	Trig4_off(); //F_Right_Trig_off()
	
	Trig5_on(); //F_Right_Trig_on()
	delay_us(20);  //??10us??
	Trig5_off(); //F_Right_Trig_off()
	
	Trig6_on(); //F_Right_Trig_on()
	delay_us(20);  //??10us??
	Trig6_off(); //F_Right_Trig_off()
}

//int Sonic_Length(float L1,float L2)
//{	
//	float ang,L3,L4,L_b=136,d_L;//10.9
//	int Length;
//	d_L=fabs(L1-L2);
//	if(d_L>=1300.0f)//???
//  {
//		if(L1>=L2)Length=L2;
//		else Length=L1;
//		return Length;
//	}	
//	if(d_L>=80.0f)d_L=80.0f;
//	else d_L=d_L;
//	ang=atan(L_b/d_L);//????
//	L3=L1*sin(ang);
//	L4=L2*sin(ang);
//	Length=(L3+L4)/2.0f;	
//  return Length;
//}


//int Sonic_Length_l(float L1,float L2)
//{	
//	float ang,L3,L4,L_b=61.0f,d_L;//10.9
//	int Length;
//	d_L=fabs(L1-L2);
//	if(d_L>=130.0f)
//  {
//		if(L1>=L2)Length=L2;
//		else Length=L1;
//		return Length;
//	}	
//	if(d_L>=80.0f)d_L=80.0f;
//	else d_L=d_L;
//	ang=atan(L_b/d_L);//????
//	L3=L1*sin(ang);
//	L4=L2*sin(ang);
//	Length=(L3+L4)/2.0f;	
//  return Length;
//}

