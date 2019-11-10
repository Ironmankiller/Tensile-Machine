#ifndef __DAC8563_H_H
#define __DAC8563_H_H
/********************************************************************/
#include "stm32f4xx.h"
/*****************************************************************************
                        Function Declare                                  
*****************************************************************************/


void ads1255_delayus(u16 time);//功能:软件粗略延时1us
void ads1255_delayms(u16 time);//功能:软件粗略延时1ms

u8 ADS1255_Init(void);         //功能:寄存器设置初始化,如果初始化成功返回0，失败返回1
u32 ADS1255_Read_a_Data(void); //功能:读一次24位转化数据
u32 ADS1255_Read_a_Data(void); //功能:读一次转化完成的数据

double ADS1255_DataFormatting(u32 Data , double Vref ,u8 PGA); 
///功能:把读数转化成电压值,输入分别为 ： 读回的二进制值   参考电压   内置增益

u8 ADS1255_DRDY(void);         //功能：读DRDY引脚状态
void ADS1255_write_reg(u8 ADS1255_command,u8 ADS1255_data);//功能:向ADS1256中对应寄存器地址写一字节数据
u8 ADS1255_read_reg(u8 ADS1255_command);                   //功能:向ADS1256中对应寄存器读一字节数据

void ADS1255_write_bit(u8 temp);//功能:写一字节数据
u8 ADS1255_read_bit(void);      //功能:读一字节数据

//---------------命令函数-----------------------------//
void ADS1255_RDATA(void);    //功能:读单次数据命令
void ADS1255_RDATAC(void);   //功能:连续读数据命令
void ADS1255_SDATAC(void);   //功能:停止连续读数据命令
void ADS1255_SELFCAL(void);  //功能:补偿和增益自我校准命令
void ADS1255_SELFOCAL(void); //功能:补偿自我校准
void ADS1255_SELFGCAL(void); //功能:增益自我校准
void ADS1255_SYSOCAL(void);  //功能:系统补偿校准
void ADS1255_SYSGCAL(void);  //功能:系统增益校准
void ADS1255_SYNC(void);     //功能:AD转换同步
void ADS1255_ATANDBY(void);  //功能:启动待机模式
void ADS1255_RESET(void);    //功能:系统复位
void ADS1255_WAKEUP(void);   //功能:退出待机模式

//-------------------------------------------------------------------------------//
#endif
