//-----------------------------------------------------------------------------
// MY_BSP.c
//
//  Created on	: 2016-7-14
//      Author	: DGVY
//		version	: V1.0
//		brief	:
//-----------------------------------------------------------------------------
// Attention:
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "My_BSP.h"
#include "Printf_Uart.h"
#include "delay.h"
#include "sys.h"
#include "BSP\LED\LED.h"
#include "BSP\MCU\Timer\Timer.h"
#include "BSP\Time\Time.h"
#include "BSP\MCU\SysTick\SysTick.h"
#include "BSP\Motor_Drive\Moto_Drive.h"
#include "BSP\OLED\OLED.h"
#include "BSP\Encoder\Encoder.h"
#include "BSP\BEEP\BEEP.h"
#include "BSP\KEY\KEY.h"
#include "BSP\Motor_Drive\Moto_Drive.h"
#include "BSP\MCU\UART\usart2.h"
#include "BSP\MCU\UART\usart3.h"
#include "BSP\MCU\UART\uart4.h"
#include "BSP\MCU\UART\usart5.h"
#include "BSP\MCU\IIC_Soft\IIC_Soft.h"
#include "BSP\MCU\IIC2\IIC2.h"
#include "BSP\key\Key_Board.h"
#include "BSP\HMI\HMI.h"
#include "BSP\MPU6050\MPU6050.h"
#include "BSP\MPU60502\MPU60502.h"
#include "BSP\Motor_Drive\Step_Moto.h"
#include "BSP\Motor_Drive\Steer_Moto.h"
#include "BSP\Motor_Drive\Wind_Moto.h"
#include "APP\IMU\ahrs.h"
#include "BSP\MCU\SPI\SPI1.h"
#include "BSP\NRF24L01\NRF24L01.h"
#include "BSP\MCU\EXTI\exti.h"
#include "BSP\PS2\PS2.h"
#include "BSP\GY953\GY953.h"
#include "BSP\Mecanum\Mecanum.h"
#include "BSP\ESCON\ESCON.h"
#include "BSP\MCU\ADC\ADC.h"
//-----------------------------------------------------------------------------
// Private Define
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------

//===============================================================================


//-----------------------------------------------------------------------------
// Extern Function
// 外部函数
//-----------------------------------------------------------------------------
/*****************************************************************************\
* Function Name   : Init
* Input           : uint32_t uart_bound     [初始化UART波特率]
*                   uint8_t  delay_sysclk   [系统时钟频率]
* Output          : None
* Return          : None
* Description     : 板级初始化，初始化硬件
*                   默认uart波特率为115200
*                   默认系统时钟为168MHz
\*****************************************************************************/
void BSP_Init(uint32_t uart_bound, uint8_t delay_sysclk)
{
    /* 设置系统中断优先级分组2 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);

    /* 清空系统时间 */
    System_Tiem_Clear();

    /* 初始化滴答定时器 */
    SysTick_Init();

    /* LED初始化 */
    LED_Init();
    LED_ALL_ON();

    /* 蜂鸣器初始化 */
    Beep_Init();

    /* OLED初始化 */
    OLED_Init();

    /* 按键初始化 */
    KEY_Init();
    
    /* 编码器初始化 */ 
    //Encoder_Init_TIM8();
    /* ADC初始化 */
    Adc_Init();
    
    /* 电机初始化 */ 
    ESCON_Init();
    ESCON_PWM_Set(-3250);

    /* UART1初始化 */
    usart1_init(115200);
    /* UART2初始化 */
    usart2_init(115200);
    /* UART3初始化 */        /* 警告：一定先初始化电机pwm再初始化串口，否则pwm可能无法输出 */
    usart3_init(115200);
    /* UART4初始化 */
    uart4_init(115200);
    /* UART5初始化 */
    usart5_init(115200);

    delay_ms(900);
    Beep_Play(100);
    LED_ALL_OFF();
    while(1);
}

/******************* (C) COPYRIGHT 2016 DGVY **********END OF FILE***********/