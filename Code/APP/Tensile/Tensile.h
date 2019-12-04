#ifndef __Tensile_H_
#define __Tensile_H_
#include "sys.h"
#include "BSP\SYSTEM\My_Flag.h"

/* λ�ƴ�������Ϣ */
typedef struct{
    
    double position;             //��ǰλ��(um)
    double target_postion;
    double offset_position;
    
    double velocity;             //�����ٶ�(um/s)
    double target_velocity;
    double offset_velocity;
    
    int32_t range;              //����(mm)
    int32_t output_max;         //������ֵ(V)
    int32_t output_min;         //�����Сֵ(V)

}sLVDT_Typedef;

/* ������������Ϣ */
typedef struct{
    
    double tension;             //��ǰ����(N)
    double target_tension;
    double offset_tension;
    
    int32_t range;              //����(N)
    int32_t output_max;         //������ֵ(V)
    int32_t output_min;         //�����Сֵ(V)

}sTensionSensor_Typedef;

enum Tensile_state{
    Running,
    Preparing,
    Stop
};

enum Tensile_Mode{
    CVelocity,                  //���ٶ�ģʽ
    CTension                   //������ģʽ
};

/* ����ʵ�����Ϣ */
typedef struct
{
    
    sLVDT_Typedef LVDT;         //λ�ƴ�����ʵ��
    
    sTensionSensor_Typedef TensionSensor;    //����������ʵ��

    enum Tensile_state state;   //��������״̬
    enum Tensile_Mode mode;     //�������з�ʽ
}sTensile_Typedef;

extern sTensile_Typedef Tensile;     //С����Ϣ

/**********************************************
* ����ʵ���������ʼ��
**********************************************/
void Tensile_Init(void);

/**********************************************
* ����ʵ�������������У׼
**********************************************/
void Tensile_Calibrate(void);

/**********************************************
* ������������
**********************************************/
void Tensile_Read_TensionSensor(void);

/**********************************************
* ��λ�ƴ�����
**********************************************/
void Tensile_Read_LVDT(void);


#endif /* __Tensile_H_ */
