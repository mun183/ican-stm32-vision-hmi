
#include <encoder.h>
EncoderStru Encoder={0,0};

int Encoder_Length_L1,Encoder_Length_R1,Encoder_Length_L2,Encoder_Length_R2;
int Read_EncoderL1(void)
{	
	Encoder.Lf1=TIM2->CNT;
	return Encoder.Lf1;		
}

//int Read_EncoderL2(void)
//{	
//	Encoder.Lf2=TIM3->CNT;
//	return Encoder.Lf2;		
//}

int Read_EncoderR1(void)
{
	Encoder.Rt1 =TIM4-> CNT;
	return Encoder.Rt1;
}
int Read_EncoderR2(void)
{
	Encoder.Rt2 =TIM8-> CNT;
	return Encoder.Rt2;
}

void Read_Encoder(void)
{
	
    Encoder_Length_L1=Read_EncoderL1();
//	Encoder_Length_L2=Read_EncoderL2();
	Encoder_Length_R1=Read_EncoderR1();
	Encoder_Length_R2=Read_EncoderR2();
	
}


void Timer6_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 999;//自动重新装载寄存器周期的值澹ㄥ计数值澹)
	TIM_TimeBaseStructure.TIM_Prescaler = 83;//时钟分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//对外部时钟进行采样的时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //高级定时器1是用定时器功能配置这个才可以是正常的计数频率一开始的72mhz 值得注意的地方
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);//参数初始化

	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn;; //???9??
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //?????0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);       

	TIM_Cmd(TIM6, ENABLE);//启动定时器 
}

void TIM2_Encoder_Init(u16 arr,u16 psc)
{
			TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
			TIM_ICInitTypeDef TIM_ICInitStructure;  
			GPIO_InitTypeDef GPIO_InitStructure;

			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//TIM3????
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//??GPIOB??

			GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2); 
			GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);

			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;	//????
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          //??
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;          //??
			GPIO_Init(GPIOA, &GPIO_InitStructure);					      //?????????GPIOB

			//???3??
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  //?????
			TIM_TimeBaseStructure.TIM_Period=arr;     //??????
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
			TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
			TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //设定计数器自动重装值
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //???,????? 	
			TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);  //TIM3???

			TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//???????3
			TIM_ICStructInit(&TIM_ICInitStructure);
			TIM_ICInitStructure.TIM_ICFilter = 6;
			TIM_ICInit(TIM2, &TIM_ICInitStructure);

			TIM_ClearFlag(TIM2, TIM_FLAG_Update);//??TIM??????
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//??????

			TIM_SetCounter(TIM2,30000);

			TIM_Cmd(TIM2, ENABLE); 
}

void TIM3_Encoder_Init(u16 arr,u16 psc)
{
			TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
			TIM_ICInitTypeDef TIM_ICInitStructure;  
			GPIO_InitTypeDef GPIO_InitStructure;

			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM3????
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//??GPIOB??

			GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 
			GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);

			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;	//????
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          //??
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;          //??
			GPIO_Init(GPIOA, &GPIO_InitStructure);					      //?????????GPIOB

			//???3??
			TIM_TimeBaseStructure.TIM_Prescaler=psc;  //?????
			TIM_TimeBaseStructure.TIM_Period=arr;     //??????
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
			TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
			TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //设定计数器自动重装值
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //???,????? 	
			TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);  //TIM3???

			TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//???????3
			TIM_ICStructInit(&TIM_ICInitStructure);
			TIM_ICInitStructure.TIM_ICFilter = 6;
			TIM_ICInit(TIM3, &TIM_ICInitStructure);

			TIM_ClearFlag(TIM3, TIM_FLAG_Update);//??TIM??????
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//??????

			TIM_SetCounter(TIM3,30000);

			TIM_Cmd(TIM3, ENABLE); 
}


