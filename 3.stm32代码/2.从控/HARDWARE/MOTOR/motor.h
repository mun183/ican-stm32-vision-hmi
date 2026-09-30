#ifndef __MOTO_H
#define __MOTO_H

#include "sys.h"
//四驱底盘及四轮麦克纳姆轮底盘
//硬件连接说明：
#define steer1_init 400
#define steer2_init 665
#define steer3_init 350
#define steer4_init 670
#define steer1_long 780
#define steer2_long 265
#define steer3_long 765
#define steer4_long 290
extern uint16_t speeda,speedb,speedc,speedd;
extern uint16_t speed_init;
void left_home(void);
void decel_motor_speed(double speed,uint64_t longdistance);
void single_right_long(void);
void decel_motor_speed_long(double speed,uint64_t longdistance);
void back_right_shu_long(float quan);
void no_single_left_long(void);
void decel_motor_speed_long_left(double speed,uint64_t longdistance);
void no_single_right_long(void);
void back_left_shu_long(float quan);
void go_home(float quan);
void correct_car(void);
#endif
