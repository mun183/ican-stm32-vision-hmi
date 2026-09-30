#ifndef __PHOTOELECTRIC_H
#define __PHOTOELECTRIC_H

#include "sys.h"


#define GUANGDIAN1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define GUANGDIAN2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define GUANGDIAN3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)
#define GUANGDIAN4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)

/****************º¯ÊýÉùÃ÷********************/
void GUANGDIAN_GPIO_Init(void);
void clean_open(void);
void clean_close(void);
void Ultraviolet_up_on(void);
void Ultraviolet_up_off(void);
void Ultraviolet_middle_on(void);
void Ultraviolet_middle_off(void);
void Ultraviolet_down_on(void);
void Ultraviolet_down_off(void);
#endif
