#include "usart4dma.h"
#include "oled.h"
#include "led.h"
#include "delay.h"
#include "usartdma.h"


u16 receive_cnt;//计算成功接收数据帧次数
u8 confidence;
u16 distance,noise,reftof;
u32 peak,intg;
u8 dis;
LidarPointTypedef Pack_Data[12];/* 雷达接收的数据储存在这个变量之中 */
u16 DISTANCE;
void USART4_Init(int Baud)
{
	NVIC_InitTypeDef NVIC_InitStructure ;//定义中断结构体
	GPIO_InitTypeDef GPIO_InitStructure;//定义IO初始化结构体
	USART_InitTypeDef USART_InitStructure;//定义串口结构体
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);//打开串口对应的外设时钟
	//初始化串口参数
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
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


}

void data_process(void)/*数据处理函数，完成一帧之后可进行数据处理*/
{
		/* 计算距离 */
//		static u8 cnt = 0;
		u8 i;
		static u16 count = 0;
//		static u32 sum = 0;
		LidarPointTypedef Pack_sum;
		for(i=0;i<12;i++)									/* 12个点取平均 */
		{
				if(Pack_Data[i].distance != 0)  /* 去除0的点 */
				{
						count++;
						Pack_sum.distance += Pack_Data[i].distance;
						Pack_sum.noise += Pack_Data[i].noise;
						Pack_sum.peak += Pack_Data[i].peak;
						Pack_sum.confidence += Pack_Data[i].confidence;
						Pack_sum.intg += Pack_Data[i].intg;
						Pack_sum.reftof += Pack_Data[i].reftof;
				}
		}
		if(count !=0)
		{

					distance = Pack_sum.distance/count;
					noise = Pack_sum.noise/count;
					peak = Pack_sum.peak/count;
					confidence = Pack_sum.confidence/count;
					intg = Pack_sum.intg/count;
					reftof = Pack_sum.reftof/count;
					Pack_sum.distance = 0;
					Pack_sum.noise = 0;
					Pack_sum.peak = 0;
					Pack_sum.confidence = 0;
					Pack_sum.intg = 0;
					Pack_sum.reftof = 0;
					count = 0;
		}
}

