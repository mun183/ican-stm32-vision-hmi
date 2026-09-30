#include "dianji.h"
#include "led.h"
#include "usart.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器PWM 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
//TIM14 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
uint64_t long_distance=0;
uint8_t tim_rush_state1=0;
uint8_t tim_rush_state2=0;
uint8_t tim_rush_state3=0;
uint8_t tim_rush_state4=0;
uint32_t tim_add_distance=0;
uint32_t tim_add_distance2=0;
uint32_t tim_add_distance3=0;
uint32_t tim_add_distance4=0;
void TIM1_OC_Init(uint32_t arr,uint32_t psc)
{		 					 
	//此部分需手动修改IO口设置
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA9
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//初始化定时器14
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
    TIM_OCInitStructure.TIM_Pulse=32768;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
    TIM_OCInitStructure.TIM_Pulse=32768;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
    TIM_OCInitStructure.TIM_Pulse=32768;
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
    TIM_OCInitStructure.TIM_Pulse=32768;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);  //使能TIM1在CCR1上的预装载寄存器
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Disable);  //使能TIM1在CCR1上的预装载寄存器
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Disable);  //使能TIM1在CCR1上的预装载寄存器
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable);  //使能TIM1在CCR1上的预装载寄存器
    TIM_CCxCmd(TIM1,TIM_Channel_1,TIM_CCx_Disable);
    TIM_CCxCmd(TIM1,TIM_Channel_2,TIM_CCx_Disable);
    TIM_CCxCmd(TIM1,TIM_Channel_3,TIM_CCx_Disable);
    TIM_CCxCmd(TIM1,TIM_Channel_4,TIM_CCx_Disable);
    TIM_ITConfig(TIM1,TIM_IT_CC2,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC2) ;
    TIM_ClearITPendingBit(TIM1,TIM_IT_CC2);
    TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC1) ;
    TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
    TIM_ITConfig(TIM1,TIM_IT_CC3,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC3) ;
    TIM_ClearITPendingBit(TIM1,TIM_IT_CC3);
    TIM_ITConfig(TIM1,TIM_IT_CC4,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC4) ;
    TIM_ClearITPendingBit(TIM1,TIM_IT_CC4);
	TIM_Cmd(TIM1, ENABLE);
    TIM_ITConfig(TIM1,TIM_IT_CC4,DISABLE);
    TIM_ITConfig(TIM1,TIM_IT_CC3,DISABLE);
    TIM_ITConfig(TIM1,TIM_IT_CC2,DISABLE);
    TIM_ITConfig(TIM1,TIM_IT_CC1,DISABLE);
    NVIC_InitStructure.NVIC_IRQChannel=TIM1_CC_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    TIM_CtrlPWMOutputs(TIM1,ENABLE);
										  
}  

void stepper_init(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct;

    STEPPER_DIR1_GPIO_CLK_ENABLE();                                 /* DIR1时钟使能 */
    STEPPER_DIR2_GPIO_CLK_ENABLE();                                 /* DIR2时钟使能 */
    STEPPER_DIR3_GPIO_CLK_ENABLE();                                 /* DIR3时钟使能 */
    STEPPER_DIR4_GPIO_CLK_ENABLE();                                 /* DIR4时钟使能 */
            

    gpio_init_struct.GPIO_Pin = STEPPER_DIR1_GPIO_PIN;              
    gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;                   
    gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init_struct.GPIO_OType= GPIO_OType_PP;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;                  
    GPIO_Init(STEPPER_DIR1_GPIO_PORT, &gpio_init_struct);     

    gpio_init_struct.GPIO_Pin = STEPPER_DIR2_GPIO_PIN;              
    gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init_struct.GPIO_OType= GPIO_OType_PP;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;                          
    gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;                  
    GPIO_Init(STEPPER_DIR2_GPIO_PORT, &gpio_init_struct);     

    gpio_init_struct.GPIO_Pin = STEPPER_DIR3_GPIO_PIN;              
    gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP; 
    gpio_init_struct.GPIO_OType= GPIO_OType_PP;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;                          
    gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz; 
    
    GPIO_Init(STEPPER_DIR3_GPIO_PORT, &gpio_init_struct); 
    gpio_init_struct.GPIO_Pin = STEPPER_DIR4_GPIO_PIN;              
    gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init_struct.GPIO_OType= GPIO_OType_PP;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;                          
    gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;                  
    GPIO_Init(STEPPER_DIR4_GPIO_PORT, &gpio_init_struct); 
    TIM1_OC_Init(arr, psc);                                /* 初始化PUL引脚，以及脉冲模式等 */
}

/********************************************梯形加减速***********************************************/
speedRampData g_srd               = {STOP,CW,0,0,0,0,0};  /* 加减速变量 */
__IO int32_t  g_step_position     = 0;                    /* 当前位置 */
__IO uint8_t  g_motion_sta        = 0;                    /* 是否在运动？0：停止，1：运动 */
__IO uint32_t g_add_pulse_count   = 0;                    /* 脉冲个数累计 */
speedRampData g_srd2              = {STOP,CW,0,0,0,0,0};
__IO int32_t  g_step_position2     = 0;                    /* 当前位置 */
__IO uint8_t  g_motion_sta2        = 0;                    /* 是否在运动？0：停止，1：运动 */
__IO uint32_t g_add_pulse_count2   = 0;                    /* 脉冲个数累计 */
speedRampData g_srd4              = {STOP,CW,0,0,0,0,0};
__IO int32_t  g_step_position4     = 0;                    /* 当前位置 */
__IO uint8_t  g_motion_sta4        = 0;                    /* 是否在运动？0：停止，1：运动 */
__IO uint32_t g_add_pulse_count4   = 0;                    /* 脉冲个数累计 */
speedRampData g_srd1              = {STOP,CW,0,0,0,0,0};
__IO int32_t  g_step_position1     = 0;                    /* 当前位置 */
__IO uint8_t  g_motion_sta1        = 0;                    /* 是否在运动？0：停止，1：运动 */
__IO uint32_t g_add_pulse_count1   = 0;                    /* 脉冲个数累计 */

