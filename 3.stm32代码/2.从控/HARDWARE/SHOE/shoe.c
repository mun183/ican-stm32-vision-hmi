//#include "usartdma.h"
//#include "led.h"
//#include "oled.h"
//#include "usart2dma.h"
//#include "dianji.h"
//#include "shoe.h"
//#include "usart5dma.h"
//#include "delay.h"
//static uint8_t BJDJ = 0;
//static uint8_t BJDJ1 = 0;

//void contorl_TUOXIE_Shenchu()
//	{
//		if(USART_RX5_BUF[2]==0x21&&BJDJ==0)
//		{
//						BJDJ=1;
//						create_t_ctrl_param4(2400,30,30,80);//鞋架转动
//						create_t_ctrl_param1(-32000,30,30,120);//上下机构   负数上升32000/3200   10圈
//		}
//		if(USART_RX5_BUF[2]==0x21&&BJDJ==1)
//		{
//						BJDJ=2;
//						create_t_ctrl_param3(90000,30,30,120);//伸出机构   正数伸出90000/3200   
//		}	
//		if(USART_RX5_BUF[2]==0x21&&BJDJ==2)
//		{
//						BJDJ=3;
//						create_t_ctrl_param1(32000,30,30,120); 
//		}
//	}
//	
//void contorl_XIEZI_Songhui()
//	{
//		if(USART_RX5_BUF[3]==0x20&&BJDJ1==0)
//						{
//								BJDJ1=1;
//								create_t_ctrl_param1(32000,30,30,120);//上下机构   负数上升32000/3200   10圈
//							
//											if(BJDJ1==1)
//											{
//															BJDJ1=2;
//															create_t_ctrl_param3(-90000,30,30,120);//伸回去   负数回去90000/3200   
//											}
//															
//											if(BJDJ1==2)
//											{
//															BJDJ1=3;
//															create_t_ctrl_param1(32000,30,30,120);//下降 
//											}
//											
//											if(BJDJ1==3)
//											{
//															BJDJ1=4;
//															create_t_ctrl_param4(4800,30,30,120);//转动
//											}
//						}
//	}
