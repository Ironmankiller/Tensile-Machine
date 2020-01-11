//-----------------------------------------------------------------------------
//  Created on	: 2017-8-9
//      Author	: ZB
//		version	: V1.0
//		brief	: Pid Forward Fuzzy Control
//-----------------------------------------------------------------------------
#include "Algorithm.h"
#include "sys.h"

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