void create_t_ctrl_param3(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed)
{
    __IO uint16_t tim_count;        /* 达到最大速度时的步数*/
    __IO uint32_t max_s_lim;        /* 必须要开始减速的步数（如果加速没有达到最大速度）*/
    __IO uint32_t accel_lim;
    if(g_motion_sta != STOP)        /* 只允许步进电机在停止的时候才继续*/
        return;
    if(step < 0)                    /* 步数为负数 */
    {   
        g_srd.dir = CCW;            /* 逆时针方向旋转 */
        ST3_DIR(CCW);
        step = -step;               /* 获取步数绝对值 */
    }
    else
    {
        g_srd.dir = CW;             /* 顺时针方向旋转 */
        ST3_DIR(CW);
    }

    if(step == 1)                   /* 步数为1 */
    {
        g_srd.accel_count = -1;     /* 只移动一步 */
        g_srd.run_state = DECEL;    /* 减速状态. */
        g_srd.step_delay = 1000;    /* 默认速度 */
    }
    else if(step != 0)              /* 如果目标运动步数不为0*/
    {
        /*设置最大速度极限, 计算得到min_delay用于定时器的计数器的值 min_delay = (alpha / t)/ w*/
        g_srd.min_delay = (int32_t)(A_T_x10 /speed); //匀速运行时的计数值

        /* 通过计算第一个(c0) 的步进延时来设定加速度，其中accel单位为0.1rad/sec^2
         step_delay = 1/tt * sqrt(2*alpha/accel)
         step_delay = ( tfreq*0.69/10 )*10 * sqrt( (2*alpha*100000) / (accel*10) )/100 */
        
        g_srd.step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / accel))/10); /* c0 */

        max_s_lim = (uint32_t)(speed*speed / (A_x200*accel/10));/* 计算多少步之后达到最大速度的限制 max_s_lim = speed^2 / (2*alpha*accel) */

        if(max_s_lim == 0)                                      /* 如果达到最大速度小于0.5步，我们将四舍五入为0,但实际我们必须移动至少一步才能达到想要的速度 */
        {
            max_s_lim = 1;
        }
        accel_lim = (uint32_t)(step*decel/(accel+decel));       /* 这里不限制最大速度 计算多少步之后我们必须开始减速 n1 = (n1+n2)decel / (accel + decel) */

        if(accel_lim == 0)                                      /* 不足一步 按一步处理*/
        {
            accel_lim = 1;
        }
        if(accel_lim <= max_s_lim)                              /* 加速阶段到不了最大速度就得减速。。。使用限制条件我们可以计算出减速阶段步数 */
        {
            g_srd.decel_val = accel_lim - step;                 /* 减速段的步数 */
        }
        else
        {
            g_srd.decel_val = -(max_s_lim*accel/decel);         /* 减速段的步数 */
        }
        if(g_srd.decel_val == 0)                                /* 不足一步 按一步处理 */
        {
            g_srd.decel_val = -1;
        }
        g_srd.decel_start = step + g_srd.decel_val;             /* 计算开始减速时的步数 */
        
        
        if(g_srd.step_delay <= g_srd.min_delay)                 /* 如果一开始c0的速度比匀速段速度还大，就不需要进行加速运动，直接进入匀速 */
        {
            g_srd.step_delay = g_srd.min_delay;
            g_srd.run_state = RUN;
        }
        else  
        {
            g_srd.run_state = ACCEL;
        }
        g_srd.accel_count = 0;                                  /* 复位加减速计数值 */
    }
    g_motion_sta = 1;                                           /* 电机为运动状态 */
    tim_count=TIM1->CNT;
    TIM_SetCompare3(TIM1, tim_count+g_srd.step_delay/2);  /* 设置定时器比较值 */ 
    TIM_CCxCmd(TIM1,TIM_Channel_3,TIM_CCx_Enable);
    TIM_ITConfig(TIM1,TIM_IT_CC3,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC3);
    TIM_Cmd(TIM1, ENABLE);
}
void create_t_ctrl_param2(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed)
{
    __IO uint16_t tim_count2;        /* 达到最大速度时的步数*/
    __IO uint32_t max_s_lim2;        /* 必须要开始减速的步数（如果加速没有达到最大速度）*/
    __IO uint32_t accel_lim2;
    if(g_motion_sta2 != STOP)        /* 只允许步进电机在停止的时候才继续*/
        return;
    if(step < 0)                    /* 步数为负数 */
    {   
        g_srd2.dir = CCW;            /* 逆时针方向旋转 */
        ST2_DIR(CCW);
        step = -step;               /* 获取步数绝对值 */
    }
    else
    {
        g_srd2.dir = CW;             /* 顺时针方向旋转 */
        ST2_DIR(CW);
    }

    if(step == 1)                   /* 步数为1 */
    {
        g_srd2.accel_count = -1;     /* 只移动一步 */
        g_srd2.run_state = DECEL;    /* 减速状态. */
        g_srd2.step_delay = 1000;    /* 默认速度 */
    }
    else if(step != 0)              /* 如果目标运动步数不为0*/
    {
        /*设置最大速度极限, 计算得到min_delay用于定时器的计数器的值 min_delay = (alpha / t)/ w*/
        g_srd2.min_delay = (int32_t)(A_T_x10 /speed); //匀速运行时的计数值

        /* 通过计算第一个(c0) 的步进延时来设定加速度，其中accel单位为0.1rad/sec^2
         step_delay = 1/tt * sqrt(2*alpha/accel)
         step_delay = ( tfreq*0.69/10 )*10 * sqrt( (2*alpha*100000) / (accel*10) )/100 */
        
        g_srd2.step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / accel))/10); /* c0 */

        max_s_lim2 = (uint32_t)(speed*speed / (A_x200*accel/10));/* 计算多少步之后达到最大速度的限制 max_s_lim = speed^2 / (2*alpha*accel) */

        if(max_s_lim2 == 0)                                      /* 如果达到最大速度小于0.5步，我们将四舍五入为0,但实际我们必须移动至少一步才能达到想要的速度 */
        {
            max_s_lim2 = 1;
        }
        accel_lim2 = (uint32_t)(step*decel/(accel+decel));       /* 这里不限制最大速度 计算多少步之后我们必须开始减速 n1 = (n1+n2)decel / (accel + decel) */

        if(accel_lim2 == 0)                                      /* 不足一步 按一步处理*/
        {
            accel_lim2 = 1;
        }
        if(accel_lim2 <= max_s_lim2)                              /* 加速阶段到不了最大速度就得减速。。。使用限制条件我们可以计算出减速阶段步数 */
        {
            g_srd2.decel_val = accel_lim2 - step;                 /* 减速段的步数 */
        }
        else
        {
            g_srd2.decel_val = -(max_s_lim2*accel/decel);         /* 减速段的步数 */
        }
        if(g_srd2.decel_val == 0)                                /* 不足一步 按一步处理 */
        {
            g_srd2.decel_val = -1;
        }
        g_srd2.decel_start = step + g_srd2.decel_val;             /* 计算开始减速时的步数 */
        
        
        if(g_srd2.step_delay <= g_srd2.min_delay)                 /* 如果一开始c0的速度比匀速段速度还大，就不需要进行加速运动，直接进入匀速 */
        {
            g_srd2.step_delay = g_srd2.min_delay;
            g_srd2.run_state = RUN;
        }
        else  
        {
            g_srd2.run_state = ACCEL;
        }
        g_srd2.accel_count = 0;                                  /* 复位加减速计数值 */
    }
    g_motion_sta2 = 1;                                           /* 电机为运动状态 */
    tim_count2=TIM1->CNT;
    TIM_SetCompare2(TIM1, tim_count2+g_srd2.step_delay/2);  /* 设置定时器比较值 */
    TIM_CCxCmd(TIM1,TIM_Channel_2,TIM_CCx_Enable);
    TIM_ITConfig(TIM1,TIM_IT_CC2,ENABLE);                                 /* 使能定时器通道 */
    TIM_ClearFlag(TIM1,TIM_FLAG_CC2);
    TIM_Cmd(TIM1, ENABLE);
}

