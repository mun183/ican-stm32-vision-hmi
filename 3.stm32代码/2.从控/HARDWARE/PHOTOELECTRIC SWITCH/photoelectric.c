#include "photoelectric.h"
#include "delay.h"
#include "stm32f4xx_gpio.h"
//---------------光电管------------------//
void GUANGDIAN_GPIO_Init(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_12|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//---------------刷鞋机构IO20对应PA7----------------//
void clean_open(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
}


void clean_close(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
}
//-----------------------------紫外线-------------------------//
//---------------------------上层紫外线------------------------//IO19对应PA6
void Ultraviolet_up_on(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
}
void Ultraviolet_up_off(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
}
//---------------------------手机紫外线------------------------//IO18对应PB9
void Ultraviolet_middle_on(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
}
void Ultraviolet_middle_off(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
}
//---------------------------鞋子紫外线------------------------//IO17对应PB8
void Ultraviolet_down_on(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
}
void Ultraviolet_down_off(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
}

