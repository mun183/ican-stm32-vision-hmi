#include "usartdma.h"
#include "led.h"
#include "oled.h"


u8 USART_RX1_BUF[128];  // 接收缓冲区
u16 USART_RX1_STA = 0;      // 接收状态标记
extern 	u8 flag1_inc;
u8 receive2_count;   


extern 	u8 flag_inc;
/*
********************************************************************************************************************
*                  void  USART1_Init(void)
*
*Description : 串口1的初始化 
							 USART1_RX---PA10
							 USART1_TX---PA9
*Arguments   : Baud：波特率配置
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

void USART1_Init(int Baud)
{
		NVIC_InitTypeDef NVIC_InitStructure ; //定义中断结构体
		GPIO_InitTypeDef GPIO_InitStructure;  //定义IO初始化结构体
		USART_InitTypeDef USART_InitStructure;//定义串口结构体

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//打开串口对应的外设时钟

    //初始化串口参数
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_BaudRate = Baud;
	//初始化串口
    USART_Init(USART1,&USART_InitStructure);

	//配置中断
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //通道设置为串口中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //中断占先等级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              //中断响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断
    NVIC_Init(&NVIC_InitStructure);

		//中断配置
		USART_ITConfig(USART1,USART_IT_TC,DISABLE);
		USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
		USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
		USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);


    //启动串口
    USART_Cmd(USART1, ENABLE);

    //设置IO口时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //管脚模式:输出口
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //类型:推挽模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 //上拉下拉设置
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//IO口速度
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  //管脚指定TX
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化


		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//管脚模式:输入口
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 //上拉下拉设置
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;    //管脚指定
		GPIO_Init(GPIOB, &GPIO_InitStructure);      //初始化
}

void USART_Senddatas(USART_TypeDef* USARTxx,u8* addr,int size)
{
	while(size--) //判断数据发送完没有
	{
		while(USART_GetFlagStatus(USARTxx,USART_FLAG_TC) == RESET);//等待上一个byte的数据发送结束。
		USART_SendData(USARTxx,*addr);//调用STM32标准库函数发送数据
		addr++; //地址偏移
	}
}



u16 GM_REC[9]={0};//二维码扫描

void USART1_IRQHandler(void)
{

    static u8 Res;
//    static u8 head_flag = 0;         // 是否检测到包头
//    static u8 tail_ff_count = 0;     // 已接收到的 0xff 数量

    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {
        Res = USART_ReceiveData(USART1);  // 必须读取清除中断标志
				if (Res == 0x11)
				{
							USART_RX1_BUF[0] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}		
				if (Res == 0x10)
				{
							USART_RX1_BUF[1] = Res;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}	
				
				
				if (Res == 0x21)
				{
							USART_RX1_BUF[2] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}		
				if (Res == 0x20)
				{
							USART_RX1_BUF[3] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}	
				
				
				if (Res == 0x31)
				{
							USART_RX1_BUF[4] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}		
				if (Res == 0x30)
				{
							USART_RX1_BUF[5] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}	
				
				
				if (Res == 0x41)
				{
							USART_RX1_BUF[6] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}		
				if (Res == 0x40)
				{
							USART_RX1_BUF[7] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}
				
				if (Res == 0x51)
				{
							USART_RX1_BUF[8] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}		
				if (Res == 0x50)
				{
							USART_RX1_BUF[9] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[11]=0;
				}	
				
				
				if (Res == 0x61)
				{
							USART_RX1_BUF[10] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[0]=0;
							USART_RX1_BUF[11]=0;
				}		
				if (Res == 0x60)
				{
							USART_RX1_BUF[11] = Res;
							USART_RX1_BUF[1]=0;
							USART_RX1_BUF[2]=0;
							USART_RX1_BUF[3]=0;
							USART_RX1_BUF[4]=0;
							USART_RX1_BUF[5]=0;
							USART_RX1_BUF[6]=0;
							USART_RX1_BUF[7]=0;
							USART_RX1_BUF[8]=0;
							USART_RX1_BUF[9]=0;
							USART_RX1_BUF[10]=0;
							USART_RX1_BUF[0]=0;
				}
	}
}
