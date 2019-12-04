#ifndef __Tensile_H_
#define __Tensile_H_
#include "sys.h"
#include "BSP\SYSTEM\My_Flag.h"

/* 位移传感器信息 */
typedef struct{
    
    double position;             //当前位移(um)
    double target_postion;
    double offset_position;
    
    double velocity;             //试样速度(um/s)
    double target_velocity;
    double offset_velocity;
    
    int32_t range;              //量程(mm)
    int32_t output_max;         //输出最大值(V)
    int32_t output_min;         //输出最小值(V)

}sLVDT_Typedef;

/* 拉力传感器信息 */
typedef struct{
    
    double tension;             //当前拉力(N)
    double target_tension;
    double offset_tension;
    
    int32_t range;              //量程(N)
    int32_t output_max;         //输出最大值(V)
    int32_t output_min;         //输出最小值(V)

}sTensionSensor_Typedef;

enum Tensile_state{
    Running,
    Preparing,
    Stop
};

enum Tensile_Mode{
    CVelocity,                  //恒速度模式
    CTension                   //恒拉力模式
};

/* 拉伸实验机信息 */
typedef struct
{
    
    sLVDT_Typedef LVDT;         //位移传感器实体
    
    sTensionSensor_Typedef TensionSensor;    //拉力传感器实体

    enum Tensile_state state;   //机器运行状态
    enum Tensile_Mode mode;     //机器运行方式
}sTensile_Typedef;

extern sTensile_Typedef Tensile;     //小车信息

/**********************************************
* 拉伸实验机参数初始化
**********************************************/
void Tensile_Init(void);

/**********************************************
* 拉伸实验机传感器数据校准
**********************************************/
void Tensile_Calibrate(void);

/**********************************************
* 读拉力传感器
**********************************************/
void Tensile_Read_TensionSensor(void);

/**********************************************
* 读位移传感器
**********************************************/
void Tensile_Read_LVDT(void);


#endif /* __Tensile_H_ */
