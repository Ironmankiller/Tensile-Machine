#ifndef _ESCON_H_
#define _ESCON_H_
#include "stm32f4xx.h"
#include "sys.h"
#include "Motor_Drive\Moto_Drive.h"

//关于  ESCON 控制引脚的定义
//ESCON使能
#define ESCON_CS_GPIO_PORT               GPIOB
#define ESCON_CS_GPIO_CLK                RCC_AHB1Periph_GPIOB
#define ESCON_CS_GPIO_PIN                GPIO_Pin_9
#define ESCON_ENABLE                     PBout(9) = 1        //电机使能
#define ESCON_DISABLE                    PBout(9) = 0        //电机使能
//ESCON方向控制
#define ESCON_DIR_GPIO_PORT              GPIOB
#define ESCON_DIR_GPIO_CLK               RCC_AHB1Periph_GPIOB
#define ESCON_DIR_GPIO_PIN               GPIO_Pin_8
#define ESCON_POS                        PBout(8) = 1        //电机正转
#define ESCON_NEG                        PBout(8) = 0        //电机反转
//ESCON PWMIO初始化
#define ESCON_TIM_GPIO_PORT              GPIOC
#define ESCON_TIM_GPIO_Pin               GPIO_Pin_6
#define ESCON_TIM_GPIO_PINSOURCE         GPIO_PinSource6
#define ESCON_TIM_GPIO_CLK               RCC_AHB1Periph_GPIOC
//ESCON PWM初始化
#define ESCON_TIM                        TIM3
#define ESCON_TIM_CLK_INIT               RCC_APB1PeriphClockCmd
#define ESCON_TIM_CLK                    RCC_APB1Periph_TIM3
#define ESCON_TIM_AF                     GPIO_AF_TIM3
#define ESCON_TIM_OCInit                 TIM_OC1Init
#define ESCON_TIM_OCPreloadConfig        TIM_OC1PreloadConfig   
#define ESCON_PWM                        TIM3->CCR1          //PA8设置pwm

/**********************************************
* 电机初始化
**********************************************/
void ESCON_Init(void);

/**********************************************
* 电机使能
**********************************************/
void ESCON_EN(unsigned char en);

/**********************************************
* 设置PWM
**********************************************/
void ESCON_PWM_Set(int32_t pwm);

#endif /*_ESCON_H_*/
