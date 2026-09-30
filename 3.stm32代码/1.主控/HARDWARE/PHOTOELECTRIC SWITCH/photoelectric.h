#ifndef __PHOTOELECTRIC_H
#define __PHOTOELECTRIC_H

#include "sys.h"


//#define GUANGDIAN1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
//#define GUANGDIAN2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
//#define GUANGDIAN3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)
//#define GUANGDIAN4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)
//#define GUANGDIAN5 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
//#define GUANGDIAN6 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)
//#define GUANGDIAN7 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
//#define GUANGDIAN8 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)
/****************º¯ÊýÉùÃ÷********************/
void fan1_open(void);
void fan2_open(void);
void fan1_close(void);
void fan2_close(void);
void huifengtongdao_open(void);
void huifengtongdao_close(void);

#endif
