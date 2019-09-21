#ifndef _MECANUM_H
#define _MECANUM_H
#include "sys.h"
#include <string.h>
#include <stdio.h>
#include "BSP\SYSTEM\My_Flag.h"
#include "APP\Control\param.h"
#include "BSP\PS2\PS2.h"

// -----用到的UART口-----
// USART1 -- 1
// USART2 -- 2
// USART3 -- 3
// USART4 -- 4
#define MECANUM_UART_PORT_SELECT 3

// 通信UART口定义
#if (MECANUM_UART_PORT_SELECT == 1)
#include "BSP\SYSTEM\usart\Printf_Uart.h"
#define MECANUM_UART_PORT USART1
#define MECANUM_UART_IRQHandler USART1_IRQHandler
#elif (MECANUM_UART_PORT_SELECT == 2)
#include "BSP/MCU/UART/usart2.h"
#define MECANUM_UART_PORT USART2
#define MECANUM_UART_IRQHandler USART2_IRQHandler
#elif (MECANUM_UART_PORT_SELECT == 3)
#include "BSP/MCU/UART/usart3.h"
#define MECANUM_UART_PORT USART3
#define MECANUM_UART_IRQHandler USART3_IRQHandler
#elif (MECANUM_UART_PORT_SELECT == 4)
#include "BSP/MCU/UART/usart4.h"
#define MECANUM_UART_PORT USART4
#define MECANUM_UART_IRQHandler USART4_IRQHandler
#else
#error "Please define MECANUM_UART_PORT!!!"
#endif


#define a_PARAMETER  (0.183f) //x方向
#define b_PARAMETER  (0.1735f) //y方向

typedef struct
{
    Flag Move;
    Flag Right;
    Flag Left;
}State_Flag;

enum Run_Mode{
    Speed,
    Position,
    Hover
};


// 小车麦轮编号
//     头
//   B—^—C
//   |   |
//   A—^—D
//    尾

typedef struct
{
    /* PID控制相关变量 */
    long int Position_A;
    long int Position_B;
    long int Position_C;
    long int Position_D;
    long int Rate_A;
    long int Rate_B;
    long int Rate_C;
    long int Rate_D;

    /* 编码器值 */
    long int Encoder_A;
    long int Encoder_B;
    long int Encoder_C;
    long int Encoder_D;

    /* 电机目标值 */
    long int Target_A;
    long int Target_B;
    long int Target_C;
    long int Target_D;

    /* 电机pwm */
    long int Moto_A;
    long int Moto_B;
    long int Moto_C;
    long int Moto_D;    

    /* XYZ轴目标速度 */
    float Move_X;
    float Move_Y;
    float Move_Z;

    /* 速度限幅 */
    float RC_Velocity;
    /* 位置限幅 */
    float RC_Position;

    /* 运行模式标志位 speed:速度模式    position:位置模式 */
    enum Run_Mode Run_Mode_Flag; 

    /* 转向标志位 */
    Flag Turn_Flag;

    /* 运行状态标志位 */
    State_Flag Move_Flag;

    /* 运行方向标志位 */
    u8 Direction_Index;

    /* 陀螺仪比例系数 */
    float Gyro_K;     				  											//陀螺仪比例系数
}sMecanum_Typedef;

extern sMecanum_Typedef Mecanum;
extern u8 rxbuf[8],Usart_ON_Flag; //串口PS2控制相关变量

void Mecanum_Param_Init(void);
void Mecanum_Update(int A,int B,int C,int D);
void Kinematic_Analysis(float Vx,float Vy,float Vz);
void Kinematic_Analysis2(float Vx,float Vy,float Vz);
void Get_RC(Flag mode);
void Count_Velocity(void);
void Count_Velocity(void);
void PS2_Usart_Control(void);
u8 click_RC (void);

#endif /* _MECANUM_H */
