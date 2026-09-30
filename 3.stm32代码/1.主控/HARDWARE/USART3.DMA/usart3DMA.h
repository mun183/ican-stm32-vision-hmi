/*
******************************************************************************************************************
*Filename      :usart3_dma.h
*Programmer(s) :chu
*Description   :Design for usart3_dma

							 USART3_RX---PD9
							 USART3_TX---PD8
******************************************************************************************************************
*/
#ifndef __USART3_DMA_H
#define __USART3_DMA_H	 
#include "sys.h"
#include "stdio.h"

//使用USART3时开启，不用可以注释
#define U3_DATA_LEN  60
#define USART3_REC_LEN  	64  	//定义最大接收字节数 200

extern u8  USART3_RX_BUF[USART3_REC_LEN];		//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART3_RX_STA;  
extern u8 connect_flag;//连接标志
extern u8 rec_data_u3[U3_DATA_LEN];   // 接收数据
extern u8 send_data_u3[U3_DATA_LEN];   
/*
******************************************************************************************************************
*                                                 FUNCTION PROTOTYPES
*                                                   串口3用函数
******************************************************************************************************************
*/
void USART3_Init(u32 bound);
//void USART3_Init(int Baud);
#define FRAME_HEADER 0x55             //帧头
#define CMD_SERVO_MOVE 0x03           //舵机移动指令
#define CMD_ACTION_GROUP_RUN 0x06     //运行动作组指令
#define CMD_ACTION_GROUP_STOP 0x07    //停止动作组指令
#define CMD_ACTION_GROUP_SPEED 0x0B   //设置动作组运行速度
#define CMD_GET_BATTERY_VOLTAGE 0x0F  //获取电池电压指令

typedef enum {
	false = 0, true = !false
}bool;

extern bool isUartRxCompleted;
extern uint8_t LobotRxBuf[16];
extern uint16_t batteryVolt;
extern void receiveHandle(void);

typedef struct _lobot_servo_ {  //舵机ID,舵机目标位置
	uint8_t ID;
	uint16_t Position;
} LobotServo;


void moveServo(uint8_t servoID, uint16_t Position, uint16_t Time);
void moveServosByArray(LobotServo servos[], uint8_t Num, uint16_t Time);
void moveServos(uint8_t Num, uint16_t Time, ...);
void runActionGroup(uint8_t numOfAction, uint16_t Times);
void stopActionGroup(void);
void setActionGroupSpeed(uint8_t numOfAction, uint16_t Speed);
void setAllActionGroupSpeed(uint16_t Speed);
void getBatteryVoltage(void);


//-------------------串口舵机-------------------//

void uartWriteBuf(uint8_t *buf, uint8_t len);


#endif
