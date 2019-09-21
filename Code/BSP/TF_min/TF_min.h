#ifndef _TF_MIN_H_
#define _TF_MIN_H_
#include "sys.h"

// -----用到的UART口-----
// USART1 -- 1
// USART2 -- 2
// USART3 -- 3
// USART4 -- 4
#define TF_min_UART_PORT_SELECT 2

// 通信UART口定义
#if (TF_min_UART_PORT_SELECT == 1)
#include "BSP\SYSTEM\usart\Printf_Uart.h"
#define TF_min_UART_PORT USART1
#define TF_min_UART_IRQHandler USART1_IRQHandler
#elif (TF_min_UART_PORT_SELECT == 2)
#include "BSP/MCU/UART/usart2.h"
#define TF_min_UART_PORT USART2
#define TF_min_UART_IRQHandler USART2_IRQHandler
#elif (TF_min_UART_PORT_SELECT == 3)
#include "BSP/MCU/UART/usart3.h"
#define TF_min_UART_PORT USART3
#define TF_min_UART_IRQHandler USART3_IRQHandler
#elif (TF_min_UART_PORT_SELECT == 4)
#include "BSP/MCU/UART/usart4.h"
#define TF_min_UART_PORT USART4
#define TF_min_UART_IRQHandler USART4_IRQHandler
#else
#error "Please define TF_min_UART_PORT!!!"
#endif

void TF_min_Init(void);

#endif /*_TF_MIN_H_*/
