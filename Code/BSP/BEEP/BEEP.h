#ifndef __BEEP_H
#define __BEEP_H

//������IO����
#define BEEP_GPIO_PORT              GPIOE
#define BEEP_GPIO_Pin               GPIO_Pin_5
#define BEEP_GPIO_PINSOURCE         GPIO_PinSource5
#define BEEP_GPIO_CLK               RCC_AHB1Periph_GPIOE

//������ʱ�ӳ�ʼ������
#define BEEP                            TIM9->CCR1  //PB15
#define BEEP_TIM                        TIM9
#define BEEP_TIM_CLK_INIT               RCC_APB2PeriphClockCmd
#define BEEP_TIM_CLK                    RCC_APB2Periph_TIM9
#define BEEP_TIM_AF                     GPIO_AF_TIM9
#define BEEP_TIM_OCInit                 TIM_OC1Init
#define BEEP_TIM_OCPreloadConfig        TIM_OC1PreloadConfig   
/**********************************************
* ��ʼ��������
**********************************************/
void Beep_Init(void);

/**********************************************
* ��������
**********************************************/
void Beep_On(void);

/**********************************************
* ��������
**********************************************/
void Beep_Off(void);

void Beep_Play(u16 t);

void Beep_BB_Set(void);
void Beep_BB(void);

#endif
