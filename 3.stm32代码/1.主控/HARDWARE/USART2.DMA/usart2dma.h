#ifndef __USART2_DMA_H
#define __USART2_DMA_H	 
#include "sys.h"

extern u8  USART_RX2_BUF[128];  // Ω” ’ª∫≥Â«¯
extern u16 USART_RX2_STA ;
extern u8 receive2_count; 
void USART2_Init(int Baud);

#endif
