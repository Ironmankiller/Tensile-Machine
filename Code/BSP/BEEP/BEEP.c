#include "sys.h"
#include "BEEP.h"
/**********************************************
* ��ʼ��������
**********************************************/
void Beep_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    /* PWM��ʼ�� */
    BEEP_TIM_CLK_INIT(BEEP_TIM_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(BEEP_GPIO_CLK, ENABLE); 

    GPIO_PinAFConfig(BEEP_GPIO_PORT, BEEP_GPIO_PINSOURCE, BEEP_TIM_AF);

    GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
    GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);              //��ʼ��PE5

    //��ʼ��TIM9
    TIM_TimeBaseStructure.TIM_Period = 720-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 64; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(BEEP_TIM, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM9 Channel2 PWMģʽ	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�

    BEEP_TIM_OCInit(BEEP_TIM, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 OC4
    BEEP_TIM_OCPreloadConfig(BEEP_TIM, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR4�ϵ�Ԥװ�ؼĴ���
    
    TIM_CtrlPWMOutputs(BEEP_TIM,ENABLE); 
    TIM_Cmd(BEEP_TIM, ENABLE);  //ʹ��TIM1
}

/**********************************************
* ��������
**********************************************/
void Beep_On(void)
{
	//TIM_SetCompare4(TIM1, (TIM1->ARR)/2);
    BEEP = 500;
}

/**********************************************
* ��������
**********************************************/
void Beep_Off(void)
{
	BEEP = 0;
}

void Beep_Play(u16 t)
{
	BEEP = 500;
	delay_ms(t);
	BEEP = 0;
}

uint8_t beep_delay = 0;
void Beep_BB_Set(void)
{
    beep_delay = 3;
    Beep_On();
}

void Beep_BB(void)
{
    beep_delay--;
    if (!beep_delay)
    {
        Beep_Off();
    }
}




