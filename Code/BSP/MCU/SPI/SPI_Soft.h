#ifndef _SPI_Soft_H_
#define _SPI_Soft_H_

#include "stm32f4xx.h"
#include "time.h"

/***************SPI GPIO¶¨Òå******************/
#define SOTF_SPI_SCK_PIN                   GPIO_Pin_3                  
#define SOTF_SPI_SCK_GPIO_PORT             GPIOB                       
#define SOTF_SPI_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB

#define SOTF_SPI_MISO_PIN                  GPIO_Pin_4                
#define SOTF_SPI_MISO_GPIO_PORT            GPIOB                   
#define SOTF_SPI_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB


#define SOTF_SPI_MOSI_PIN                  GPIO_Pin_5                
#define SOTF_SPI_MOSI_GPIO_PORT            GPIOB                     
#define SOTF_SPI_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB

#define SOTF_CS_PIN                        GPIO_Pin_6               
#define SOTF_CS_GPIO_PORT                  GPIOG                     
#define SOTF_CS_GPIO_CLK                   RCC_AHB1Periph_GPIOG

/*********************************************/
#define SCS_H           SOTF_CS_GPIO_PORT->BSRRL = SOTF_CS_PIN
#define SCS_L           SOTF_CS_GPIO_PORT->BSRRL = SOTF_CS_PIN
#define SCLK_H          SOTF_SPI_SCK_GPIO_PORT->BSRRL = SOTF_SPI_SCK_PIN
#define SCLK_L          SOTF_SPI_SCK_GPIO_PORT->BSRRH = SOTF_SPI_SCK_PIN
#define SMISO_H         SOTF_SPI_MISO_GPIO_PORT->BSRRL = SOTF_SPI_MISO_PIN
#define SMISO_L         SOTF_SPI_MISO_GPIO_PORT->BSRRH = SOTF_SPI_MISO_PIN

#endif /*_SPI_Soft_H_*/