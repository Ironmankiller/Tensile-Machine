#ifndef __OLED_H
#define __OLED_H

#include <stdint.h>
#include "delay.h"
#include "sys.h"


//-----------------OLED端口定义---------------- 
#define OLED_RST_GPIO_PORT                GPIOD
#define OLED_RST_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define OLED_RST_GPIO_PIN                 GPIO_Pin_5

#define OLED_RS_GPIO_PORT                 GPIOD
#define OLED_RS_GPIO_CLK                  RCC_AHB1Periph_GPIOD
#define OLED_RS_GPIO_PIN                  GPIO_Pin_4

#define OLED_SCLK_GPIO_PORT               GPIOD
#define OLED_SCLK_GPIO_CLK                RCC_AHB1Periph_GPIOD
#define OLED_SCLK_GPIO_PIN                GPIO_Pin_7

#define OLED_SDIN_GPIO_PORT               GPIOD
#define OLED_SDIN_GPIO_CLK                RCC_AHB1Periph_GPIOD
#define OLED_SDIN_GPIO_PIN                GPIO_Pin_6

#define OLED_RST_Clr()      PDout(5) = 0    //RST
#define OLED_RST_Set()      PDout(5) = 1    //RST

#define OLED_RS_Clr()       PDout(4) = 0    //DC
#define OLED_RS_Set()       PDout(4) = 1    //DC

#define OLED_SCLK_Clr()     PDout(7) = 0    //SCL D0
#define OLED_SCLK_Set()     PDout(7) = 1    //SCL

#define OLED_SDIN_Clr()     PDout(6) = 0    //SDA D1
#define OLED_SDIN_Set()     PDout(6) = 1    //SDA

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//OLED控制用函数
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p);	
void OLED_ShowFloat(uint8_t x, uint8_t y, float p);

void OLED_ShowInt(uint8_t x, uint8_t y, int32_t a);

#endif  
	 
