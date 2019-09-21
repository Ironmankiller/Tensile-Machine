#include "ESCON.h"

/**********************************************
* 电机初始化
**********************************************/
void ESCON_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_AHB1PeriphClockCmd(ESCON_CS_GPIO_CLK | ESCON_DIR_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    //使能引脚初始化
	GPIO_InitStructure.GPIO_Pin = ESCON_CS_GPIO_PIN;
	GPIO_Init(ESCON_CS_GPIO_PORT, &GPIO_InitStructure);
    //方向控制引脚初始化
    GPIO_InitStructure.GPIO_Pin = ESCON_DIR_GPIO_PIN;
	GPIO_Init(ESCON_DIR_GPIO_PORT, &GPIO_InitStructure);

    /* PWM初始化 */
    ESCON_TIM_CLK_INIT(ESCON_TIM_CLK, ENABLE);   //电机时钟
    RCC_AHB1PeriphClockCmd(ESCON_TIM_GPIO_CLK , ENABLE); 
	
    GPIO_PinAFConfig(ESCON_TIM_GPIO_PORT, ESCON_TIM_GPIO_PINSOURCE, ESCON_TIM_AF); //复用为定时器8

    GPIO_InitStructure.GPIO_Pin = ESCON_TIM_GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //开漏复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
    GPIO_Init(ESCON_TIM_GPIO_PORT, &GPIO_InitStructure);              //初始化PC7

    //初始化TIM8
    TIM_TimeBaseStructure.TIM_Period = 8400-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = 0; //设置用来作为TIMx时钟频率除数的预分频值 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(ESCON_TIM, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //初始化TIM3 Channel2 PWM模式	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高

    ESCON_TIM_OCInit(ESCON_TIM, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 OC1
    ESCON_TIM_OCPreloadConfig(ESCON_TIM, TIM_OCPreload_Enable);  //使能TIM1在CCR1上的预装载寄存器
    
    //TIM_CtrlPWMOutputs(ESCON_TIM,ENABLE); 
    TIM_Cmd(ESCON_TIM, ENABLE);  //使能TIM1

    //使能电机驱动
    ESCON_EN(1);
}

/**********************************************
* 电机使能控制
**********************************************/
void ESCON_EN(unsigned char en){
    if(en)
    {
        ESCON_ENABLE;
    }
    else
    {
        ESCON_DISABLE;
    }
}

/**********************************************
* 设置PWM
**********************************************/
void ESCON_PWM_Set(int32_t pwm){
    //pwm限幅
    if(pwm > 7560)  pwm = 7560;
    if(pwm < -7560)  pwm = -7560;
    if(pwm < 840 && pwm > 0) pwm = 840;
    if(pwm > -840 && pwm < 0) pwm = -840;
    //确定方向并赋值
    if(pwm > 0){
        ESCON_POS;
        ESCON_PWM = pwm;
    } else{
        ESCON_NEG;
        ESCON_PWM = -pwm;
    }
}
