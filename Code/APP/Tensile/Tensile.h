#ifndef __Tensile_H_
#define __Tensile_H_

#include "BSP\SYSTEM\My_Flag.h"

enum Tensile_state{
    Running,
    Preparing,
    Stop
};

enum Tensile_Mode{
    CVelocity,                  //���ٶ�ģʽ
    CStrength                   //������ģʽ
};

/* ����ʵ�����Ϣ */
typedef struct
{
    float velocity;             //����λ��(us/s)
    float strength;             //������ʩ�ӵ�����(N)
    
    float target_velocity;
    float target_strength;
    
    float offset_velocity;
    float offset_strength;

    enum Tensile_state state;   //��������״̬
    enum Tensile_Mode mode;     //�������з�ʽ
}sTensile_Typedef;

extern sTensile_Typedef Tensile;     //С����Ϣ

/**********************************************
* ����ʵ���������ʼ��
**********************************************/
void Tensile_Init(void);

/**********************************************
* ����ʵ�������������
**********************************************/
void Tensile_Param_Update(float velocity, float strength);

/**********************************************
* ����ʵ�������������У׼
**********************************************/
void Tensile_Calibrate(void);

#endif /* __Tensile_H_ */
