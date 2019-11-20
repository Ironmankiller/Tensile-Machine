#ifndef __DAC8563_H_H
#define __DAC8563_H_H
/********************************************************************/
#include "stm32f4xx.h"
/*****************************************************************************
                             Define                                  
*****************************************************************************/
//----------write------------------

#define ADS1255_Write_SCLK_H GPIO_SetBits(GPIOF, GPIO_Pin_0)
#define ADS1255_Write_SCLK_L GPIO_ResetBits(GPIOF,GPIO_Pin_0)	
	
#define ADS1255_Write_CS_H GPIO_SetBits(GPIOF, GPIO_Pin_3)
#define ADS1255_Write_CS_L GPIO_ResetBits(GPIOF,GPIO_Pin_3)	

#define ADS1255_Write_RST_H GPIO_SetBits(GPIOF, GPIO_Pin_5)
#define ADS1255_Write_RST_L GPIO_ResetBits(GPIOF,GPIO_Pin_5)		
	
#define ADS1255_Write_DIN_H GPIO_SetBits(GPIOF, GPIO_Pin_1)
#define ADS1255_Write_DIN_L GPIO_ResetBits(GPIOF,GPIO_Pin_1)	

#define ADS1255_Write_SYNC_H GPIO_SetBits(GPIOF, GPIO_Pin_6)
#define ADS1255_Write_SYNC_L GPIO_ResetBits(GPIOF,GPIO_Pin_6)	
//----------read------------------
#define ADS1255_Read_DOUT GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)
#define ADS1255_Read_DRDY GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)

/*****************************************************************************
                        Function Declare                                  
*****************************************************************************/
void ADS1255_GPIO_Init(void);

void ADS1255_delayus(u16 time);//����:���������ʱ1us
void ADS1255_delayms(u16 time);//����:���������ʱ1ms

u8 ADS1255_Init(void);         //����:�Ĵ������ó�ʼ��,�����ʼ���ɹ�����0��ʧ�ܷ���1
u32 ADS1255_Read_a_Data(void); //����:��һ��24λת������
u32 ADS1255_Read_a_Data(void); //����:��һ��ת����ɵ�����

double ADS1255_DataFormatting(u32 Data , double Vref ,u8 PGA); 
///����:�Ѷ���ת���ɵ�ѹֵ,����ֱ�Ϊ �� ���صĶ�����ֵ   �ο���ѹ   ��������

u8 ADS1255_DRDY(void);         //���ܣ���DRDY����״̬
void ADS1255_write_reg(u8 ADS1255_command,u8 ADS1255_data);//����:��ADS1255�ж�Ӧ�Ĵ�����ַдһ�ֽ�����
u8 ADS1255_read_reg(u8 ADS1255_command);                   //����:��ADS1255�ж�Ӧ�Ĵ�����һ�ֽ�����

void ADS1255_write_bit(u8 temp);//����:дһ�ֽ�����
u8 ADS1255_read_bit(void);      //����:��һ�ֽ�����

//---------------�����-----------------------------//
void ADS1255_RDATA(void);    //����:��������������
void ADS1255_RDATAC(void);   //����:��������������
void ADS1255_SDATAC(void);   //����:ֹͣ��������������
void ADS1255_SELFCAL(void);  //����:��������������У׼����
void ADS1255_SELFOCAL(void); //����:��������У׼
void ADS1255_SELFGCAL(void); //����:��������У׼
void ADS1255_SYSOCAL(void);  //����:ϵͳ����У׼
void ADS1255_SYSGCAL(void);  //����:ϵͳ����У׼
void ADS1255_SYNC(void);     //����:ADת��ͬ��
void ADS1255_ATANDBY(void);  //����:��������ģʽ
void ADS1255_RESET(void);    //����:ϵͳ��λ
void ADS1255_WAKEUP(void);   //����:�˳�����ģʽ

//-------------------------------------------------------------------------------//
#endif
