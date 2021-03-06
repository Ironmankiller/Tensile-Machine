#ifndef __TASK_LOOP_H
#define __TASK_LOOP_H

#include <stdint.h>
#include "My_Flag.h"


/**********************************************
* 清空循环计数标志
**********************************************/
void Loop_Time_Clear(void);

/**********************************************
* 任务循环
* 由主函数初始化完成后调用
**********************************************/
void Task_Loop(void);

/**********************************************
* 任务循环计时
* 由1ms定时中断调用
**********************************************/
void Loop_Time_Check(void);

extern Flag GYRO_Calibrate;

#endif
