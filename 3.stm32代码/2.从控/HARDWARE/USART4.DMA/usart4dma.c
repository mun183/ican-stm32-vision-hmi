#include "usart4dma.h"
#include "oled.h"
#include "led.h"
#include "delay.h"
#include "usartdma.h"
#include "sys.h"
u8 USART_RX4_BUF[13];  // 接收缓冲区
u16 USART_RX4_STA = 0;  // 接收状态标记
u16 clothes_data= 0;  // 接收状态标记

/*
********************************************************************************************************************
*                  void  UART4_Init(void)
*
*Description : 串口4的初始化 
							 UART4_RX---PC11
							 UART4_TX---PC10
*Arguments   : Baud：波特率配置
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/
void USART4_Init(int Baud)
{
	NVIC_InitTypeDef NVIC_InitStructure ;//定义中断结构体
	GPIO_InitTypeDef GPIO_InitStructure;//定义IO初始化结构体
	USART_InitTypeDef USART_InitStructure;//定义串口结构体
//	DMA_InitTypeDef DMA_InitStructure;//定义DMA结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);//打开串口对应的外设时钟
	//**********************串口 发送 DMA 设置（DMA1_Stream6）**************************
	// 0 启动DMA时钟
	// 1 DMA发送中断设置
	//初始化串口参数
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_BaudRate = Baud;
	//初始化串口
	USART_Init(UART4,&USART_InitStructure);
	//配置中断
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;               //通道设置为串口中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //中断占先等级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              //中断响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断
	NVIC_Init(&NVIC_InitStructure);
	//中断配置
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
	
	//启动串口
	USART_Cmd(UART4, ENABLE);
	//设置IO口时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //管脚模式:输出口
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //类型:推挽模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 //上拉下拉设置
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//IO口速度
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  //管脚指定
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//管脚模式:输入口
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 //上拉下拉设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;    //管脚指定
	GPIO_Init(GPIOC, &GPIO_InitStructure);      //初始化
//	send_com(0x45);

}
/*
********************************************************************************************************************
*                  void UART4_DMATransfer(uint32_t *BufferSRC, uint32_t BufferSize)
*
*Description : 串口4发送函数 
*Arguments   : BufferSRC:发送数据存放地址；BufferSize:发送数据字节数
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/

/*
********************************************************************************************************************
*                  void  UART4_IRQHandler(void)
*
*Description : 串口4接收函数 
*Arguments   : none
*Returns     : none
*Notes       : none
********************************************************************************************************************
*/


void usart_board_senddata()
{
		uint8_t databag[13]={0};
    databag[0]=USART_RX1_BUF[0];
    databag[1]=USART_RX1_BUF[1];
    databag[2]=USART_RX1_BUF[2];
    databag[3]=USART_RX1_BUF[3];
    databag[4]=USART_RX1_BUF[4];
    databag[5]=USART_RX1_BUF[5];
    databag[6]=USART_RX1_BUF[6];
    databag[7]=USART_RX1_BUF[7];
    databag[8]=USART_RX1_BUF[8];
    databag[9]=USART_RX1_BUF[9];
		databag[10]=USART_RX1_BUF[10];
		databag[11]=USART_RX1_BUF[11];
		databag[12]=clothes_data;
		USART_Senddatas(UART4,databag,13);
}

__IO uint8_t work_flag_value=0;

void UART4_IRQHandler(void)
{	
		static u8 Res;
    static u8 head_flag = 0;
    static u8 receive_count = 0;

    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        Res = USART_ReceiveData(UART4); // 读取接收到的数据

        if(Res == 0xFF)
        {
            head_flag = 1; // 检测到帧头0xFF
            receive_count = 0; // 重置接收计数器
        }
        else
        {
            if(head_flag == 1)
            {
                if(receive_count < 13)
                {
                    USART_RX4_BUF[receive_count] = Res; // 存储接收到的数据
                    receive_count++;

                    if(receive_count == 13)
                    {
                        head_flag = 0; // 重置帧头标志
                        USART_RX4_STA |= (1 << 15); // 设置接收完成标志
                    }
                }
                else
                {
                    head_flag = 0; // 重置帧头标志
                    receive_count = 0; // 重置接收计数器
                }
            }
        }
    }
}
