实验器材:
	探索者STM32F4开发板
	
实验目的:
	学习MPU9250 九轴传感器(三轴加速度+三轴陀螺仪+三轴磁力计)的使用.
	
硬件资源:
	1,DS0(连接在PF9)
	2,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面)
	3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过FSMC驱动,FSMC_NE4接LCD片选/A6接RS)
	4,MPU9250传感器(连接在PB6(SCL),PB7(SDA)上面).

实验现象:
	本实验开机后，先初始化MPU9250，然后利用MPL库，初始化MPU9250及使能DMP，最后，在死循环里面不停
	读取：温度传感器、加速度传感器、陀螺仪、DMP姿态解算后的欧拉角等数据。并在LCD模块上面显示采集
	到的信息。DS0来指示程序正在运行。
	
	


//				temp=yaw*10;
//			  if(temp<0)
//				{
////					OLED_ShowString(45,30,"-",12);		
////					 OLED_Refresh_Gram();
//					temp=-temp;		//转为正数
//				}
//       else 
//				OLED_ShowString(35,30," ",12);	
//					
//				  OLED_ShowNum(60,30,temp/10,3 ,12);	
//			  
//				  OLED_ShowNum(80,30,temp%10,3 ,12);	
//				  OLED_Refresh_Gram();



//		if(MS6==6) 
//		{
//		     GPIO_ResetBits(GPIOE,GPIO_Pin_6) ;//复位F9 点亮D1
//		
//					if(mpu_mpl_get_data(&pitch,&roll,&yaw)==0)
//		{	
//			    temp=MPU_Get_Temperature();	//得到温度值
//			    MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
//		     	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
//				temp=yaw*10;
//			  if(temp<0)
//				{
//					OLED_ShowString(45,30,"-",12);		
//					 OLED_Refresh_Gram();
//					temp=-temp;		//转为正数
//				}
//        else OLED_ShowString(35,30," ",12);	
//					
//				  OLED_ShowNum(60,30,temp/10,3 ,12);	
//			  
//				  OLED_ShowNum(80,30,temp%10,3 ,12);	
//				  OLED_Refresh_Gram();
//				  

//				speed_angle = PID_Control(&PID_Inner,Expectation_Angle,yaw);
//      
//        MS6=0;  
//		}	 
//			} 
					
					
	


		
void EXTI15_10_IRQHandler(void)
{
	static int flag2=0;
	
	if(flag2==1)
	{
	 GEZI=0;
	 GPIO_ResetBits(GPIOE,GPIO_Pin_3) ;//复位F9 点亮D1		 
	}
	if(flag2==3)
	{
	 GEZI=1;
	 GPIO_ResetBits(GPIOE,GPIO_Pin_5) ;//复位F9 点亮D1
	    		
	}
	if(flag2==5)
	{
	 GEZI=2;
	 GPIO_ResetBits(GPIOE,GPIO_Pin_6) ;//复位F9 点亮D1
	   		
	}
	 flag2++;

	 EXTI_ClearITPendingBit(EXTI_Line14); //清除LINE0上的中断标志位 
}	
	

//void EXTI9_5_IRQHandler(void)
//{
//	
//    
//	 EXTI_ClearITPendingBit(EXTI_Line9); //清除LINE0上的中断标志位 
//}	

//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX1_Init(FunctionalState NewState)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
//	KEY_Init(); //按键对应的IO口初始化
  XUNJI_Front_GPIO_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource14);//PA0 连接到中断线0

	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置

}


//void EXTIX2_Init(FunctionalState NewState)
//{
//	NVIC_InitTypeDef   NVIC_InitStructure;
//	EXTI_InitTypeDef   EXTI_InitStructure;
//	GPIO_InitTypeDef  GPIO_InitStructure;
//  XUNJI_Front_GPIO_Init();
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PA0 连接到中断线0
// 
//	/* 配置EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
//  EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
//  EXTI_Init(&EXTI_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
//}


			
					
					
					
					
					