void UART4_IRQHandler(void)//接收ld14雷达数据
{
		static u8 state = 0;			//状态位	
		static u8 crc = 0;				//校验和
		static u8 cnt = 0;				//用于一帧12个点的计数
		static u8 PACK_FLAG = 0;  //命令标志位
		static u8 data_len  = 0;  //数据长度
		static u32 timestamp = 0; //时间戳
		static u8 state_flag = 1; //转入数据接收标志位
		u8 temp_data;
		if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)      /* 接收到数据 */
		{
				temp_data=USART_ReceiveData(UART4); 									 
				USART_ClearITPendingBit(UART4,USART_IT_RXNE); 				 /* 清除中断标志位 */
				if(state< 4) 																					 /* 起始符验证 前4个数据均为0xAA */
				{                                          
						if(temp_data == HEADER) state ++;
						else state = 0;
				}
				else if(state<10&&state>3)
				{
						switch(state)
						{
								case 4:   
									if(temp_data == device_address)              /* 设备地址验证  */
									{							
													state ++;
													crc = crc + temp_data;									
													break;        
									} 
									else state = 0,crc = 0;
								case 5:   
									if(temp_data == PACK_GET_DISTANCE)					 /* 获取测量数据命令 */
									{  
													PACK_FLAG = PACK_GET_DISTANCE;
													state ++;	
													crc = crc + temp_data;	
													break;									
									}		 

									else if(temp_data == PACK_RESET_SYSTEM) 		 /* 复位命令 */
									{
													PACK_FLAG = PACK_RESET_SYSTEM;
													state ++; 
													crc = crc + temp_data;	
													break;	
									}
									else if(temp_data == PACK_STOP)							 /* 停止测量数据传输命令 */
									{ 
													PACK_FLAG = PACK_STOP;
													state ++; 
													crc = crc + temp_data;	
													break;
									}
									else if(temp_data == PACK_ACK)							 /* 应答码命令 */
									{  
													PACK_FLAG = PACK_ACK;
													state ++;
													crc = crc + temp_data;	
													break;
									}			 				 
									else if(temp_data == PACK_VERSION)					 /* 获取传感器信息命令 */
									{ 
													PACK_FLAG = PACK_VERSION,
													state ++,
													crc = crc + temp_data;	   	     
													break;
									}
									else state = 0,crc = 0;
								case 6: if(temp_data == chunk_offset)          /* 偏移地址 */
												{  
													state ++;
													crc = crc + temp_data;
													break; 	  
												}	
												else state = 0,crc = 0;
								case 7: if(temp_data == chunk_offset)
												{  
													state ++;
													crc = crc + temp_data;
													break;
												}
												else state = 0,crc = 0;
								case 8: 
										data_len = (u16)temp_data;								 /* 数据长度低八位 */
										state ++; 
										crc = crc + temp_data;
										break;																			 
								case 9: 
										data_len = data_len + ((u16)temp_data<<8); 			 /* 数据长度高八位 */
										state ++;
										crc = crc + temp_data;
										break; 
								default: break;
						}
				}
				else if(state == 10 ) state_flag = 0;                    /*由switch跳出来时state为10，但temp_data仍为距离长度高八位数据，需跳过一次中断*/
				if(PACK_FLAG == PACK_GET_DISTANCE&&state_flag == 0)      /* 获取一帧数据并校验 */
				{
						if(state>9)
						{
								if(state<190)
								{
										static u8 state_num;
										state_num = (state-10)%15;
										switch(state_num)
										{
												case 0: 
													Pack_Data[cnt].distance = (u16)temp_data ;				 /* 距离数据低八位 */
													crc = crc + temp_data;
													state++;
													break;        
												case 1: 
													Pack_Data[cnt].distance = ((u16)temp_data<<8) + Pack_Data[cnt].distance;	 /* 距离数据 */
                                                    DISTANCE=Pack_Data[cnt].distance;
													crc = crc + temp_data;
													state++;
													break; 
												case 2:
													Pack_Data[cnt].noise = (u16)temp_data;				 /* 环境噪音低八位 */
													crc = crc + temp_data;
													state++;
													break; 
												case 3:
													Pack_Data[cnt].noise = ((u16)temp_data<<8) + Pack_Data[cnt].noise;				 /* 环境噪音 */
													crc = crc + temp_data;
													state++;
													break; 
												case 4:
													Pack_Data[cnt].peak = (u32)temp_data;				 										 /* 接受强度信息低八位 */
													crc = crc + temp_data;
													state++;
													break; 
												case 5:
													Pack_Data[cnt].peak = ((u32)temp_data<<8) + Pack_Data[cnt].peak;
													crc = crc + temp_data;
													state++;
													break; 
												case 6:
													Pack_Data[cnt].peak = ((u32)temp_data<<16) + Pack_Data[cnt].peak;	
													crc = crc + temp_data;
													state++;
													break; 
												case 7:
													Pack_Data[cnt].peak = ((u32)temp_data<<24) + Pack_Data[cnt].peak;				    /* 接受强度信息 */
													crc = crc + temp_data;
													state++;
													break; 
												case 8:
													Pack_Data[cnt].confidence = temp_data;				 /* 置信度 */
													crc = crc + temp_data;
													state++;
													break; 
												case 9:
													Pack_Data[cnt].intg = (u32)temp_data;															/* 积分次数低八位 */
													crc = crc + temp_data;
													state++;
													break; 
												case 10:
													Pack_Data[cnt].intg = ((u32)temp_data<<8) + Pack_Data[cnt].intg;
													crc = crc + temp_data;
													state++;
													break; 
												case 11:
													Pack_Data[cnt].intg = ((u32)temp_data<<16) + Pack_Data[cnt].intg;
													crc = crc + temp_data;
													state++;
													break; 
												case 12:
													Pack_Data[cnt].intg = ((u32)temp_data<<24) + Pack_Data[cnt].intg;				  	 /* 积分次数 */
													crc = crc + temp_data;
													state++;
													break; 
												case 13:
													Pack_Data[cnt].reftof = (int16_t)temp_data;				 								 /* 温度表征值低八位 */
													crc = crc + temp_data;
													state++;
													break; 
												case 14:
													Pack_Data[cnt].reftof = ((int16_t)temp_data<<8) +Pack_Data[cnt].reftof;			/* 温度表征值 */
													crc = crc + temp_data;
													state++;
													cnt++;							 /* 进入下一个测量点 */
													break; 
												default: break;
										}
							}
										/* 时间戳 */
										if(state == 190) timestamp = temp_data,state++,crc = crc + temp_data;
										else if(state == 191) timestamp = ((u32)temp_data<<8) + timestamp,state++,crc = crc + temp_data; 
										else if(state == 192) timestamp = ((u32)temp_data<<16) + timestamp,state++,crc = crc + temp_data;
										else if(state == 193) timestamp = ((u32)temp_data<<24) + timestamp,state++,crc = crc + temp_data; 
										else if(state==194)
										{
													if(temp_data == crc)   /* 校验成功 */
													{
															data_process();  	 /* 数据处理函数，完成一帧之后可进行数据处理 */
															receive_cnt++;	 	 /* 输出接收到正确数据的次数 */
													}
													distance = Pack_Data[0].distance;
													crc = 0;
													state = 0;
													state_flag = 1;
													cnt = 0; 							 /* 复位*/
										}
							
						}
				}
		}
}
void usart4_board_command(uint16_t cmd1,uint16_t cmd2,uint16_t cmd3)
{
		uint8_t databag[4]={0};
    databag[0]=0xFF;
    databag[1]=cmd1;
		databag[2]=cmd2;
		databag[3]=cmd3;
		USART_Senddatas(UART4,databag,4);
}
