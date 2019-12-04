#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "stm32f4xx.h"
#include <stdint.h>

/*--------------------------------------------------------
模糊控制
--------------------------------------------------------*/
void fuzzy_ctr_x(void);
void fuzzy_ctr_y(void);

/*--------------------------------------------------------
前馈控制
--------------------------------------------------------*/
void forward_setup_x(float Xtarget);
void forward_setup_y(float Ytarget);
void forward_ctr_x(void);
void forward_ctr_y(void);

/*--------------------------------------------------------
PID控制
--------------------------------------------------------*/
//设置
void pid_setup_velocity(double target);

void pid_setup_tension(double target);

//控制
void pid_ctr_velocity(void);

void pid_ctr_tension(void);







#endif




