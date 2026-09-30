//#include "oled.h"
//#include "stm32f4xx_gpio.h"
//#include "motor.h"
//#include "pid.h"
//#include "motor.h"
//#include "stm32f4xx_gpio.h"
//#include "photoelectric.h"
//#include "duoji.h"
//#include "control.h"
//#include "delay.h"
//#include "pid.h"
//#include "usart2dma.h"
//#include "tim6_delay.h"
//#include "dianji.h"
//#include "usartdma.h"
//#include "led.h"
//#include "usart5dma.h"
//extern int car_state;
//extern uint64_t long_distance;
//extern float yaw;
//extern uint16_t delay_TIM7;
//extern uint8_t g_motion_sta1,g_motion_sta2,g_motion_sta,g_motion_sta4;
//extern u16 distance;
//extern float speed_yaw;
//extern uint16_t distance_left;
//extern uint16_t distance_right;
//uint8_t flag_xiuzheng=0;
//void left_home(void)//离家
//{
//    usart5_board_senddata(0);
//    usart5_board_senddata(0);
//    usart5_board_senddata(0);
//    PID_Init(&left_home_sonic,0.5f,0.0f,0.0f);//离开家超声波
////    PID_Init(&left_home_sonic,0.7f,0.0f,2.0f);//离开家超声波
//   // PID_Init(&left_home_yaw,2.0f,0.0f,0.0f);//陀螺仪
//    usart_steer_senddata(steer1_init,steer2_init,steer3_init,steer4_init,0);//舵机初始化
////    usart_steer_senddata(steer1_long,steer2_long,steer3_long,steer4_long,0);
//	control_speed1(350,0);//四个电机速度
//	control_speed2(350,0);
//	control_speed3(-350,0);
//	control_speed4(-350,0);

//    PID_Init(&left_home_yaw,0.0f,0.0f,0.0f);
//    car_state=1;
//    while(1)//先给350小速度，long_distance>=1000后切到speed=1200的大速度
//    {
//        if(long_distance>=6000)
//            break;
//    }
//    PID_Init(&left_home_yaw,1.5f,0.0f,0.0f);
////		  PID_Init(&left_home_yaw,1.5f,0.0f,0.0f);
//   control_speed1(1200,0);
//	 control_speed2(1200,0);
//	control_speed3(-1200,0);
//	control_speed4(-1200,0);
////    usart_steer_senddata(steer1_init,steer2_init,steer3_init,steer4_init,0);
//	car_state=1;
//	long_distance=0;
//	while(1)
//	{
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//		if(long_distance>=8500)//两个超声波已经全部入陇，可以利用超声波跑直线
//		{
//		car_state=2;
//	control_speed1(1600,0);
//	control_speed2(1600,0);
//	control_speed3(-1600,0);
//	control_speed4(-1600,0);
//		break;
//		}
//	}
//	  PID_Init(&left_home_yaw,1.5f,0.0f,0.0f);///////////////////////////////////////
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance<1000)
//        {
//            control_speed1(1400,0);
//	        control_speed2(1400,0);
//	        control_speed3(-1400,0);
//	        control_speed4(-1400,0);
//            break;//前侧光电管照到边，减速停车
//        }
//    }
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance<600)
//        {
//					control_speed1(500,0);
//	        control_speed2(500,0);
//	        control_speed3(-500,0);
//	        control_speed4(-500,0);
//            break;//前侧光电管照到边，减速停车
//        }
//    }
//    PID_Init(&left_home_sonic,1.5f,0.0f,0.0f);//离开家超声波
//    PID_Init(&left_home_yaw,8.5f,0.0f,10.0f);
//    
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance<140)
//        {
//          control_speed1(0,1);
//	        control_speed2(0,1);
//	        control_speed3(0,1);
//	        control_speed4(0,1);
//            break;
//        }
//    }
//    car_state=0;
//	
//}

