#include "sys.h"
#include "usart.h"	
#include "delay.h"	
#include "oled.h"	
////////////////////////////////////////////////////////////////////////////////// 	 
//Èç¹ûÊ¹ÓÃucos,Ôò°üÀ¨ÏÂÃæµÄÍ·ÎÄ¼þ¼´¿É.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos Ê¹ÓÃ	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK STM32F4Ì½Ë÷Õß¿ª·¢°å
//´®¿Ú1³õÊ¼»¯		   
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ÐÞ¸ÄÈÕÆÚ:2014/6/10
//°æ±¾£ºV1.5
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3ÐÞ¸ÄËµÃ÷ 
//Ö§³ÖÊÊÓ¦²»Í¬ÆµÂÊÏÂµÄ´®¿Ú²¨ÌØÂÊÉèÖÃ.
//¼ÓÈëÁË¶ÔprintfµÄÖ§³Ö
//Ôö¼ÓÁË´®¿Ú½ÓÊÕÃüÁî¹¦ÄÜ.
//ÐÞÕýÁËprintfµÚÒ»¸ö×Ö·û¶ªÊ§µÄbug
//V1.4ÐÞ¸ÄËµÃ÷
//1,ÐÞ¸Ä´®¿Ú³õÊ¼»¯IOµÄbug
//2,ÐÞ¸ÄÁËUSART_RX_STA,Ê¹µÃ´®¿Ú×î´ó½ÓÊÕ×Ö½ÚÊýÎª2µÄ14´Î·½
//3,Ôö¼ÓÁËUSART_REC_LEN,ÓÃÓÚ¶¨Òå´®¿Ú×î´óÔÊÐí½ÓÊÕµÄ×Ö½ÚÊý(²»´óÓÚ2µÄ14´Î·½)
//4,ÐÞ¸ÄÁËEN_USART1_RXµÄÊ¹ÄÜ·½Ê½
//V1.5ÐÞ¸ÄËµÃ÷
//1,Ôö¼ÓÁË¶ÔUCOSIIµÄÖ§³Ö
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//¼ÓÈëÒÔÏÂ´úÂë,Ö§³Öprintfº¯Êý,¶ø²»ÐèÒªÑ¡Ôñuse MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//±ê×¼¿âÐèÒªµÄÖ§³Öº¯Êý                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//¶¨Òå_sys_exit()ÒÔ±ÜÃâÊ¹ÓÃ°ëÖ÷»úÄ£Ê½    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//ÖØ¶¨Òåfputcº¯Êý 
//int fputc(int ch, FILE *f)
//{ 	
//	while((USART1->SR&0X40)==0);//Ñ­»··¢ËÍ,Ö±µ½·¢ËÍÍê±Ï   
//	USART1->DR = (u8) ch;      
//	return ch;
//}
#endif
 
 
/*********************ÑÕÉ«Ê¶±ð*/////////////////
//1------ºìÉ«
//2------ÂÌÉ«
//3------À¶É«

//É¨ÂëÄ£¿é   xxx+xxx  ÏÈÉÏºóÏÂ
//openmv     xxx+xxx  ÏÈÉÏºóÏÂ

int sss=0;
int openmv_site=0;
int color_flag=0;
char SendData[8];
char SendData1[8];
char SendData2[8];
u8 saoma[9];
u8 shibie[9];
u8 flag;
u8 flag2=0;
u16 he1;//É¨ÂëÄ£¿é
u16 he2;//É¨ÂëÄ£¿é
u16 he3;//ÑÕÉ«Ê¶±ð
u16 he4;//ÑÕÉ«Ê¶±ð
int guocheng=1;
int color_site=0;

