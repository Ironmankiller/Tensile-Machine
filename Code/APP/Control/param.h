#ifndef _PARAM_H_
#define _PARAM_H_

#include "stm32f4xx.h"
#include "APP\Control\pid.h"
#include "APP\Control\forward.h"

extern pid pid_velocity;
extern pid pid_tension;

extern float pidvelocityparam[11];
extern float pidtensionparam[11];
#endif

