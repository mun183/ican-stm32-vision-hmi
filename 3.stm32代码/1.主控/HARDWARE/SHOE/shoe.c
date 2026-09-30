#include "usartdma.h"
#include "led.h"
#include "oled.h"
#include "usart2dma.h"
#include "dianji.h"
#include "shoe.h"
#include "usart5dma.h"
#include "delay.h"
#include "usart3dma.h"


void Clean_middle()
{
			moveServo(0, 1500, 500); //1号舵机至500位置
			moveServo(1, 1500, 500); //1号舵机至500位置
			moveServo(2, 1500, 500); //1号舵机至500位置
}

void Clean_down()
{
			moveServo(0, 1300, 500); //1号舵机至500位置
			moveServo(1, 1500, 500); //1号舵机至500位置
			moveServo(2, 1900, 500); //1号舵机至500位置
}