void create_t_ctrl_param4(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed)
{
    __IO uint16_t tim_count4;        /* 达到最大速度时的步数*/
    __IO uint32_t max_s_lim4;        /* 必须要开始减速的步数（如果加速没有达到最大速度）*/
    __IO uint32_t accel_lim4;
    if(g_motion_sta4 != STOP)        /* 只允许步进电机在停止的时候才继续*/
        return;
    if(step < 0)                    /* 步数为负数 */
    {   
        g_srd4.dir = CCW;            /* 逆时针方向旋转 */
        ST4_DIR(CCW);
        step = -step;               /* 获取步数绝对值 */
    }
    else
    {
        g_srd4.dir = CW;             /* 顺时针方向旋转 */
        ST4_DIR(CW);
    }

    if(step == 1)                   /* 步数为1 */
    {
        g_srd4.accel_count = -1;     /* 只移动一步 */
        g_srd4.run_state = DECEL;    /* 减速状态. */
        g_srd4.step_delay = 1000;    /* 默认速度 */
    }
    else if(step != 0)              /* 如果目标运动步数不为0*/
    {
        /*设置最大速度极限, 计算得到min_delay用于定时器的计数器的值 min_delay = (alpha / t)/ w*/
        g_srd4.min_delay = (int32_t)(A_T_x10 /speed); //匀速运行时的计数值

        /* 通过计算第一个(c0) 的步进延时来设定加速度，其中accel单位为0.1rad/sec^2
         step_delay = 1/tt * sqrt(2*alpha/accel)
         step_delay = ( tfreq*0.69/10 )*10 * sqrt( (2*alpha*100000) / (accel*10) )/100 */
        
        g_srd4.step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / accel))/10); /* c0 */

        max_s_lim4 = (uint32_t)(speed*speed / (A_x200*accel/10));/* 计算多少步之后达到最大速度的限制 max_s_lim = speed^2 / (2*alpha*accel) */

        if(max_s_lim4 == 0)                                      /* 如果达到最大速度小于0.5步，我们将四舍五入为0,但实际我们必须移动至少一步才能达到想要的速度 */
        {
            max_s_lim4 = 1;
        }
        accel_lim4 = (uint32_t)(step*decel/(accel+decel));       /* 这里不限制最大速度 计算多少步之后我们必须开始减速 n1 = (n1+n2)decel / (accel + decel) */

        if(accel_lim4 == 0)                                      /* 不足一步 按一步处理*/
        {
            accel_lim4 = 1;
        }
        if(accel_lim4 <= max_s_lim4)                              /* 加速阶段到不了最大速度就得减速。。。使用限制条件我们可以计算出减速阶段步数 */
        {
            g_srd4.decel_val = accel_lim4 - step;                 /* 减速段的步数 */
        }
        else
        {
            g_srd4.decel_val = -(max_s_lim4*accel/decel);         /* 减速段的步数 */
        }
        if(g_srd4.decel_val == 0)                                /* 不足一步 按一步处理 */
        {
            g_srd4.decel_val = -1;
        }
        g_srd4.decel_start = step + g_srd4.decel_val;             /* 计算开始减速时的步数 */
        
        
        if(g_srd4.step_delay <= g_srd4.min_delay)                 /* 如果一开始c0的速度比匀速段速度还大，就不需要进行加速运动，直接进入匀速 */
        {
            g_srd4.step_delay = g_srd4.min_delay;
            g_srd4.run_state = RUN;
        }
        else  
        {
            g_srd4.run_state = ACCEL;
        }
        g_srd4.accel_count = 0;                                  /* 复位加减速计数值 */
    }
    g_motion_sta4 = 1;
    tim_count4=TIM1->CNT;
    TIM_SetCompare4(TIM1, tim_count4+g_srd4.step_delay/2);  /* 设置定时器比较值 */ 
    TIM_CCxCmd(TIM1,TIM_Channel_4,TIM_CCx_Enable);
    TIM_ITConfig(TIM1,TIM_IT_CC4,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC4);
    TIM_Cmd(TIM1, ENABLE);
}