extern int llll;
int xerror[10];
int yerror[10];
#if EN_USART1_RX   //Èç¹ûÊ¹ÄÜÁË½ÓÊÕ
//´®¿Ú1ÖÐ¶Ï·þÎñ³ÌÐò
//×¢Òâ,¶ÁÈ¡USARTx->SRÄÜ±ÜÃâÄªÃûÆäÃîµÄ´íÎó   	
u8 USART_RX_BUF[USART_REC_LEN];     //½ÓÊÕ»º³å,×î´óUSART_REC_LEN¸ö×Ö½Ú.
//½ÓÊÕ×´Ì¬
//bit15£¬	½ÓÊÕÍê³É±êÖ¾
//bit14£¬	½ÓÊÕµ½0x0d
//bit13~0£¬	½ÓÊÕµ½µÄÓÐÐ§×Ö½ÚÊýÄ¿
u16 USART_RX_STA=0;       //½ÓÊÕ×´Ì¬±ê¼Ç	

//³õÊ¼»¯IO ´®¿Ú1 
//bound:²¨ÌØÂÊ
/***********************************************************************************ÉÏÎ»»ú*//////////////////////////////////////////////////////////////////////////////////////////////////////

//// p+=0.1;
////		 	if(p>3.14)  p=-3.14; 
////			DataScope_Get_Channel_Data(500*sin(p), 1 );
////			DataScope_Get_Channel_Data(500* tan(p), 2 );
////			DataScope_Get_Channel_Data( 500*cos(p), 3 ); 
////			DataScope_Get_Channel_Data( 100*p , 4 );   
////			DataScope_Get_Channel_Data(0, 5 );
////			DataScope_Get_Channel_Data(0 , 6 );
////			DataScope_Get_Channel_Data(0, 7 );
////			DataScope_Get_Channel_Data( 0, 8 ); 
////			DataScope_Get_Channel_Data(0, 9 );  
////			DataScope_Get_Channel_Data( 0 , 10);
////			Send_Count = DataScope_Data_Generate(10);
////			for( i = 0 ; i < Send_Count; i++) 
////			{
////			while((USART3->SR&0X40)==0);  
////			USART3->DR = DataScope_OutPut_Buffer[i]; 
////			}
////			delay_ms(50); //20HZ

//unsigned char DataScope_OutPut_Buffer[42] = {0};	   //´®¿Ú·¢ËÍ»º³åÇø
//void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
//{
//    unsigned char *point;
//    point = (unsigned char*)target;	  //µÃµ½floatµÄµØÖ·
//    buf[beg]   = point[0];
//    buf[beg+1] = point[1];
//    buf[beg+2] = point[2];
//    buf[beg+3] = point[3];
//}

//void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
//{
//	if ( (Channel > 10) || (Channel == 0) ) return;  //Í¨µÀ¸öÊý´óÓÚ10»òµÈÓÚ0£¬Ö±½ÓÌø³ö£¬²»Ö´ÐÐº¯Êý
//  else
//  {
//     switch (Channel)
//		{
//      case 1:  Float2Byte(&Data,DataScope_OutPut_Buffer,1); break;
//      case 2:  Float2Byte(&Data,DataScope_OutPut_Buffer,5); break;
//		  case 3:  Float2Byte(&Data,DataScope_OutPut_Buffer,9); break;
//		  case 4:  Float2Byte(&Data,DataScope_OutPut_Buffer,13); break;
//		  case 5:  Float2Byte(&Data,DataScope_OutPut_Buffer,17); break;
//		  case 6:  Float2Byte(&Data,DataScope_OutPut_Buffer,21); break;
//		  case 7:  Float2Byte(&Data,DataScope_OutPut_Buffer,25); break;
//		  case 8:  Float2Byte(&Data,DataScope_OutPut_Buffer,29); break;
//		  case 9:  Float2Byte(&Data,DataScope_OutPut_Buffer,33); break;
//		  case 10: Float2Byte(&Data,DataScope_OutPut_Buffer,37); break;
//		}
//  }	 
//}


