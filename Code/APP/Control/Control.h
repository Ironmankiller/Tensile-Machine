#ifndef __CONTROL_H
#define __CONTROL_H

#include "My_Flag.h"
#include <stdint.h>
#include "param.h"

void Control_Velocity(void);
void Control_Strength(void);
void Control_Stop(void);
void Control_Preparing(void);

extern int flag;
extern Flag Init_flag;
#endif // !__CONTROL_H