void create_t_ctrl_param1(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed)
{
    __IO uint16_t tim_count1;        /* 达到最大速度时的步数*/
    __IO uint32_t max_s_lim1;        /* 必须要开始减速的步数（如果加速没有达到最大速度）*/
    __IO uint32_t accel_lim1;
    if(g_motion_sta1 != STOP)        /* 只允许步进电机在停止的时候才继续*/
        return;
    if(step < 0)                    /* 步数为负数 */
    {   
        g_srd1.dir = CCW;            /* 逆时针方向旋转 */
        ST1_DIR(CCW);
        step = -step;               /* 获取步数绝对值 */
    }
    else
    {
        g_srd1.dir = CW;             /* 顺时针方向旋转 */
        ST1_DIR(CW);
    }

    if(step == 1)                   /* 步数为1 */
    {
        g_srd1.accel_count = -1;     /* 只移动一步 */
        g_srd1.run_state = DECEL;    /* 减速状态. */
        g_srd1.step_delay = 1000;    /* 默认速度 */
    }
    else if(step != 0)              /* 如果目标运动步数不为0*/
    {
        /*设置最大速度极限, 计算得到min_delay用于定时器的计数器的值 min_delay = (alpha / t)/ w*/
        g_srd1.min_delay = (int32_t)(A_T_x10 /speed); //匀速运行时的计数值

        /* 通过计算第一个(c0) 的步进延时来设定加速度，其中accel单位为0.1rad/sec^2
         step_delay = 1/tt * sqrt(2*alpha/accel)
         step_delay = ( tfreq*0.69/10 )*10 * sqrt( (2*alpha*100000) / (accel*10) )/100 */
        
        g_srd1.step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / accel))/10); /* c0 */

        max_s_lim1 = (uint32_t)(speed*speed / (A_x200*accel/10));/* 计算多少步之后达到最大速度的限制 max_s_lim = speed^2 / (2*alpha*accel) */

        if(max_s_lim1 == 0)                                      /* 如果达到最大速度小于0.5步，我们将四舍五入为0,但实际我们必须移动至少一步才能达到想要的速度 */
        {
            max_s_lim1 = 1;
        }
        accel_lim1 = (uint32_t)(step*decel/(accel+decel));       /* 这里不限制最大速度 计算多少步之后我们必须开始减速 n1 = (n1+n2)decel / (accel + decel) */

        if(accel_lim1 == 0)                                      /* 不足一步 按一步处理*/
        {
            accel_lim1 = 1;
        }
        if(accel_lim1 <= max_s_lim1)                              /* 加速阶段到不了最大速度就得减速。。。使用限制条件我们可以计算出减速阶段步数 */
        {
            g_srd1.decel_val = accel_lim1 - step;                 /* 减速段的步数 */
        }
        else
        {
            g_srd1.decel_val = -(max_s_lim1*accel/decel);         /* 减速段的步数 */
        }
        if(g_srd1.decel_val == 0)                                /* 不足一步 按一步处理 */
        {
            g_srd1.decel_val = -1;
        }
        g_srd1.decel_start = step + g_srd1.decel_val;             /* 计算开始减速时的步数 */
        
        
        if(g_srd1.step_delay <= g_srd1.min_delay)                 /* 如果一开始c0的速度比匀速段速度还大，就不需要进行加速运动，直接进入匀速 */
        {
            g_srd1.step_delay = g_srd1.min_delay;
            g_srd1.run_state = RUN;
        }
        else  
        {
            g_srd1.run_state = ACCEL;
        }
        g_srd1.accel_count = 0;                                  /* 复位加减速计数值 */
    }
    g_motion_sta1 = 1;
    tim_count1=TIM1->CNT;
    TIM_SetCompare1(TIM1, tim_count1+g_srd1.step_delay/2);  /* 设置定时器比较值 */ 
    TIM_CCxCmd(TIM1,TIM_Channel_1,TIM_CCx_Enable);
    TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC1) ;
    TIM_Cmd(TIM1, ENABLE);
}
void control_speed1(double speed,uint8_t state)//速度单位为度/秒
{
    uint32_t count_bujin_data;
    if(state==0)
    {
    if(speed<0)
    {
        speed=-speed;
        g_srd1.dir = CCW;
        ST1_DIR(CCW);
    }
    else
    {
        g_srd1.dir = CW;
        ST1_DIR(CW);
    }
	if(speed<2)
	{
		speed=2;
	}
    count_bujin_data=(uint32_t)(MAX_STEP_ANGLE/(0.0000005*speed*2));
    tim_add_distance=count_bujin_data;
    tim_rush_state1=1;
    g_motion_sta1 = 1;
	TIM_CCxCmd(TIM1,TIM_Channel_1,TIM_CCx_Enable);
    TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC1) ;
    TIM_Cmd(TIM1, ENABLE);
    }
    else
    {
    TIM_ITConfig(TIM1,TIM_IT_CC1,DISABLE);
    TIM_CCxCmd(TIM1,TIM_Channel_1,TIM_CCx_Disable);
    g_motion_sta1 = 0;                           /* 电机为停止状态  */
    tim_rush_state1=0;
	tim_add_distance=0;
    }
}

void pid_speed1(double speed)//速度单位为度/秒
{
    uint32_t count_bujin_data;
    if(speed<0)
    {
        speed=-speed;
        g_srd1.dir = CCW;
        ST1_DIR(CCW);
    }
    else
    {
        g_srd1.dir = CW;
        ST1_DIR(CW);
    }
    count_bujin_data=(uint32_t)(MAX_STEP_ANGLE/(0.0000005*speed*2));
    tim_add_distance=count_bujin_data;   
}
void control_speed2(double speed,uint8_t state)//速度单位为度/秒
{
    uint32_t count_bujin_data;
    if(state==0)
    {
    if(speed<0)
    {
        speed=-speed;
        g_srd2.dir = CCW;
        ST2_DIR(CCW);
    }
    else
    {
        g_srd2.dir = CW;
        ST2_DIR(CW);
    }
	if(speed<2)
	{
		speed=2;
	}
    count_bujin_data=(uint32_t)(MAX_STEP_ANGLE/(0.0000005*speed*2));
    tim_add_distance2=count_bujin_data;
    tim_rush_state2=1;
    g_motion_sta2 = 1;
	TIM_CCxCmd(TIM1,TIM_Channel_2,TIM_CCx_Enable);
    TIM_ITConfig(TIM1,TIM_IT_CC2,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC2) ;
    TIM_Cmd(TIM1, ENABLE);
    }
    else
    {
    TIM_ITConfig(TIM1,TIM_IT_CC2,DISABLE);
    TIM_CCxCmd(TIM1,TIM_Channel_2,TIM_CCx_Disable);
    g_motion_sta2 = 0;                           /* 电机为停止状态  */
    tim_rush_state2=0;
	tim_add_distance2=0;
    }
}
void pid_speed2(double speed)//速度单位为度/秒
{
    uint32_t count_bujin_data;
    if(speed<0)
    {
        speed=-speed;
        g_srd2.dir = CCW;
        ST2_DIR(CCW);
    }
    else
    {
        g_srd2.dir = CW;
        ST2_DIR(CW);
    }
	if(speed<2)
	{
		speed=2;
	}
    count_bujin_data=(uint32_t)(MAX_STEP_ANGLE/(0.0000005*speed*2));
    tim_add_distance2=count_bujin_data;   
}
void control_speed3(double speed,uint8_t state)//速度单位为度/秒
{
    uint32_t count_bujin_data;
    if(state==0)
    {
    if(speed<0)
    {
        speed=-speed;
        g_srd.dir = CCW;
        ST3_DIR(CCW);
    }
    else
    {
        g_srd.dir = CW;
        ST3_DIR(CW);
    }
	if(speed<2)
	{
		speed=2;
	}
    count_bujin_data=(uint32_t)(MAX_STEP_ANGLE/(0.0000005*speed*2));
    tim_add_distance3=count_bujin_data;
    tim_rush_state3=1;
    g_motion_sta = 1;
	TIM_CCxCmd(TIM1,TIM_Channel_3,TIM_CCx_Enable);
    TIM_ITConfig(TIM1,TIM_IT_CC3,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC3) ;
    TIM_Cmd(TIM1, ENABLE);
    }
    else
    {
    TIM_ITConfig(TIM1,TIM_IT_CC3,DISABLE);
    TIM_CCxCmd(TIM1,TIM_Channel_3,TIM_CCx_Disable);
    g_motion_sta = 0;                           /* 电机为停止状态  */
    tim_rush_state3=0;
	tim_add_distance3=0;
    }
}

