#include "key.h"
#include "delay.h" 
#include "oled.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK STM32F407¿ª·¢°å
//°´¼üÊäÈëÇı¶¯´úÂë	   
//ÕıµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//´´½¨ÈÕÆÚ:2014/5/3
//°æ±¾£ºV1.0
//°æÈ¨ËùÓĞ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//*********************************************************************************°´¼üÊ¾Àı³ÌĞò*********************************************************************************************ò//
//	   OLED_ShowString(16,4,"LED_TEST",12);
//	   OLED_Refresh_Gram();//¸üĞÂÏÔÊ¾µ½OLED	
//		key=KEY_Scan(0);	//µÃµ½¼üÖµ
//		if(key)
//		{						   
//			switch(key)
//			{				 
//							case KEY1_PRES:									
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 delay_ms(100);							
//							break;
//						 
//						 case KEY2_PRES:	
//						  LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 delay_ms(100);
//						 break;
//						 
//						 case KEY3_PRES:	
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	  
//						 delay_ms(100);
//						 break;
//						 
//						 case KEY4_PRES:	
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 delay_ms(100);
//							break;
//						 
//						 case KEY5_PRES:	
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 	delay_ms(100);
//							break;
//						 
//						 case KEY6_PRES:	
//							LED1=!LED1;
//							LED2=!LED2;
//							LED3=!LED3;	
//						 delay_ms(100);
//							break;
//						 
//			}
//			}

//extern  int Res_2;
//extern int key;
//int Mod=0;
//void mode_set(void)
//{

//while(1)	
//	{ 

