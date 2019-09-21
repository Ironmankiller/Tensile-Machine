//-----------------------------------------------------------------------------
//  Created on	: 2017-8-9
//      Author	: ZB
//		version	: V1.0
//		brief	: Pid Forward Fuzzy Control
//-----------------------------------------------------------------------------
#include "Algorithm.h"
#include "forward.h"
#include "APP\Math\My_Math.h"
#include "APP\Control\param.h"
#include "includes.h"
#include <stdint.h>
#include "BSP\Time\Time.h"
#include "pid.h"
#include "BSP\Motor_Drive\Moto_Drive.h"
#include "BSP\Motor_Drive\Wind_Moto.h"
#include "APP\IMU\ahrs.h"
#include "BSP\MCU\UART\usart3.h"
#include "APP\Car\Car.h"
#include "APP\ANO_DT\ANO_DT.h"
#include "APP\Math\My_Math.h"
#include "APP\Control\param.h"
#include "BSP\MPU6050\MPU6050.h"
#include "BSP\Motor_Drive\Steer_Moto.h"
#include "BSP\Mecanum\Mecanum.h"

void pid_setup_mecanum_speed()
{

}
void pid_setup_mecanum_position()
{

}

void pid_ctr_mecanum_speed(int Encode_A,int Encode_B,int Encode_C,int Encode_D)
{


}
void pid_ctr_mecanum_position(int Position_A,int Position_B,int Position_C,int Position_D)
{

}
void pid_setup_speed(void)
{

}

void pid_ctr_speed(void)
{

}

void pid_setup_angle(float target)
{
	
}

void pid_ctr_angle(void)
{

}


/*--------------------------------------------------------
                       Y_PID_Angle
   --------------------------------------------------------*/
void pid_setup_angle_y(float Ytarget)
{

}

void pid_ctr_angle_y(void)
{

}

/*--------------------------------------------------------
                       X_PID_Angle
   --------------------------------------------------------*/
void pid_setup_angle_x(float Xtarget)
{

}

void pid_ctr_angle_x(void)
{

}

/*--------------------------------------------------------
                         Y_PID
   --------------------------------------------------------*/
void pid_setup_y(float Ytarget)
{

}

void pid_ctr_y(void)
{

}

/*Fuzzy PID*/
void fuzzy_ctr_y(void)
{

}


/*--------------------------------------------------------
                          X_PID
   --------------------------------------------------------*/
void pid_setup_x(float Xtarget)
{

}



void pid_ctr_x(void)
{


}
/*Fuzzy PID*/
void fuzzy_ctr_x(void)
{

}


/*--------------------------------------------------------
                       Y_PID_Speed
   --------------------------------------------------------*/
void pid_setup_speed_y(float Ytarget)
{

}

void pid_ctr_speed_y(void)
{

}

/*--------------------------------------------------------
                         X_PID_Speed
   --------------------------------------------------------*/
void pid_setup_speed_x(float Xtarget)
{

}

void pid_ctr_speed_x(void)
{

}



/*--------------------------------------------------------
   Y_Forward
   --------------------------------------------------------*/
/*��ʼ��Yֱ��ǰ������*/
void forward_setup_y(float Ytarget)
{

}

//Yֱ��ǰ������
void forward_ctr_y(void)
{


}


/*--------------------------------------------------------
   X_Forward
   --------------------------------------------------------*/
/*��ʼ��Xֱ��ǰ������*/
void forward_setup_x(float Xtarget)
{

}

//Xֱ��ǰ������
void forward_ctr_x(void)
{

}
/******************* (C) COPYRIGHT 2017 ZB ***********END OF FILE***********/
