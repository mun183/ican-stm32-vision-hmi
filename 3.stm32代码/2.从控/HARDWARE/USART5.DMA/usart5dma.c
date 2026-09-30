#include "usart5dma.h"
#include "usart2dma.h"
#include "oled.h"
#include "led.h"
#include "delay.h"
#include "usart4dma.h"
#include "usartdma.h"
//#include "control.h"
u8 USART_RX5_BUF[128];  // 接收缓冲区


#define USART_REC_LEN 20
u8 USART_RX_BUF5[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA5=0;       //接收状态标记	
//串口5接收数据
void USART5_Init(int Baud)
{
	NVIC_InitTypeDef NVIC_InitStructure ;//定义中断结构体
	GPIO_InitTypeDef GPIO_InitStructure;//定义IO初始化结构体
	USART_InitTypeDef USART_InitStructure;//定义串口结构体
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);//打开串口对应的外设时钟
	//初始化串口参数
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_BaudRate = Baud;
	//初始化串口
	USART_Init(UART5,&USART_InitStructure);
	//配置中断
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;               //通道设置为串口中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //中断占先等级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              //中断响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断
	NVIC_Init(&NVIC_InitStructure);
	//中断配置
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	//启动串口
	USART_Cmd(UART5, ENABLE);
	//设置IO口时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //管脚模式:输出口
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //类型:推挽模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 //上拉下拉设置
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//IO口速度
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  //管脚指定
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//管脚模式:输入口
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 //上拉下拉设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;    //管脚指定
	GPIO_Init(GPIOC, &GPIO_InitStructure);      //初始化
}
uint16_t distance_left;
uint16_t distance_right;
uint8_t work_flag1;
uint8_t Res;
uint8_t buf_board_final[9];

uint16_t command1;
uint16_t command2;
uint16_t command3;
//uint16_t command4;
//uint16_t command5;
//uint16_t command6;

void UART5_IRQHandler(void)
{	
//    static u8 head_flag=0;
//    static u8 state=0;
//    static uint8_t BUF_BOARD[9];

	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{
        Res =USART_ReceiveData(UART5);//(USART1->DR);	//读取接收到的数据
        if(Res==0x11)
        {
            USART_RX5_BUF[0]=Res;  // 接收缓冲区  
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;
				}
				if(Res==0x10)
        {
            USART_RX5_BUF[1]=Res;  // 接收缓冲区   
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;					
				}
				
				if(Res==0x21)
        {
            USART_RX5_BUF[2]=Res;  // 接收缓冲区   
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;					
				}

				if(Res==0x20)
        {
            USART_RX5_BUF[3]=Res;  // 接收缓冲区     
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;					
				}
				
				
				if(Res==0x31)
        {
            USART_RX5_BUF[4]=Res;  // 接收缓冲区       
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;
				}
				if(Res==0x30)
        {
            USART_RX5_BUF[5]=Res;  // 接收缓冲区       
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;
				}
				
				if(Res==0x41)
        {
            USART_RX5_BUF[6]=Res;  // 接收缓冲区     
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;					
				}
				if(Res==0x40)
        {
            USART_RX5_BUF[7]=Res;  // 接收缓冲区  
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;					
				}
				
				if(Res==0x51)
        {
            USART_RX5_BUF[8]=Res;  // 接收缓冲区     
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;					
				}
				if(Res==0x50)
        {
            USART_RX5_BUF[9]=Res;  // 接收缓冲区     
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[11]=0;					
				}
				
				if(Res==0x61)
        {
            USART_RX5_BUF[10]=Res;  // 接收缓冲区    
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[0]=0;
						USART_RX5_BUF[11]=0;					
				}
				if(Res==0x60)
        {
            USART_RX5_BUF[11]=Res;  // 接收缓冲区     
						USART_RX5_BUF[1]=0;
						USART_RX5_BUF[2]=0;
						USART_RX5_BUF[3]=0;
						USART_RX5_BUF[4]=0;
						USART_RX5_BUF[5]=0;
						USART_RX5_BUF[6]=0;
						USART_RX5_BUF[7]=0;
						USART_RX5_BUF[8]=0;
						USART_RX5_BUF[9]=0;
						USART_RX5_BUF[10]=0;
						USART_RX5_BUF[0]=0;					
				}
  }
}




void usart5_board_senddata(uint8_t flag1)
{
		uint8_t databag[2]={0};
    databag[0]=0xFF;
    databag[1]=flag1;
		USART_Senddatas(UART5,databag,2);
}


void usart5_board_command(uint16_t command1,uint16_t command2,uint16_t command3)
{
		uint8_t databag[4]={0};
    databag[0]=0xFF;
    databag[1]=command1;
		databag[2]=command2;
		databag[3]=command3;
		USART_Senddatas(UART5,databag,4);
}