//		if(Res_2=='a')
//		{
//		  OLED_ShowCHinese( 16, 0,0);//µ÷ÊÔ
//		OLED_ShowCHinese( 32, 0,1);
//		OLED_ShowNum(48,16,1,3,16);			
//		OLED_Refresh_Gram();	
//			Mod=1;
//			Res_2='z';
//		}
//		if(Res_2=='b')
//		{
//		  OLED_ShowCHinese( 16, 0,0);//µ÷ÊÔ
//		OLED_ShowCHinese( 32, 0,1);
//		OLED_ShowNum(48,16,2,3,16);			
//		OLED_Refresh_Gram();	
//				Mod=2;
//			Res_2='z';
//		}
//	  if(Res_2=='c')
//		{
//		  OLED_ShowCHinese( 16, 0,0);//µ÷ÊÔ
//		OLED_ShowCHinese( 32, 0,1);
//		OLED_ShowNum(48,16,3,3,16);			
//		OLED_Refresh_Gram();
//	Mod=3;			
//			Res_2='z';
//		}
//		if(Res_2=='d')
//		{
//		 OLED_ShowCHinese( 16, 0,0);//µ÷ÊÔ
//		OLED_ShowCHinese( 32, 0,1);
//		OLED_ShowNum(48,16,4,3,16);			
//		OLED_Refresh_Gram();
//	Mod=4;			
//			Res_2='z';
//		}
//	  if(Res_2=='e')
//		{
//    OLED_ShowCHinese( 16,16,2);//»ù´¡²¿·Ö
//		OLED_ShowCHinese( 32,16,3);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//		OLED_ShowNum(80,16,1,3,16);			
//		OLED_Refresh_Gram();
//				Mod=5;
//			Res_2='z';
//		}
//		if(Res_2=='f')
//		{
//		  OLED_ShowCHinese( 16,16,2);//»ù´¡²¿·Ö
//		OLED_ShowCHinese( 32,16,3);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//		OLED_ShowNum(80,16,2,3,16);	
//OLED_Refresh_Gram();
//	Mod=6;			
//			Res_2='z';
//		}
//	  if(Res_2=='g')
//		{
//		  OLED_ShowCHinese( 16,16,2);//»ù´¡²¿·Ö
//		OLED_ShowCHinese( 32,16,3);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//		OLED_ShowNum(80,16,3,3,16);	
//OLED_Refresh_Gram();
//	Mod=7;			
//			Res_2='z';
//		}
//		if(Res_2=='h')
//		{
//		  OLED_ShowCHinese( 16,16,2);//»ù´¡²¿·Ö
//		OLED_ShowCHinese( 32,16,3);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//		OLED_ShowNum(80,16,4,3,16);
//OLED_Refresh_Gram();			
//				Mod=8;
//			Res_2='z';
//		}
//		if(Res_2=='i')
//		{
//		  OLED_ShowCHinese( 16,16,4);//·¢»Ó²¿·Ö
//		OLED_ShowCHinese( 32,16,5);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//			OLED_ShowNum(80,16,1,3,16);
//OLED_Refresh_Gram();			
//				Mod=9;
//			Res_2='z';
//		}
//		if(Res_2=='j')
//		{
//		 		  OLED_ShowCHinese( 16,16,4);//·¢»Ó²¿·Ö
//		OLED_ShowCHinese( 32,16,5);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//			OLED_ShowNum(80,16,2,3,16);
//OLED_Refresh_Gram();
//	Mod=10;			
//			Res_2='z';
//		}
//	  if(Res_2=='k')
//		{
//		  		  OLED_ShowCHinese( 16,16,4);//·¢»Ó²¿·Ö
//		OLED_ShowCHinese( 32,16,5);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//			OLED_ShowNum(80,16,3,3,16);
//OLED_Refresh_Gram();
//	Mod=11;			
//			Res_2='z';
//		}
//		if(Res_2=='l')
//		{
//				  OLED_ShowCHinese( 16,16,4);//·¢»Ó²¿·Ö
//		OLED_ShowCHinese( 32,16,5);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//			OLED_ShowNum(80,16,4,3,16);
//OLED_Refresh_Gram();
//	Mod=12;			
//			Res_2='z';
//		}
//		if(Res_2=='m')
//		{
//		OLED_ShowCHinese( 16,16,6);//ÍØÕ¹²¿·Ö
//		OLED_ShowCHinese( 32,16,7);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//			OLED_ShowNum(80,16,1,3,16);
//OLED_Refresh_Gram();
//	Mod=13;			
//			Res_2='z';
//		}
//		if(Res_2=='n')
//		{
//		 OLED_ShowCHinese( 16,16,6);//ÍØÕ¹²¿·Ö
//		OLED_ShowCHinese( 32,16,7);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//			OLED_ShowNum(80,16,2,3,16);
//OLED_Refresh_Gram();
//	Mod=14;			
//			Res_2='z';
//		}
//	  if(Res_2=='o')
//		{
//		 OLED_ShowCHinese( 16,16,6);//ÍØÕ¹²¿·Ö
//		OLED_ShowCHinese( 32,16,7);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//			OLED_ShowNum(80,16,3,3,16);
//OLED_Refresh_Gram();
//	Mod=15	;		
//			Res_2='z';
//		}
//		if(Res_2=='p')
//		{
//		OLED_ShowCHinese( 16,16,6);//ÍØÕ¹²¿·Ö
//		OLED_ShowCHinese( 32,16,7);
//		OLED_ShowCHinese( 48,16,8);
//		OLED_ShowCHinese( 64,16,9);
//			OLED_ShowNum(80,16,4,3,16);
//OLED_Refresh_Gram();		  
//				Mod=16;
//			Res_2='z';
//		}
//	key=KEY_Scan(0);	//µÃµ½¼üÖµ	
//		if(key==KEY6_PRES)
//			{	  
//				break;
//			}	
//		
//	}

//OLED_Clear( );


//}







//°´¼ü³õÊ¼»¯º¯Êı
void KEY_Init(void)
{
	
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}
//°´¼ü´¦Àíº¯Êı
//·µ»Ø°´¼üÖµ
//mode:0,²»Ö§³ÖÁ¬Ğø°´;1,Ö§³ÖÁ¬Ğø°´;
//0£¬Ã»ÓĞÈÎºÎ°´¼ü°´ÏÂ
//1£¬KEY0°´ÏÂ
//2£¬KEY1°´ÏÂ
//3£¬KEY2°´ÏÂ 
//4£¬WKUP°´ÏÂ WK_UP
//×¢Òâ´Ëº¯ÊıÓĞÏìÓ¦ÓÅÏÈ¼¶,KEY0>KEY1>KEY2>WK_UP!!

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//°´¼ü°´ËÉ¿ª±êÖ¾
	if(mode)key_up=1;  //Ö§³ÖÁ¬°´		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0))
	{
		delay_ms(10);//È¥¶¶¶¯ 
		key_up=0;
		if(KEY1==0)return 1;
		else if(KEY2==0)return 2;
		else if(KEY3==0)return 3;
		else if(KEY4==0)return 4;
		else if(KEY5==0)return 5;
		else if(KEY6==0)return 6;
		
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1&&KEY6==1)key_up=1; 	    
 	return 0;// ÎŞ°´¼ü°´ÏÂ
}
