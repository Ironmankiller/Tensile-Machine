#ifndef __Tensile_H_
#define __Tensile_H_

#include "BSP\SYSTEM\My_Flag.h"

enum Tensile_state{
    Running,
    Preparing,
    Stop
};

enum Tensile_Mode{
    CVelocity,                  //恒速度模式
    CStrength                   //恒拉力模式
};

/* 拉伸实验机信息 */
typedef struct
{
    float velocity;             //试样位移(us/s)
    float strength;             //对试样施加的拉力(N)
    
    float target_velocity;
    float target_strength;
    
    float offset_velocity;
    float offset_strength;

    enum Tensile_state state;   //机器运行状态
    enum Tensile_Mode mode;     //机器运行方式
}sTensile_Typedef;

extern sTensile_Typedef Tensile;     //小车信息

/**********************************************
* 拉伸实验机参数初始化
**********************************************/
void Tensile_Init(void);

/**********************************************
* 拉伸实验机参数初更新
**********************************************/
void Tensile_Param_Update(float velocity, float strength);

/**********************************************
* 拉伸实验机传感器数据校准
**********************************************/
void Tensile_Calibrate(void);

#endif /* __Tensile_H_ */
