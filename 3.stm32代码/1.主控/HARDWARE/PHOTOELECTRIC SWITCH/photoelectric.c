#include "photoelectric.h"
#include "delay.h"
#include "stm32f4xx_gpio.h"
//---------------光电管------------------//
void fan1_close(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_4|GPIO_Pin_5);
}

void fan2_close(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_12|GPIO_Pin_15);
}
void fan1_open(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOA, GPIO_Pin_4|GPIO_Pin_5);
}

void fan2_open(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOA, GPIO_Pin_12|GPIO_Pin_15);
}

void huifengtongdao_close(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_6|GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_9);
}

void huifengtongdao_open(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 设置为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 设置最大速率为 100MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 禁用上下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_6|GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_9);
}