//void decel_motor_speed(double speed,uint64_t longdistance)//减速
//{
//    double speed_adjust;
//    speed_adjust=800-distance ;//(speed-300)/(distance -300);
//    long_distance=0;
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        control_speed1(speed-speed_adjust,0);
//        control_speed2(speed-speed_adjust,0);
//	    control_speed3(-(speed-speed_adjust),0);
//	    control_speed4(-(speed-speed_adjust),0);
//        if(distance <=300)
//        {
//            break;
//        }
//    }
//    control_speed1(300,0);
//    control_speed2(300,0);
//	control_speed3(-300,0);
//	control_speed4(-300,0);
//    
//}
//void decel_motor_speed_long(double speed,uint64_t longdistance)//减速
//{
//    double speed_adjust;
//    speed_adjust=(speed-250)/longdistance;
//    long_distance=0;
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        control_speed1(speed-speed_adjust*long_distance,0);
//        control_speed2(-(speed-speed_adjust*long_distance),0);
//	    control_speed3(-(speed-speed_adjust*long_distance),0);
//	    control_speed4(speed-speed_adjust*long_distance,0);
//        if(long_distance>=longdistance)
//        {
//            break;
//        }
//    }
//    control_speed1(500,0);
//    control_speed2(-500,0);
//	control_speed3(-500,0);
//	control_speed4(500,0);
//    
//}
//void decel_motor_speed_long_left(double speed,uint64_t longdistance)//减速
//{
//    double speed_adjust;
//    speed_adjust=(speed-250)/longdistance;
//    long_distance=0;
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        control_speed1(-(speed-speed_adjust*long_distance),0);
//        control_speed2(speed-speed_adjust*long_distance,0);
//	    control_speed3(speed-speed_adjust*long_distance,0);
//	    control_speed4(-(speed-speed_adjust*long_distance),0);
//        if(long_distance>=longdistance)
//        {
//            break;
//        }
//    }
//    control_speed1(-400,0);
//    control_speed2(400,0);
//    control_speed3(400,0);
//    control_speed4(-400,0);
//    
//}
//void correct_car(void)
//{
//    delay_TIM7=0;
//    while(delay_TIM7<=350)//大于300毫秒或者车身动伏较大直接进行修正
//    {
//			   control_speed1(10*yaw,0);
//         control_speed2(10*yaw,0);
//         control_speed3(10*yaw,0);
//         control_speed4(10*yaw,0);
//        if(yaw>2.5&&yaw<-2.5)
//            break;
//    }
//    if(yaw<2.5&&yaw>-2.5)
//    {
//        goto nojudge;
//    }
//    LED2=!LED2;
//    while(1)//用于车身修正
//    {
//        if(yaw<=8||yaw>=-8)
//        {
//         control_speed1(20*yaw,0);
//         control_speed2(20*yaw,0);
//         control_speed3(20*yaw,0);
//         control_speed4(20*yaw,0);
//        }
//        else
//        {
//            if(yaw>0)
//            {
//         control_speed1(120,0);
//         control_speed2(120,0);
//         control_speed3(120,0);
//         control_speed4(120,0);
//            }
//            if(yaw<0)
//            {
//              control_speed1(-120,0);
//              control_speed2(-120,0);
//              control_speed3(-120,0);
//              control_speed4(-120,0);
//            }
//        }
//        if(yaw<=3&&yaw>=-3)//车身动伏较小时停止修正
//        {
//          delay_TIM7=0;
//          while(1)
//          {
//              control_speed1(10,0);
//              control_speed2(10,0);
//              control_speed3(10,0);
//              control_speed4(10,0);
//              
//              if(delay_TIM7>200)
//              {
//                  if(yaw<=3&&yaw>=-3)
//                  {
//                      flag_xiuzheng=1;
//                  }
//                  else
//                  {
//                      flag_xiuzheng=0;
//                  }
//                  break;
//              }
//          }
//          if(flag_xiuzheng==1)
//          {
//              flag_xiuzheng=0;
//              break;
//          }
//        }
//    }
//        nojudge:
//         control_speed1(15*yaw,1);
//         control_speed2(15*yaw,1);
//         control_speed3(15*yaw,1);
//         control_speed4(15*yaw,1);
//    
//}
//void single_right_long(void)//向右跑陇
//{
//    usart5_board_senddata(0);
//    usart5_board_senddata(0);
//    usart5_board_senddata(0);
//    usart_steer_senddata(steer1_long,steer2_long,steer3_long,steer4_long,0);
//    correct_car();
//    car_state=7;
//    PID_Init(&left_home_sonic,0.4f,0.0f,0.01f);
//    PID_Init(&left_home_yaw,8.0f,0.0f,0.0f);
//    control_speed1(800,0);
//    control_speed2(-800,0);
//    control_speed3(-800,0);
//    control_speed4(800,0);
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
////        if(GUANGDIAN4==0)//光电4照射到障碍物时标志两个超声波已经进入陇道，运用超声波来跑直道
////        {
////         PID_Init(&left_home_yaw,3.3f,0.0f,0.0f);
////         PID_Init(&left_home_sonic,0.75f,0.0f,0.01f);
////         control_speed1(1600,0);
////         control_speed2(-1600,0);
////         control_speed3(-1600,0);
////         control_speed4(1600,0);
////            break;
////        }
//        
//    }
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance_right<650)
//        {
//            
//            control_speed1(1200,0);
//            control_speed2(-1200,0);
//            control_speed3(-1200,0);
//            control_speed4(1200,0);
//            break;
//        }
//    }
//    decel_motor_speed_long(800,4000);
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance_right<155)
//        {
//            
//            control_speed1(0,1);
//            control_speed2(0,1);
//            control_speed3(0,1);
//            control_speed4(0,1);
//            break;
//        }
//    }
//    car_state=0;
//}



