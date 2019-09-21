#ifndef __Wind_MOTO_DRIVE_H
#define __Wind_MOTO_DRIVE_H

#include <stdint.h>

/**********************************************
* 电机初始化
**********************************************/
void Wind_Moto_Init(void);

/**********************************************
* 设置PWM
**********************************************/
void Wind_Moto_A_Set(int32_t pwm);
void Wind_Moto_B_Set(int32_t pwm);

/**********************************************
* 停止电机
**********************************************/
void Wind_Moto_A_Stop(void);
void Wind_Moto_B_Stop(void);

/**********************************************
* 关闭电机控制
**********************************************/
void Wind_Moto_OFF(void);

/**********************************************
* 关闭电机控制
**********************************************/
void Wind_Moto_ON(void);
/**********************************************
* 电机控制状态改变
**********************************************/
void Wind_Moto_Switch(void);


#endif