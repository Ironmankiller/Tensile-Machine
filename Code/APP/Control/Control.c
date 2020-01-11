#include "Control.h"
#include "sys.h"


Flag Init_flag = MY_TRUE;
/**********************************************
* 拉伸实验机恒速度运行
**********************************************/
void Control_Velocity(void){
    
    if(Init_flag == MY_TRUE) {
        Init_flag = MY_FALSE;
        pid_setup_velocity(Tensile.LVDT.target_velocity);
    }
    pid_ctr_velocity();
}

/**********************************************
* 拉伸实验机恒力运行
**********************************************/
void Control_Strength(void){

}

/**********************************************
* 拉伸实验机停止运行
**********************************************/
void Control_Stop(void){
    ESCON_PWM_Set(0);
}

/**********************************************
* 拉伸实验机快速卸力
**********************************************/
void Control_Preparing(void){
    ESCON_PWM_Set(-16800);
}