////º¯ÊýËµÃ÷£ºÉú³É DataScopeV1.0 ÄÜÕýÈ·Ê¶±ðµÄÖ¡¸ñÊ½
////Channel_Number£¬ÐèÒª·¢ËÍµÄÍ¨µÀ¸öÊý
////·µ»Ø·¢ËÍ»º³åÇøÊý¾Ý¸öÊý
////·µ»Ø0±íÊ¾Ö¡¸ñÊ½Éú³ÉÊ§°Ü 
//unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
//{
//	if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //Í¨µÀ¸öÊý´óÓÚ10»òµÈÓÚ0£¬Ö±½ÓÌø³ö£¬²»Ö´ÐÐº¯Êý
//  else
//  {	
//	 DataScope_OutPut_Buffer[0] = '$';  //Ö¡Í·
//		
//	 switch(Channel_Number)   
//   { 
//		 case 1:   DataScope_OutPut_Buffer[5]  =  5; return  6;  
//		 case 2:   DataScope_OutPut_Buffer[9]  =  9; return 10;
//		 case 3:   DataScope_OutPut_Buffer[13] = 13; return 14; 
//		 case 4:   DataScope_OutPut_Buffer[17] = 17; return 18;
//		 case 5:   DataScope_OutPut_Buffer[21] = 21; return 22;  
//		 case 6:   DataScope_OutPut_Buffer[25] = 25; return 26;
//		 case 7:   DataScope_OutPut_Buffer[29] = 29; return 30; 
//		 case 8:   DataScope_OutPut_Buffer[33] = 33; return 34; 
//		 case 9:   DataScope_OutPut_Buffer[37] = 37; return 38;
//     case 10:  DataScope_OutPut_Buffer[41] = 41; return 42; 
//   }	 
//  }
//	return 0;
//}
/***********************************************************************************ÉÏÎ»»ú*//////////////////////////////////////////////////////////////////////////////////////////////////////

//void uart_init(u32 bound){
//   //GPIO¶Ë¿ÚÉèÖÃ
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //Ê¹ÄÜGPIOAÊ±ÖÓ
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//Ê¹ÄÜUSART1Ê±ÖÓ
// 
//	//´®¿Ú1¶ÔÓ¦Òý½Å¸´ÓÃÓ³Éä
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9¸´ÓÃÎªUSART1
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10¸´ÓÃÎªUSART1
//	
//	//USART1¶Ë¿ÚÅäÖÃ
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9ÓëGPIOA10
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//¸´ÓÃ¹¦ÄÜ
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//ËÙ¶È50MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //ÍÆÍì¸´ÓÃÊä³ö
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //ÉÏÀ­
//	GPIO_Init(GPIOA,&GPIO_InitStructure); //³õÊ¼»¯PA9£¬PA10

//   //USART1 ³õÊ¼»¯ÉèÖÃ
//	USART_InitStructure.USART_BaudRate = bound;//²¨ÌØÂÊÉèÖÃ
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//×Ö³¤Îª8Î»Êý¾Ý¸ñÊ½
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//Ò»¸öÍ£Ö¹Î»
//	USART_InitStructure.USART_Parity = USART_Parity_No;//ÎÞÆæÅ¼Ð£ÑéÎ»
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ÎÞÓ²¼þÊý¾ÝÁ÷¿ØÖÆ
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ÊÕ·¢Ä£Ê½
//  USART_Init(USART1, &USART_InitStructure); //³õÊ¼»¯´®¿Ú1
//	
//  USART_Cmd(USART1, ENABLE);  //Ê¹ÄÜ´®¿Ú1 
//	
//	USART_ClearFlag(USART1, USART_FLAG_TC);
//	
//#if EN_USART1_RX	
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//¿ªÆôÏà¹ØÖÐ¶Ï

//	//Usart1 NVIC ÅäÖÃ
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//´®¿Ú1ÖÐ¶ÏÍ¨µÀ
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//ÇÀÕ¼ÓÅÏÈ¼¶3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//×ÓÓÅÏÈ¼¶3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍ¨µÀÊ¹ÄÜ
//	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷¡¢

//#endif
//	
//}
#endif	

//void USART1_IRQHandler(void)                	//´®¿Ú1ÖÐ¶Ï·þÎñ³ÌÐò
//	{
//	int16_t Res;
//	static u8 state = 0;	
//	static u8 bit_number=0;
//  u8 i;	
//	static u16 openmv[9];	//´æÈ¡Êý¾Ý
//	

