/*
******************************************************************************************************************
*Filename      :spi3.h
*Programmer(s) :?????
*Description   :2019??
******************************************************************************************************************
*/

#ifndef __SPI3_H
#define __SPI3_H
#include "sys.h"



void NRF_SPI3_Init(void);			 //???SPI1?
void NRF_SPI3_SetSpeed(u8 SPI_BaudRatePrescaler);
u8   NRF_SPI3_ReadWriteByte(u8 TxData);//SPI1????????

#endif

