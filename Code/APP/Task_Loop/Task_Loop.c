#include "Task_Loop.h"
#include "sys.h"

/* 任务循环计时结构体 */
typedef struct {
    uint8_t check_flag;
    uint8_t err_flag;
    uint8_t cnt_1ms;
    uint8_t cnt_2ms;
    uint8_t cnt_5ms;
    uint8_t cnt_10ms;
    uint8_t cnt_20ms;
    uint8_t cnt_50ms;
}Loop_Time_TypeDef;

static Loop_Time_TypeDef Loop_Time;    //任务循环计时

__INLINE static void Task_1ms(void);
__INLINE static void Task_2ms(void);
__INLINE static void Task_5ms(void);
__INLINE static void Task_10ms(void);
__INLINE static void Task_20ms(void);
__INLINE static void Task_50ms(void);

/**********************************************
* 清空循环计数标志
**********************************************/
void Loop_Time_Clear(void)
{
    memset(&Loop_Time, 0, sizeof(Loop_Time_TypeDef));
}

/**********************************************
* 任务循环
* 由主函数初始化完成后调用
**********************************************/
void Task_Loop(void)
{
    if (Loop_Time.check_flag >= 1)
    {
        Task_1ms();                     //周期1ms的任务
        if (Loop_Time.cnt_2ms >= 2)
        {
            Loop_Time.cnt_2ms = 0;
            Task_2ms();	 			//周期2ms的任务
        }
        if (Loop_Time.cnt_5ms >= 5)//
        {
            Loop_Time.cnt_5ms = 0;
            Task_5ms();                 //周期5ms的任务
        }
        if (Loop_Time.cnt_10ms >= 10)
        {
            Loop_Time.cnt_10ms = 0;
            Task_10ms();                //周期10ms的任务
        }
        if (Loop_Time.cnt_20ms >= 20)
        {
            Loop_Time.cnt_20ms = 0;
            Task_20ms();                //周期20ms的任务
        }
        if (Loop_Time.cnt_50ms >= 50)
        {
            Loop_Time.cnt_50ms = 0;
            Task_50ms();                //周期50ms的任务
        }


        Loop_Time.check_flag = 0;       //循环运行完毕标志
    }
}

/**********************************************
* 1ms任务
**********************************************/
__INLINE static void Task_1ms(void)
{   
    /* 执行上位机指令 */
    ANO_DT_Do();
}

/**********************************************
* 2ms任务
**********************************************/
__INLINE static void Task_2ms(void)
{
    HMI_Data_Handle((uint8_t*)USART_RX_BUF);
}
/**********************************************
* 5ms任务
**********************************************/
__INLINE static void Task_5ms(void)
{

}

/**********************************************
* 10ms任务               
**********************************************/
__INLINE static void Task_10ms(void)
{   
    
    Tensile_Read_LVDT();
    
    switch(Tensile.state)
    {
        case Running:
            if(Tensile.mode == CVelocity){
                Control_Velocity();
            }
            else if(Tensile.mode == CTension){
                Control_Strength();
            }
            break;
        case Stop:
            Control_Stop();
            break;
        case Preparing:
            Control_Preparing();
            break;
        default:
            ESCON_EN(0);
            while(1){
                Beep_Play(300);
                LED_ALL_ON();
                delay_ms(300);
                LED_ALL_OFF();
            }
    }
}
/**********************************************
* 20ms任务
**********************************************/
__INLINE static void Task_20ms(void)
{
    /* 发送调试数据到上位机 */
//    ANO_DT_Send_Senser(
//    0, 0, 0,
//	0 ,0 , 0, 0,
//    0, 0, 0);
//    ANO_DT_Send_Status(EulerAngle.Roll, EulerAngle.Pitch, EulerAngle.Yaw, 0, 0, 1);

}

/**********************************************
* 50ms任务
**********************************************/
__INLINE static void Task_50ms(void)
{
    /* LED闪烁 */
    LED_Blink(LED_2);
    LED_Blink(LED_3);
    LED_Blink(LED_4);
    LED_Blink(LED_1);
    
    /* 显示 */
    u1_printf("%f\r\n",Tensile.LVDT.position * (Tensile.LVDT.output_max - Tensile.LVDT.output_min)/Tensile.LVDT.range);

    /* 独立按键（调试用 比赛时慎用） */
    switch (KEY_Scan())
    {
    case 2:
        LED_SWITCH(LED_1);
        Tensile.state = Running;
        break;
    case 3:
        LED_SWITCH(LED_2);
        Tensile.state = Stop;
        break;
    case 4:
        LED_SWITCH(LED_3);
        break;
    case 5:
		LED_SWITCH(LED_4);
        break;
      default:      break;
    }
}


/**********************************************
* 任务循环计时
* 由1ms定时中断调用
**********************************************/
void Loop_Time_Check(void)
{
    Loop_Time.cnt_2ms++;
    Loop_Time.cnt_5ms++;
    Loop_Time.cnt_10ms++;
    Loop_Time.cnt_20ms++;
    Loop_Time.cnt_50ms++;

    if (Loop_Time.check_flag >= 2)
    {
        Loop_Time.err_flag++;     //每累加一次，证明代码在预定周期2ms内没有跑完。
    }
    else
    {
        Loop_Time.check_flag += 1;	//该标志位在循环的最后被清零
    }
}
