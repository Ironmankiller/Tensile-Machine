#ifndef __LED_H
#define __LED_H

/***************LED GPIO定义******************/
#define LED_1_GPIO_PORT               GPIOE
#define LED_1_GPIO_CLK                RCC_AHB1Periph_GPIOE
#define LED_1_GPIO_PIN                GPIO_Pin_4

#define LED_2_GPIO_PORT               GPIOE
#define LED_2_GPIO_CLK                RCC_AHB1Periph_GPIOE
#define LED_2_GPIO_PIN                GPIO_Pin_1

#define LED_3_GPIO_PORT               GPIOE
#define LED_3_GPIO_CLK                RCC_AHB1Periph_GPIOE
#define LED_3_GPIO_PIN                GPIO_Pin_6

#define LED_4_GPIO_PORT               GPIOE
#define LED_4_GPIO_CLK                RCC_AHB1Periph_GPIOE
#define LED_4_GPIO_PIN                GPIO_Pin_6

#define LED4_ON  PCout(13) = 0;
#define LED4_OFF PCout(13) = 1;

#define LED3_ON  PEout(6) = 0;
#define LED3_OFF PEout(6) = 1;

#define LED2_ON  PEout(1) = 0;
#define LED2_OFF PEout(1) = 1;

#define LED1_ON  PEout(4) = 0;
#define LED1_OFF PEout(4) = 1;

/*********************************************/

enum LED_Num {
	LED_1,
	LED_2,
	LED_3,
	LED_4,
	LED_5,
	LED_6
};

/**********************************************
* 初始化LED
**********************************************/
void LED_Init(void);

/**********************************************
* 开灯
**********************************************/
void LED_ON(enum LED_Num led);

/**********************************************
* 关灯
**********************************************/
void LED_OFF(enum LED_Num led);

/**********************************************
* 切换
**********************************************/
void LED_SWITCH(enum LED_Num led);

/**********************************************
* 开启全部LED
**********************************************/
void LED_ALL_ON(void);

/**********************************************
* 关闭全部LED
**********************************************/
void LED_ALL_OFF(void);

/**********************************************
* 闪烁某个LED
* 由50ms定时任务调用
**********************************************/
void LED_Blink(enum LED_Num led);


#endif