void pid_speed3(double speed)//速度单位为度/秒
{
    uint32_t count_bujin_data;
    if(speed<0)
    {
        speed=-speed;
        g_srd.dir = CCW;
        ST3_DIR(CCW);
    }
    else
    {
        g_srd.dir = CW;
        ST3_DIR(CW);
    }
	if(speed<2)
	{
		speed=2;
	}
    count_bujin_data=(uint32_t)(MAX_STEP_ANGLE/(0.0000005*speed*2));
    tim_add_distance3=count_bujin_data;   
}

void pid_speed4(double speed)//速度单位为度/秒
{
    uint32_t count_bujin_data;
    if(speed<0)
    {
        speed=-speed;
        g_srd4.dir = CCW;
        ST4_DIR(CCW);
    }
    else
    {
        g_srd4.dir = CW;
        ST4_DIR(CW);
    }
	if(speed<2)
	{
		speed=2;
	}
    count_bujin_data=(uint32_t)(MAX_STEP_ANGLE/(0.0000005*speed*2));
    tim_add_distance4=count_bujin_data;   
}
void control_speed4(double speed,uint8_t state)//速度单位为度/秒
{
    uint32_t count_bujin_data;
    if(state==0)
    {
    if(speed<0)
    {
        speed=-speed;
        g_srd4.dir = CCW;
        ST4_DIR(CCW);
    }
    else
    {
        g_srd4.dir = CW;
        ST4_DIR(CW);
    }
	if(speed<2)
	{
		speed=2;
	}
    count_bujin_data=(uint32_t)(MAX_STEP_ANGLE/(0.0000005*speed*2));
    tim_add_distance4=count_bujin_data;
    tim_rush_state4=1;
    g_motion_sta4 = 1;
	TIM_CCxCmd(TIM1,TIM_Channel_4,TIM_CCx_Enable);
    TIM_ITConfig(TIM1,TIM_IT_CC4,ENABLE);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC4) ;
    TIM_Cmd(TIM1, ENABLE);
    }
    else
    {
    TIM_ITConfig(TIM1,TIM_IT_CC4,DISABLE);
    TIM_CCxCmd(TIM1,TIM_Channel_4,TIM_CCx_Disable);
    g_motion_sta4 = 0;                           /* 电机为停止状态  */
    tim_rush_state4=0;
	tim_add_distance4=0;
    }
}

