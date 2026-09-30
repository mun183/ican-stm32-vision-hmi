#include "usartdma.h"
#include "led.h"
#include "oled.h"
#include "usart2dma.h"
#define RX2_BUFFER_SIZE 128  // 可以根据实际需求调整
u8 USART_RX2_BUF[128];  // 接收缓冲区
u16 USART_RX2_STA = 0;      // 接收状态标记
extern 	u8 flag2_inc;
u8 receive2_count;   
void USART2_Init(int Baud)
{
		NVIC_InitTypeDef NVIC_InitStructure ; //定义中断结构体
		GPIO_InitTypeDef GPIO_InitStructure;  //定义IO初始化结构体
		USART_InitTypeDef USART_InitStructure;//定义串口结构体

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//打开串口对应的外设时钟

    //初始化串口参数
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_BaudRate = Baud;
	//初始化串口
    USART_Init(USART2,&USART_InitStructure);

	//配置中断
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               //通道设置为串口中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //中断占先等级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              //中断响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断
    NVIC_Init(&NVIC_InitStructure);

		//中断配置
		USART_ITConfig(USART2,USART_IT_TC,DISABLE);
		USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);
		USART_ITConfig(USART2,USART_IT_TXE,DISABLE);
		USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);


    //启动串口
    USART_Cmd(USART2, ENABLE);

    //设置IO口时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //管脚模式:输出口
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //类型:推挽模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 //上拉下拉设置
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//IO口速度
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  //管脚指定TX
		GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化


		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//管脚模式:输入口
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	 //上拉下拉设置
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;    //管脚指定
		GPIO_Init(GPIOD, &GPIO_InitStructure);      //初始化
}



void USART2_IRQHandler(void)
{
    static u8 Res;

    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        Res = USART_ReceiveData(USART2);  // 必须读取清除中断标志
			if (Res == 0x01)
			{
						USART_RX2_BUF[0] = Res;
						USART_RX2_BUF[1] =0;
						USART_RX2_BUF[2] =0;
			}		
			if (Res == 0x02)
			{
						USART_RX2_BUF[1] = Res;
						USART_RX2_BUF[0] =0;
						USART_RX2_BUF[2] =0;
			}	
			if (Res == 0x03)
			{
						USART_RX2_BUF[2] = Res;
						USART_RX2_BUF[0] =0;
						USART_RX2_BUF[1] =0;
			}		
			if (Res == 0x04)
			{
						USART_RX2_BUF[3] = Res;
			}				
//        if (!head_flag)
//        {
//            if (Res == 0x55)
//            {
//                head_flag = 1;          // 检测到包头
//                receive2_count = 0;      // 清空计数器
//                tail_ff_count = 0;
//                USART_RX1_BUF[receive2_count++] = Res;
//            }
//        }
//        else
//        {
//            USART_RX1_BUF[receive2_count++] = Res;

//            // 判断是否是 0xFF，统计连续出现次数
//            if (Res == 0xFF)
//            {
//                tail_ff_count++;
//                if (tail_ff_count >= 1)
//                {
//                    // 找到完整包，减去最后三个 0xFF
//                    receive2_count -= 1;

//                    // 设置接收完成标志
//                    USART_RX1_STA |= (1 << 15);

//                    // 可选：重置状态
//                    head_flag = 0;
//                    receive2_count = 0;
//                    tail_ff_count = 0;
//                }
//            }
//            else
//            {
//                tail_ff_count = 0;  // 非 0xFF 时清零计数器

//                // 检查是否超出缓冲区
//                if (receive2_count >= RX2_BUFFER_SIZE - 1)
//                {
//                    // 缓冲区溢出，重置
//                    head_flag = 0;
//                    receive2_count = 0;
//                    tail_ff_count = 0;
//                }
//            }
//        }
    }

}
