#ifndef __USART1_DMA_H
#define __USART1_DMA_H	 
#include "sys.h"

extern u8  USART_RX1_BUF[128];;  // Ω” ’ª∫≥Â«¯
extern u16 USART_RX1_STA ;

void USART1_Init(int Baud);
void USART_Senddatas(USART_TypeDef* USARTxx,u8* addr,int size);

#endif
