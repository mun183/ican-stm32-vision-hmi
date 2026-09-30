#ifndef __USART5_DMA_H
#define __USART5_DMA_H	 
#include "sys.h"
//#include "control.h"

void USART5_Init(int Baud);
void data5_process(void);
void usart5_board_senddata(uint8_t flag1);
void usart5_board_command(uint16_t command1,uint16_t command2,uint16_t command3);
extern u8 USART_RX5_BUF[128];  // Ω” ’ª∫≥Â«¯
void usart5_CKPM(void);

#endif