void TIM1_CC_IRQHandler(void)
{
    __IO uint32_t tim_count = 0;
    __IO uint32_t tmp = 0;
    uint16_t new_step_delay = 0;                            /* 保存新（下）一个延时周期 */
    __IO static uint16_t last_accel_delay = 0;              /* 加速过程中最后一次延时（脉冲周期） */
    __IO static uint32_t step_count = 0;                    /* 总移动步数计数器*/
    __IO static int32_t rest = 0;                           /* 记录new_step_delay中的余数，提高下一步计算的精度 */
    __IO static uint8_t i = 0;                              /* 定时器使用翻转模式，需要进入两次中断才输出一个完整脉冲 */
    __IO uint32_t tim_count2 = 0;
    __IO uint32_t tmp2 = 0;
    uint16_t new_step_delay2 = 0;                            /* 保存新（下）一个延时周期 */
    __IO static uint16_t last_accel_delay2 = 0;              /* 加速过程中最后一次延时（脉冲周期） */
    __IO static uint32_t step_count2 = 0;                    /* 总移动步数计数器*/
    __IO static int32_t rest2 = 0;                           /* 记录new_step_delay中的余数，提高下一步计算的精度 */
    __IO static uint8_t i2 = 0;                              /* 定时器使用翻转模式，需要进入两次中断才输出一个完整脉冲 */
    __IO uint32_t tim_count4 = 0;
    __IO uint32_t tmp4 = 0;
    uint16_t new_step_delay4 = 0;                            /* 保存新（下）一个延时周期 */
    __IO static uint16_t last_accel_delay4 = 0;              /* 加速过程中最后一次延时（脉冲周期） */
    __IO static uint32_t step_count4 = 0;                    /* 总移动步数计数器*/
    __IO static int32_t rest4 = 0;                           /* 记录new_step_delay中的余数，提高下一步计算的精度 */
    __IO static uint8_t i4 = 0;                              /* 定时器使用翻转模式，需要进入两次中断才输出一个完整脉冲 */
    __IO uint32_t tim_count1 = 0;
    __IO uint32_t tmp1 = 0;
    uint16_t new_step_delay1 = 0;                            /* 保存新（下）一个延时周期 */
    __IO static uint16_t last_accel_delay1 = 0;              /* 加速过程中最后一次延时（脉冲周期） */
    __IO static uint32_t step_count1 = 0;                    /* 总移动步数计数器*/
    __IO static int32_t rest1 = 0;                           /* 记录new_step_delay中的余数，提高下一步计算的精度 */
    __IO static uint8_t i1 = 0;                              /* 定时器使用翻转模式，需要进入两次中断才输出一个完整脉冲 */
    if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
    {
        if(tim_rush_state1==0)
        {
        LED1=0;
        tim_count1=TIM1->CNT;
        tmp1 = tim_count1 + g_srd1.step_delay/2;
        TIM_SetCompare1(TIM1, tmp1);
        i1++;                                                /* 定时器中断次数计数值 */
        if(i1 == 2)                                          /* 2次，说明已经输出一个完整脉冲 */
        {
            i1 = 0;                                          /* 清零定时器中断次数计数值 */
            switch(g_srd1.run_state)                         /* 加减速曲线阶段 */
            {
            case STOP:
                step_count1 = 0;                             /* 清零步数计数器 */
                rest1 = 0;                                   /* 清零余值 */
                /* 关闭通道*/
                TIM_ITConfig(TIM1,TIM_IT_CC1,DISABLE);
                TIM_CCxCmd(TIM1,TIM_Channel_1,TIM_CCx_Disable);
                g_motion_sta1 = 0;                           /* 电机为停止状态  */
                break;

            case ACCEL:
                g_add_pulse_count1++;                        /* 只用于记录相对位置转动了多少度 */
                step_count1++;                               /* 步数加1*/
                if(g_srd1.dir == CW)
                {
                    g_step_position1++;                      /* 绝对位置加1  记录绝对位置转动多少度*/
                }
                else
                {
                    g_step_position1--;                      /* 绝对位置减1*/
                }
                g_srd1.accel_count++;                        /* 加速计数值加1*/
                new_step_delay1 = g_srd1.step_delay - (((2 *g_srd1.step_delay) + rest1)/(4 * g_srd1.accel_count + 1));/* 计算新(下)一步脉冲周期(时间间隔) */
                                //g_srd.step_delay - (((2 * g_srd.step_delay) + rest)/(4 * g_srd.accel_count + 1));
                rest1 = ((2 * g_srd1.step_delay)+rest1)%(4 * g_srd1.accel_count + 1);                                /* 计算余数，下次计算补上余数，减少误差 */
                if(step_count1 >= g_srd1.decel_start)         /* 检查是否到了需要减速的步数 */
                {
                    g_srd1.accel_count = g_srd1.decel_val;    /* 加速计数值为减速阶段计数值的初始值 */
                    g_srd1.run_state = DECEL;                /* 下个脉冲进入减速阶段 */
                }
                else if(new_step_delay1 <= g_srd1.min_delay)  /* 检查是否到达期望的最大速度 计数值越小速度越快，当你的速度和最大速度相等或更快就进入匀速*/
                {
                    last_accel_delay1 = new_step_delay1;      /* 保存加速过程中最后一次延时（脉冲周期）*/
                    new_step_delay1 = g_srd1.min_delay;       /* 使用min_delay（对应最大速度speed）*/
                    rest1 = 0;                               /* 清零余值 */
                    g_srd1.run_state = RUN;                  /* 设置为匀速运行状态 */
                }
                break;

            case RUN:
                g_add_pulse_count1++;
                step_count1++;                               /* 步数加1 */
                if(g_srd1.dir == CW)
                {
                    g_step_position1++;                      /* 绝对位置加1 */
                }
                else
                {
                    g_step_position1--;                      /* 绝对位置减1*/
                }
                new_step_delay1 = g_srd1.min_delay;           /* 使用min_delay（对应最大速度speed）*/
                if(step_count1 >= g_srd1.decel_start)         /* 需要开始减速 */
                {
                    g_srd1.accel_count = g_srd1.decel_val;    /* 减速步数做为加速计数值 */
                    new_step_delay1 = last_accel_delay1;      /* 加阶段最后的延时做为减速阶段的起始延时(脉冲周期) */
                    g_srd1.run_state = DECEL;                /* 状态改变为减速 */
                }
                break;

            case DECEL:
                step_count1++;                               /* 步数加1 */
                g_add_pulse_count1++;
                if(g_srd1.dir == CW)
                {
                    g_step_position1++;                      /* 绝对位置加1 */
                }
                else
                {
                    g_step_position1--;                      /* 绝对位置减1 */
                }
                g_srd1.accel_count++;
                new_step_delay1 = g_srd1.step_delay - (((2 * g_srd1.step_delay) + rest1)/(4 * g_srd1.accel_count + 1));  /* 计算新(下)一步脉冲周期(时间间隔) */
                rest1 = ((2 * g_srd1.step_delay)+rest1)%(4 * g_srd1.accel_count + 1);                                   /* 计算余数，下次计算补上余数，减少误差 */

                /* 检查是否为最后一步 */
                if(g_srd1.accel_count >= 0)                  /* 判断减速步数是否从负值加到0是的话 减速完成 */
                {
                    g_srd1.run_state = STOP;
                }
                break;
            }
            g_srd1.step_delay = new_step_delay1;              /* 为下个(新的)延时(脉冲周期)赋值 */
        }
        }
        else
        {
            tim_count1=TIM1->CNT;
            tmp1 = tim_count1+tim_add_distance; 
            TIM_SetCompare1(TIM1, tmp1);
					  long_distance++;
        }
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
        TIM_ClearFlag(TIM1,TIM_FLAG_CC1) ;
    }
    if (TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)
    {
        if(tim_rush_state2==0)
        {
        tim_count2=TIM1->CNT;
        tmp2 = tim_count2 + g_srd2.step_delay/2;
        TIM_SetCompare2(TIM1, tmp2);
        i2++;                                                /* 定时器中断次数计数值 */
        if(i2 == 2)                                          /* 2次，说明已经输出一个完整脉冲 */
        {
            i2 = 0;                                          /* 清零定时器中断次数计数值 */
            switch(g_srd2.run_state)                         /* 加减速曲线阶段 */
            {
            case STOP:
                step_count2 = 0;                             /* 清零步数计数器 */
                rest2 = 0;                                   /* 清零余值 */
                /* 关闭通道*/
                TIM_ITConfig(TIM1,TIM_IT_CC2,DISABLE);
                TIM_CCxCmd(TIM1,TIM_Channel_2,TIM_CCx_Disable);
//                ST2_EN(EN_OFF);
                g_motion_sta2 = 0;                           /* 电机为停止状态  */
                break;

            case ACCEL:
                g_add_pulse_count2++;                        /* 只用于记录相对位置转动了多少度 */
                step_count2++;                               /* 步数加1*/
                if(g_srd2.dir == CW)
                {
                    g_step_position2++;                      /* 绝对位置加1  记录绝对位置转动多少度*/
                }
                else
                {
                    g_step_position2--;                      /* 绝对位置减1*/
                }
                g_srd2.accel_count++;                        /* 加速计数值加1*/
                new_step_delay2 = g_srd2.step_delay - (((2 *g_srd2.step_delay) + rest2)/(4 * g_srd2.accel_count + 1));/* 计算新(下)一步脉冲周期(时间间隔) */
                                //g_srd.step_delay - (((2 * g_srd.step_delay) + rest)/(4 * g_srd.accel_count + 1));
                rest2 = ((2 * g_srd2.step_delay)+rest2)%(4 * g_srd2.accel_count + 1);                                /* 计算余数，下次计算补上余数，减少误差 */
                if(step_count2 >= g_srd2.decel_start)         /* 检查是否到了需要减速的步数 */
                {
                    g_srd2.accel_count = g_srd2.decel_val;    /* 加速计数值为减速阶段计数值的初始值 */
                    g_srd2.run_state = DECEL;                /* 下个脉冲进入减速阶段 */
                }
                else if(new_step_delay2 <= g_srd2.min_delay)  /* 检查是否到达期望的最大速度 计数值越小速度越快，当你的速度和最大速度相等或更快就进入匀速*/
                {
                    last_accel_delay2 = new_step_delay2;      /* 保存加速过程中最后一次延时（脉冲周期）*/
                    new_step_delay2 = g_srd2.min_delay;       /* 使用min_delay（对应最大速度speed）*/
                    rest2 = 0;                               /* 清零余值 */
                    g_srd2.run_state = RUN;                  /* 设置为匀速运行状态 */
                }
                break;

            case RUN:
                g_add_pulse_count2++;
                step_count2++;                               /* 步数加1 */
                if(g_srd2.dir == CW)
                {
                    g_step_position2++;                      /* 绝对位置加1 */
                }
                else
                {
                    g_step_position2--;                      /* 绝对位置减1*/
                }
                new_step_delay2 = g_srd2.min_delay;           /* 使用min_delay（对应最大速度speed）*/
                if(step_count2 >= g_srd2.decel_start)         /* 需要开始减速 */
                {
                    g_srd2.accel_count = g_srd2.decel_val;    /* 减速步数做为加速计数值 */
                    new_step_delay2 = last_accel_delay2;      /* 加阶段最后的延时做为减速阶段的起始延时(脉冲周期) */
                    g_srd2.run_state = DECEL;                /* 状态改变为减速 */
                }
                break;

            case DECEL:
                step_count2++;                               /* 步数加1 */
                g_add_pulse_count2++;
                if(g_srd2.dir == CW)
                {
                    g_step_position2++;                      /* 绝对位置加1 */
                }
                else
                {
                    g_step_position2--;                      /* 绝对位置减1 */
                }
                g_srd2.accel_count++;
                new_step_delay2 = g_srd2.step_delay - (((2 * g_srd2.step_delay) + rest2)/(4 * g_srd2.accel_count + 1));  /* 计算新(下)一步脉冲周期(时间间隔) */
                rest2 = ((2 * g_srd2.step_delay)+rest2)%(4 * g_srd2.accel_count + 1);                                   /* 计算余数，下次计算补上余数，减少误差 */

                /* 检查是否为最后一步 */
                if(g_srd2.accel_count >= 0)                  /* 判断减速步数是否从负值加到0是的话 减速完成 */
                {
                    g_srd2.run_state = STOP;
                }
                break;
            }
            g_srd2.step_delay = new_step_delay2;              /* 为下个(新的)延时(脉冲周期)赋值 */
        }
        }
        else
        {
            tim_count2=TIM1->CNT;
            tmp2 = tim_count2+tim_add_distance2; 
            TIM_SetCompare2(TIM1, tmp2);
        }
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);
        TIM_ClearFlag(TIM1,TIM_FLAG_CC2) ;
    }
    
    if (TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)
    {
        if(tim_rush_state3==0)
        {
        tim_count=TIM1->CNT;
        tmp = tim_count + g_srd.step_delay/2;
        TIM_SetCompare3(TIM1, tmp);
        i++;                                                /* 定时器中断次数计数值 */
        if(i == 2)                                          /* 2次，说明已经输出一个完整脉冲 */
        {
            i = 0;                                          /* 清零定时器中断次数计数值 */
            switch(g_srd.run_state)                         /* 加减速曲线阶段 */
            {
            case STOP:
                step_count = 0;                             /* 清零步数计数器 */
                rest = 0;                                   /* 清零余值 */
                /* 关闭通道*/
                TIM_ITConfig(TIM1,TIM_IT_CC3,DISABLE);
                TIM_CCxCmd(TIM1,TIM_Channel_3,TIM_CCx_Disable);
//                ST3_EN(EN_OFF);
                g_motion_sta = 0;                           /* 电机为停止状态  */
                break;

            case ACCEL:
                g_add_pulse_count++;                        /* 只用于记录相对位置转动了多少度 */
                step_count++;                               /* 步数加1*/
                if(g_srd.dir == CW)
                {
                    g_step_position++;                      /* 绝对位置加1  记录绝对位置转动多少度*/
                }
                else
                {
                    g_step_position--;                      /* 绝对位置减1*/
                }
                g_srd.accel_count++;                        /* 加速计数值加1*/
                new_step_delay = g_srd.step_delay - (((2 *g_srd.step_delay) + rest)/(4 * g_srd.accel_count + 1));/* 计算新(下)一步脉冲周期(时间间隔) */
                                //g_srd.step_delay - (((2 * g_srd.step_delay) + rest)/(4 * g_srd.accel_count + 1));
                rest = ((2 * g_srd.step_delay)+rest)%(4 * g_srd.accel_count + 1);                                /* 计算余数，下次计算补上余数，减少误差 */
                if(step_count >= g_srd.decel_start)         /* 检查是否到了需要减速的步数 */
                {
                    g_srd.accel_count = g_srd.decel_val;    /* 加速计数值为减速阶段计数值的初始值 */
                    g_srd.run_state = DECEL;                /* 下个脉冲进入减速阶段 */
                }
                else if(new_step_delay <= g_srd.min_delay)  /* 检查是否到达期望的最大速度 计数值越小速度越快，当你的速度和最大速度相等或更快就进入匀速*/
                {
                    last_accel_delay = new_step_delay;      /* 保存加速过程中最后一次延时（脉冲周期）*/
                    new_step_delay = g_srd.min_delay;       /* 使用min_delay（对应最大速度speed）*/
                    rest = 0;                               /* 清零余值 */
                    g_srd.run_state = RUN;                  /* 设置为匀速运行状态 */
                }
                break;

            case RUN:
                g_add_pulse_count++;
                step_count++;                               /* 步数加1 */
                if(g_srd.dir == CW)
                {
                    g_step_position++;                      /* 绝对位置加1 */
                }
                else
                {
                    g_step_position--;                      /* 绝对位置减1*/
                }
                new_step_delay = g_srd.min_delay;           /* 使用min_delay（对应最大速度speed）*/
                if(step_count >= g_srd.decel_start)         /* 需要开始减速 */
                {
                    g_srd.accel_count = g_srd.decel_val;    /* 减速步数做为加速计数值 */
                    new_step_delay = last_accel_delay;      /* 加阶段最后的延时做为减速阶段的起始延时(脉冲周期) */
                    g_srd.run_state = DECEL;                /* 状态改变为减速 */
                }
                break;

            case DECEL:
                step_count++;                               /* 步数加1 */
                g_add_pulse_count++;
                if(g_srd.dir == CW)
                {
                    g_step_position++;                      /* 绝对位置加1 */
                }
                else
                {
                    g_step_position--;                      /* 绝对位置减1 */
                }
                g_srd.accel_count++;
                new_step_delay = g_srd.step_delay - (((2 * g_srd.step_delay) + rest)/(4 * g_srd.accel_count + 1));  /* 计算新(下)一步脉冲周期(时间间隔) */
                rest = ((2 * g_srd.step_delay)+rest)%(4 * g_srd.accel_count + 1);                                   /* 计算余数，下次计算补上余数，减少误差 */

                /* 检查是否为最后一步 */
                if(g_srd.accel_count >= 0)                  /* 判断减速步数是否从负值加到0是的话 减速完成 */
                {
                    g_srd.run_state = STOP;
                }
                break;
            }
            g_srd.step_delay = new_step_delay;              /* 为下个(新的)延时(脉冲周期)赋值 */
        }
        }
        else
        {
            tim_count=TIM1->CNT;
            tmp = tim_count+tim_add_distance3; 
            TIM_SetCompare3(TIM1, tmp);
        }
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);
        TIM_ClearFlag(TIM1,TIM_FLAG_CC3) ;
    }
    if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)
    {
        if(tim_rush_state4==0)
        {
        tim_count4=TIM1->CNT;
        tmp4 = tim_count4 + g_srd4.step_delay/2;
        TIM_SetCompare4(TIM1, tmp4);
        i4++;                                                /* 定时器中断次数计数值 */
        if(i4 == 2)                                          /* 2次，说明已经输出一个完整脉冲 */
        {
            i4 = 0;                                          /* 清零定时器中断次数计数值 */
            switch(g_srd4.run_state)                         /* 加减速曲线阶段 */
            {
            case STOP:
                step_count4 = 0;                             /* 清零步数计数器 */
                rest4 = 0;                                   /* 清零余值 */
                /* 关闭通道*/
                TIM_ITConfig(TIM1,TIM_IT_CC4,DISABLE);
                TIM_CCxCmd(TIM1,TIM_Channel_4,TIM_CCx_Disable);
//                ST4_EN(EN_OFF);
                g_motion_sta4 = 0;                           /* 电机为停止状态  */
                break;

            case ACCEL:
                g_add_pulse_count4++;                        /* 只用于记录相对位置转动了多少度 */
                step_count4++;                               /* 步数加1*/
                if(g_srd4.dir == CW)
                {
                    g_step_position4++;                      /* 绝对位置加1  记录绝对位置转动多少度*/
                }
                else
                {
                    g_step_position4--;                      /* 绝对位置减1*/
                }
                g_srd4.accel_count++;                        /* 加速计数值加1*/
                new_step_delay4 = g_srd4.step_delay - (((2 *g_srd4.step_delay) + rest4)/(4 * g_srd4.accel_count + 1));/* 计算新(下)一步脉冲周期(时间间隔) */
                                //g_srd.step_delay - (((2 * g_srd.step_delay) + rest)/(4 * g_srd.accel_count + 1));
                rest4 = ((2 * g_srd4.step_delay)+rest4)%(4 * g_srd4.accel_count + 1);                                /* 计算余数，下次计算补上余数，减少误差 */
                if(step_count4 >= g_srd4.decel_start)         /* 检查是否到了需要减速的步数 */
                {
                    g_srd4.accel_count = g_srd4.decel_val;    /* 加速计数值为减速阶段计数值的初始值 */
                    g_srd4.run_state = DECEL;                /* 下个脉冲进入减速阶段 */
                }
                else if(new_step_delay4 <= g_srd4.min_delay)  /* 检查是否到达期望的最大速度 计数值越小速度越快，当你的速度和最大速度相等或更快就进入匀速*/
                {
                    last_accel_delay4 = new_step_delay4;      /* 保存加速过程中最后一次延时（脉冲周期）*/
                    new_step_delay4 = g_srd4.min_delay;       /* 使用min_delay（对应最大速度speed）*/
                    rest4 = 0;                               /* 清零余值 */
                    g_srd4.run_state = RUN;                  /* 设置为匀速运行状态 */
                }
                break;

            case RUN:
                g_add_pulse_count4++;
                step_count4++;                               /* 步数加1 */
                if(g_srd4.dir == CW)
                {
                    g_step_position4++;                      /* 绝对位置加1 */
                }
                else
                {
                    g_step_position4--;                      /* 绝对位置减1*/
                }
                new_step_delay4 = g_srd4.min_delay;           /* 使用min_delay（对应最大速度speed）*/
                if(step_count4 >= g_srd4.decel_start)         /* 需要开始减速 */
                {
                    g_srd4.accel_count = g_srd4.decel_val;    /* 减速步数做为加速计数值 */
                    new_step_delay4 = last_accel_delay4;      /* 加阶段最后的延时做为减速阶段的起始延时(脉冲周期) */
                    g_srd4.run_state = DECEL;                /* 状态改变为减速 */
                }
                break;

            case DECEL:
                step_count4++;                               /* 步数加1 */
                g_add_pulse_count4++;
                if(g_srd4.dir == CW)
                {
                    g_step_position4++;                      /* 绝对位置加1 */
                }
                else
                {
                    g_step_position4--;                      /* 绝对位置减1 */
                }
                g_srd4.accel_count++;
                new_step_delay4 = g_srd4.step_delay - (((2 * g_srd4.step_delay) + rest4)/(4 * g_srd4.accel_count + 1));  /* 计算新(下)一步脉冲周期(时间间隔) */
                rest4 = ((2 * g_srd4.step_delay)+rest4)%(4 * g_srd4.accel_count + 1);                                   /* 计算余数，下次计算补上余数，减少误差 */

                /* 检查是否为最后一步 */
                if(g_srd4.accel_count >= 0)                  /* 判断减速步数是否从负值加到0是的话 减速完成 */
                {
                    g_srd4.run_state = STOP;
                }
                break;
            }
            g_srd4.step_delay = new_step_delay4;              /* 为下个(新的)延时(脉冲周期)赋值 */
        }
        }
        else
        {
            tim_count4=TIM1->CNT;
            tmp4 = tim_count4+tim_add_distance4; 
            TIM_SetCompare4(TIM1, tmp4);
        }
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);
        TIM_ClearFlag(TIM1,TIM_FLAG_CC4) ;
    }
}




void zero_clearing(void)
 {          g_motion_sta2=0;
			g_motion_sta=0; 
			g_motion_sta4=0;
			g_motion_sta1=0;
			tim_rush_state1=0;
			tim_rush_state2=0;
			tim_rush_state3=0;
			tim_rush_state4=0;
	}
 
	void zero_fill(void)
 {          g_motion_sta2=1;
			g_motion_sta=1; 
			g_motion_sta4=1;
			g_motion_sta1=1;
			tim_rush_state1=1;
			tim_rush_state2=1;
			tim_rush_state3=1;
			tim_rush_state4=1;
	}