//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶Ï
//		{ USART_ClearFlag(USART1, USART_FLAG_TC); 
//			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//		  Res=USART_ReceiveData(USART1);	//¶ÁÈ¡½ÓÊÕµ½µÄÊý¾Ý
//				
//	GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_3);//GPIOF9,F10ÉèÖÃ¸ß£¬µÆÃð

//			//USART_SendData(USART3,Res);//»Ø´«½ÓÊÕµ½µÄÊý¾Ý		
//	//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET)
//		//	Delay_ms(100);		
//if((state==0)&&(Res==0xb3))  
//	{	
//		state=1;
//		openmv[bit_number++]=Res;
//	}

//	else if(state==1)
//	{
//		openmv[1]=Res;
//			
//		 state=2;
//	}
//	else if(state==2)
//	{ 
//		openmv[2]=Res;

//		state=3;
//	}
//	else if(state==3)
//	{ 
//		openmv[3]=Res;
//				
//		state=4;
//	}
//	
//	else if(state==4)
//	{
//		openmv[4]=Res;
//		
//		 state=5;
//	}
//	else if(state==5)
//	{ 
//		openmv[5]=Res;
//			
//		state=6;
//	}
//	else if(state==6)
//	{ 
//		openmv[6]=Res;
//	          OLED_ShowNum(40,12,openmv[1],4,12);
//						OLED_ShowNum(40,24,openmv[2],4,12);
//						OLED_ShowNum(40,36,openmv[3],4,12);
//						OLED_ShowNum(40,48,openmv[4],4,12);
//						OLED_ShowNum(80,12,openmv[5],4,12);
//						OLED_Refresh_Gram();
//		state=7;
//	}
//					else if(state==7)		//¼ì²âÊÇ·ñ½ÓÊÜµ½½áÊø±êÖ¾
//	      {
//        	if(Res == 0x5b)
//        	{	

//						state = 0;
//            		openmv[7]=Res;
//        	}
//        	else if(Res != 0x5b)
//        	{
//           		 state = 0;
//            		for(i=0;i<8;i++)
//            		{
//               			 openmv[i]=0x00;
//            		}           
//        	}
//				}
//						

//				USART_RX_STA=0;
//		}}


	void uart_init2(u32 bound){
   //GPIO¶Ë¿ÚÉèÖÃ
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //Ê¹ÄÜGPIOAÊ±ÖÓ
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 ,ENABLE);//Ê¹ÄÜUSART1Ê±ÖÓ
 
	//´®¿Ú1¶ÔÓ¦Òý½Å¸´ÓÃÓ³Éä
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA9¸´ÓÃÎªUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA10¸´ÓÃÎªUSART1
	
	//USART1¶Ë¿ÚÅäÖÃ
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA9ÓëGPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//ËÙ¶È50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //ÉÏÀ­
	GPIO_Init(GPIOA,&GPIO_InitStructure); //³õÊ¼»¯PA9£¬PA10

   //USART1 ³õÊ¼»¯ÉèÖÃ
	USART_InitStructure.USART_BaudRate = bound;//²¨ÌØÂÊÉèÖÃ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//×Ö³¤Îª8Î»Êý¾Ý¸ñÊ½
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//Ò»¸öÍ£Ö¹Î»
	USART_InitStructure.USART_Parity = USART_Parity_No;//ÎÞÆæÅ¼Ð£ÑéÎ»
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ÎÞÓ²¼þÊý¾ÝÁ÷¿ØÖÆ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ÊÕ·¢Ä£Ê½
  USART_Init(USART2, &USART_InitStructure); //³õÊ¼»¯´®¿Ú1
	
  USART_Cmd(USART2, ENABLE);  //Ê¹ÄÜ´®¿Ú1 
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
	

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//¿ªÆôÏà¹ØÖÐ¶Ï

	//Usart1 NVIC ÅäÖÃ
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//´®¿Ú1ÖÐ¶ÏÍ¨µÀ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//ÇÀÕ¼ÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//×ÓÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍ¨µÀÊ¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷¡¢

}