//void no_single_left_long(void)//左陇
//{
//    usart5_board_senddata(0XAA);
//    usart5_board_senddata(0XAA);
//    usart5_board_senddata(0XAA);
//    usart_steer_senddata(steer1_long,steer2_long,steer3_long,steer4_long,0);//舵机转向
//    correct_car();
//         car_state=5;
//         PID_Init(&left_home_sonic,0.0f,0.0f,0.00f);
//         PID_Init(&left_home_yaw,6.0f,0.0f,0.0f);
//         control_speed1(-800,0);
//         control_speed2(800,0);
//         control_speed3(800,0);
//         control_speed4(-800,0);
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance<180)//距离180
//        {
//         PID_Init(&left_home_yaw,2.0f,0.0f,0.0f);
//         PID_Init(&left_home_sonic,0.7f,0.0f,0.00f);//////////////////////////////////////////////////////////////////
//         control_speed1(-1600,0);
//         control_speed2(1600,0);
//         control_speed3(1600,0);
//         control_speed4(-1600,0);
//            break;
//        }
//        
//    }
//		while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance_left<=650)//距离180
//        {
//            control_speed1(-1200,0);
//            control_speed2(1200,0);
//            control_speed3(1200,0);
//            control_speed4(-1200,0);
//            break;
//        }
//    }
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
////        if(GUANGDIAN4==1)//距离180
////        {
////            PID_Init(&left_home_sonic,0.0f,0.0f,0.00f);
////            PID_Init(&left_home_yaw,4.0f,0.0f,0.0f);
////            break;
////        }
//    }
//    
//    decel_motor_speed_long_left(800,800);
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance_left<150)
//        {
//         control_speed1(-600,1);
//         control_speed2(600,1);
//         control_speed3(600,1);
//         control_speed4(-600,1);
//            break;
//        }
//    }
//    car_state=0;
//    usart5_board_senddata(0);
//    usart5_board_senddata(0);
//    usart5_board_senddata(0);
//}


