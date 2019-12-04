//-----------------------------------------------------------------------------
//  Created on	: 2017-8-9
//      Author	: ZB
//		version	: V1.0
//		brief	: Pid Forward Fuzzy Control
//-----------------------------------------------------------------------------
#include "Algorithm.h"
#include "forward.h"
#include "APP\Math\My_Math.h"
#include "APP\Control\param.h"
#include "includes.h"
#include <stdint.h>
#include "BSP\Time\Time.h"
#include "pid.h"
#include "BSP\Motor_Drive\Moto_Drive.h"
#include "BSP\Motor_Drive\Wind_Moto.h"
#include "APP\IMU\ahrs.h"
#include "BSP\MCU\UART\usart3.h"
#include "APP\Car\Car.h"
#include "APP\ANO_DT\ANO_DT.h"
#include "APP\Math\My_Math.h"
#include "APP\Control\param.h"
#include "BSP\MPU6050\MPU6050.h"
#include "BSP\Motor_Drive\Steer_Moto.h"
#include "APP\Tensile\Tensile.h"
#include "BSP\ESCON\ESCON.h"

void pid_setup_velocity(double target)
{
    update_pid_param(&pid_velocity,pidvelocityparam,target);
}

void pid_ctr_velocity(void)
{
    float value;
    value = pid_inc_calc(&pid_velocity, Tensile.LVDT.velocity);
    ESCON_PWM_Set(value);
}

void pid_setup_tension(double target)
{
	update_pid_param(&pid_tension,pidtensionparam,target);
}

void pid_ctr_tension(void)
{

}
