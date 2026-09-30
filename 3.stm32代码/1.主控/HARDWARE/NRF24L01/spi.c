/*
******************************************************************************************************************
*Filename      :spi3.c
*Programmer(s) :?????
*Description   :2019??
******************************************************************************************************************
*/

#include "sys.h"
#include "spi3.h"

/*
*****************************************************************************************************************
*                                     void Motor_SPI3_Init()
*
*Description : NRF_24L01?SPI3?????
*Arguments   : none
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void NRF_SPI3_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//??GPIOB??
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);//??SPI3??

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//PB3~5??????	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//????
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??
	GPIO_Init(GPIOB, &GPIO_InitStructure);//???

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI3); //PB13??? SPI3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI3); //PB14??? SPI3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI3); //PB15??? SPI3

	//?????SPI????
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,ENABLE);//??SPI3
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,DISABLE);//????SPI3
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //??SPI???????????:SPI??????????
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//??SPI????:????SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//??SPI?????:SPI????8????
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//???????????????
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//????????1????(?????)?????
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS?????(NSS??)????(??SSI?)??:??NSS???SSI???
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//??????????:????????256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//???????MSB???LSB???:?????MSB???
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC???????
	SPI_Init(SPI3, &SPI_InitStructure);  //??SPI_InitStruct???????????SPIx???

	SPI_Cmd(SPI3, ENABLE); //??SPI??
//	NRF_SPI3_ReadWriteByte(0xff);//????
}


/*
*****************************************************************************************************************
*                                     void NRF_SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
*
*Description : Motor_SPI3??????
*Arguments   : SPI??=fAPB2/????
                          @ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
                           fAPB2?????84Mhz:
*Returns     : none
*Notes       : none
*******************************************************************************************************************
*/
void NRF_SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//?????

	SPI3->CR1&=0XFFC7;//?3-5??,???????
	SPI3->CR1|=SPI_BaudRatePrescaler;	//??SPI3?? 
	SPI_Cmd(SPI3,ENABLE); //??SPI3
} 

/*
*****************************************************************************************************************
*                                     u8 NRF_SPI3_ReadWriteByte(u8 TxData)
*
*Description : Motor_SPI3 ??????
*Arguments   : TxData:??????:
*Returns     : ??????
*Notes       : none
*******************************************************************************************************************
*/
u8 NRF_SPI3_ReadWriteByte(u8 TxData)
{
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){}//??????  

	SPI_I2S_SendData(SPI3, TxData); //????SPIx????byte  ??
		
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){} //???????byte  

	return SPI_I2S_ReceiveData(SPI3); //????SPIx???????	
}