//void no_single_right_long(void)//右陇
//{
//    usart5_board_senddata(0XBB);
//    usart5_board_senddata(0XBB);
//    usart5_board_senddata(0XBB);
//    usart_steer_senddata(steer1_long,steer2_long,steer3_long,steer4_long,0);
//    correct_car();
//         car_state=3;
//         PID_Init(&left_home_sonic,0.0f,0.0f,0.00f);
//         PID_Init(&left_home_yaw,6.0f,0.0f,0.0f);
//         control_speed1(800,0);
//         control_speed2(-800,0);
//         control_speed3(-800,0);
//         control_speed4(800,0);
//    while(1)//进陇道
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance<180)
//        {
//         PID_Init(&left_home_yaw,2.0f,0.0f,0.0f);
//         PID_Init(&left_home_sonic,0.65f,0.0f,0.0f);//////////////////////////////////////////////////////////////////
//         control_speed1(1600,0);
//         control_speed2(-1600,0);
//         control_speed3(-1600,0);
//         control_speed4(1600,0);
//            break;
//        }
//        
//    }
//		while(1)//出陇道
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance_right<=700)
//        {
//				 control_speed1(1200,0);
//         control_speed2(-1200,0);
//         control_speed3(-1200,0);
//         control_speed4(1200,0);
//            break;
//        }
//    }
//    while(1)//出陇道
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
////        if(GUANGDIAN4==1)
////        {
////            PID_Init(&left_home_sonic,0.0f,0.0f,0.00f);
////            PID_Init(&left_home_yaw,4.0f,0.0f,0.0f);
////            break;
////        }
//    }
//    
//    decel_motor_speed_long(800,500);
//    while(1)
//    {
//        usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//        if(distance_right<150)
//        {
//         control_speed1(250,1);
//         control_speed2(-250,1);
//         control_speed3(-250,1);
//         control_speed4(250,1);
//            break;
//        }
//    }
//    car_state=0;
//    usart5_board_senddata(0);
//    usart5_board_senddata(0);
//    usart5_board_senddata(0);
//}

//void back_left_shu_long(float quan)//左竖陇
//{
//    usart_steer_senddata(steer1_init,steer2_init,steer3_init,steer4_init,0);
//    correct_car();
//         car_state=6;
//         PID_Init(&left_home_sonic,0.45f,0.0f,0.01f);
//         PID_Init(&left_home_yaw,1.5f,0.0f,0.0f);
//         create_t_ctrl_param1(-SPR*quan, 400, 400, 400);
//         create_t_ctrl_param2(-SPR*quan, 400, 400, 400);
//         create_t_ctrl_param3(SPR*quan, 400, 400, 400);
//         create_t_ctrl_param4(SPR*quan, 400, 400, 400);//固定距离停车
//         while(g_motion_sta1||g_motion_sta2||g_motion_sta||g_motion_sta4)//全部停车
//         {
//             usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//         }
//         car_state=0;
//}
//void back_right_shu_long(float quan)//右竖陇
//{
//    usart_steer_senddata(steer1_init,steer2_init,steer3_init,steer4_init,0);
//    correct_car();
//         car_state=4;
//         PID_Init(&left_home_sonic,0.45f,0.0f,0.01f);
//         PID_Init(&left_home_yaw,1.5f,0.0f,0.0f);
//         create_t_ctrl_param1(-SPR*quan, 400, 400, 400);
//         create_t_ctrl_param2(-SPR*quan, 400, 400, 400);
//         create_t_ctrl_param3(SPR*quan, 400, 400, 400);
//         create_t_ctrl_param4(SPR*quan, 400, 400, 400);
//         while(g_motion_sta1||g_motion_sta2||g_motion_sta||g_motion_sta4)
//         {
//             usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//         }
//         car_state=0;
//}

//void go_home(float quan)
//{
//    usart_steer_senddata(steer1_init,steer2_init,steer3_init,steer4_init,0);
//    correct_car();
//         car_state=6;
//         PID_Init(&left_home_sonic,0.0f,0.0f,0.00f);
//         PID_Init(&left_home_yaw,5.0f,0.0f,0.0f);
//         create_t_ctrl_param1(-SPR*quan, 400, 400, 400);
//         create_t_ctrl_param2(-SPR*quan, 400, 400, 400);
//         create_t_ctrl_param3(SPR*quan, 400, 400, 400);
//         create_t_ctrl_param4(SPR*quan, 400, 400, 400);
//         while(g_motion_sta1||g_motion_sta2||g_motion_sta||g_motion_sta4)
//         {
//             usart_steer_senddata(speeda,speedb,speedc,speedd,0);
//         }
//         car_state=0;
//}
