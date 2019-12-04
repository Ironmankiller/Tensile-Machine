#include "BSP\Time\Time.h"
#include <stdio.h>
#include "APP\Control\pid.h"
#include "APP\Control\control.h"
#include "forward.h"
#include "param.h"
#include "Algorithm.h"
#include "BSP\SYSTEM\My_Flag.h"
#include "APP\Math\My_Math.h"
#include "BSP\MCU\UART\usart3.h"
#include "BSP\MCU\UART\usart2.h"
#include "APP\Pan_Tilt\Pan_Tilt.h"
#include "BSP\SYSTEM\usart\Printf_Uart.h"
#include "APP\Tensile\Tensile.h"
#include "BSP\ESCON\ESCON.h"

Flag Init_flag = MY_TRUE;
/**********************************************
* 拉伸实验机恒速度运行
**********************************************/
void Control_Velocity(void){
    
    if(Init_flag == MY_TRUE) {
        Init_flag = MY_FALSE;
        pid_setup_velocity(Tensile.LVDT.target_velocity);
    }
    pid_ctr_velocity();
}

/**********************************************
* 拉伸实验机恒力运行
**********************************************/
void Control_Strength(void){

}

/**********************************************
* 拉伸实验机停止运行
**********************************************/
void Control_Stop(void){
    ESCON_PWM_Set(0);
}

/**********************************************
* 拉伸实验机快速卸力
**********************************************/
void Control_Preparing(void){
    ESCON_PWM_Set(-16800);
}