void TIM4_Encoder_Init(u16 arr,u16 psc)
{
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_ICInitTypeDef TIM_ICInitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;
	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//TIM3????
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//??GPIOB??
	
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); 
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13;	//????
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          //??
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;          //??
    GPIO_Init(GPIOD, &GPIO_InitStructure);					      //?????????GPIOB
	
	//???3??
	  TIM_TimeBaseStructure.TIM_Prescaler=psc;  //?????
	  TIM_TimeBaseStructure.TIM_Period=arr;     //??????
	  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //设定计数器自动重装值
  	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //???,????? 	
	  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);  //TIM3???
	
	  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//???????3
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//??TIM??????
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//??????
	
	  TIM_SetCounter(TIM4,30000);
	
    TIM_Cmd(TIM4, ENABLE); 
}

void TIM8_Encoder_Init(u16 arr,u16 psc)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_ICInitTypeDef TIM_ICInitStructure;  
    GPIO_InitTypeDef GPIO_InitStructure;
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	  GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); 
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;	//????
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          //??
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;          //??
    GPIO_Init(GPIOC, &GPIO_InitStructure);					      //?????????GPIOB
	
	//???3??
	  TIM_TimeBaseStructure.TIM_Prescaler=psc;  //?????
	  TIM_TimeBaseStructure.TIM_Period=arr;     //??????
	  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //设定计数器自动重装值
	  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //???,????? 	
	  TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);  //TIM3???
	
	  TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//???????3
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
	
	  TIM_ClearFlag(TIM8, TIM_FLAG_Update);//??TIM??????
    TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);//??????
	
	  TIM_SetCounter(TIM8,30000);
	
    TIM_Cmd(TIM8, ENABLE);
	
}

int Encoder_Fabs_L1=0,Encoder_Fabs_L2=0,Encoder_Fabs_R1=0,Encoder_Fabs_R2=0;
int Encoder_Fabs_L1_last=0,Encoder_Fabs_L2_last=0,Encoder_Fabs_R1_last=0,Encoder_Fabs_R2_last=0;
int Encoder_Real_L1=0,Encoder_Real_L2=0,Encoder_Real_R1=0,Encoder_Real_R2=0;

void Encoder_Fabs(void)//取绝对值对应走的距离,不取绝对值对应的是位移
{
	Read_Encoder();
	Encoder_Fabs_L1=Encoder_Length_L1-30000;
	Encoder_Fabs_R1=Encoder_Length_R1-30000;
	Encoder_Fabs_L2=Encoder_Length_L2-30000;
	Encoder_Fabs_R2=Encoder_Length_R2-30000;
	
	if(Encoder_Fabs_L1>=0)
	{
		Encoder_Fabs_L1=Encoder_Fabs_L1;
	}else if(Encoder_Fabs_L1<0)
	{
		Encoder_Fabs_L1=-Encoder_Fabs_L1;
	}
//	
//	if(Encoder_Fabs_L2>=0)
//	{
//		Encoder_Fabs_L2=Encoder_Fabs_L2;
//	}else if(Encoder_Fabs_L2<0)
//	{
//		Encoder_Fabs_L2=-Encoder_Fabs_L2;
//	}
	
//	
	if(Encoder_Fabs_R1>=0)
	{
		Encoder_Fabs_R1=Encoder_Fabs_R1;
	}else if(Encoder_Fabs_R1<0)
	{
		Encoder_Fabs_R1=-Encoder_Fabs_R1;
	}
	
	if(Encoder_Fabs_R2>=0)
	{
		Encoder_Fabs_R2=Encoder_Fabs_R2;
	}else if(Encoder_Fabs_R2<0)
	{
		Encoder_Fabs_R2=-Encoder_Fabs_R2;
	}
}

void Encoder_Real(void)//不取绝对值对应的是位移
{
	Read_Encoder();
	Encoder_Real_L1=-(Encoder_Length_L1-30000);
	Encoder_Real_R1=(Encoder_Length_R1-30000);
//	Encoder_Real_L2=-(Encoder_Length_L2-30000);
	Encoder_Real_R2=(Encoder_Length_R2-30000);
}