//unsigned char ReceiveData;    //½ÓÊÜ´æ´¢±äÁ¿
//int16_t Res;
//int16_t Res_1;
//extern u16 openmv2[9];
//void USART2_IRQHandler(void)                	//´®¿Ú1ÖÐ¶Ï·þÎñ³ÌÐò
//	{
//	int16_t Res;
//	static u8 state = 0;	
//	static u8 bit_number=0;
//  u8 i;	
//			int t;
//	static uint8_t Uart2_Rec_Len = 0;
//	static u16 hmi_num[6];	//´æÈ¡Êý¾
//	static u16 openmv[9];	//´æÈ¡Êý¾Ý
//	

//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //½ÓÊÕÖÐ¶Ï
//		{ USART_ClearFlag(USART2, USART_FLAG_TC); 
//			USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//		  Res=USART_ReceiveData(USART2);	//¶ÁÈ¡½ÓÊÕµ½µÄÊý¾Ý
//				USART_SendData(USART2,Res);
//	GPIO_ResetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_3);//GPIOF9,F10ÉèÖÃ¸ß£¬µÆÃð
//if(state==0&&Res==0x01)
//	
//	{		hmi_num[0]=Res; 
//		state=1;
//	
//		
//	}

//	else if(state==1)
//	{
//		hmi_num[1]=Res;	
//		openmv2[1]=hmi_num[1];
//		state=2;	
//	}
//	else if(state==2)
//	{ 
//		hmi_num[2]=Res;	
//		openmv2[2]=hmi_num[2];
//		 state=3;
//	}
//		else if(state==3)
//	{ 
//		hmi_num[3]=Res;	
//		openmv2[3]=hmi_num[3];
//		 state=4;
//	}
//			else if(state==4)
//	{ 
//		hmi_num[4]=Res;	
//		openmv2[4]=hmi_num[4];
//		 state=5;
//	}
//	else if(state==5)
//	{
//		hmi_num[5]=Res;	
//		openmv2[5]=hmi_num[5];
//		state=6;	
//	}
//	else if(state==6)
//	{ 
//		hmi_num[6]=Res;	
//		openmv2[6]=hmi_num[6];
//		 state=7;
//	}
//		else if(state==7)
//	{ 
//		hmi_num[7]=Res;	
//		openmv2[7]=hmi_num[7];
//		 state=8;
//	}
//			else if(state==8)
//	{ 
//		hmi_num[8]=Res;	
//		openmv2[8]=hmi_num[8];
//		 state=9;
//	}
//	else if(state==9)
//	{ 
//        	if(Res == 0x02)
//        	{	

//						state = 0;
//							for(i=0;i<10;i++)
//            		{
//               			 hmi_num[i]=0x00;
//            		}     
////            hmi_num[2]=Res;
//        	}
//        	else if(Res!= 0x02)
//        	{
//           		 state = 0;
//            		for(i=0;i<10;i++)
//            		{
//               			 hmi_num[i]=0x00;
//            		}           
//        	}
//				}
//						

//						

//				USART_RX_STA=0;
//		}}


//void HMISendstart(void)
//{
//	 	delay_ms(200);
//		HMISendb(0xff);
//		delay_ms(200);
//}
//void HMISends(char *buf1)		  //×Ö·û´®·¢ËÍº¯Êý
//{
//	 u8 i=0;
//	 while(1)
//	{
//	    if(buf1[i]!=0)
//	 	 {
//			   USART_SendData(USART2,buf1[i]);  //·¢ËÍÒ»¸ö×Ö½Ú
//			   while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//µÈ´ý·¢ËÍ½áÊø
//		   	 i++;
//		 }
//	    else 
//	       return ;
//	}
//}
//void HMISendb(u8 k)		         //×Ö½Ú·¢ËÍº¯Êý
//{		 
//	  u8 i;
//	  for(i=0;i<3;i++)
//	 {
//	     if(k!=0)
//	 	  {
//			    USART_SendData(USART2,k);  //·¢ËÍÒ»¸ö×Ö½Ú
//			    while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//µÈ´ý·¢ËÍ½áÊø
//		  }
//	     else 
//	        return ;
//	 } 
//} 


