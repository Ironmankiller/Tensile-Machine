#include <stdint.h>
#include <stdio.h>
#include "BSP\My_BSP.h"
#include "APP\Task_Loop\Task_Loop.h"
#include "APP\ANO_DT\ANO_DT.h"
#include "BSP\Time\Time.h"
#include "APP\Tensile\Tensile.h"

static void System_Init(void);       // 系统初始化
/**********************************************
* 主函数 
**********************************************/
int main(void)
 {
    System_Init();	    // 系统初始化
    while (1)
    {
        Task_Loop();    // 任务循环
    }
}
 
/********************************************
* 系统初始化
* 包括硬件驱动层的初始化和软件层的初始化
*********************************************/
static void System_Init(void)
{
    /* 硬件驱动层初始化 */
    BSP_Init(115200, 168);
    /* 软件层初始化 */
    Tensile_Init();
    Loop_Time_Clear();
    Cycle_Time_Init();
}



//#include "stm32f10x.h"
//#include "usart1.h"
//#include "GPIO_Init.h"
//#include "ADS1255.h"

//void DataUart(double ReadVoltage);//函数声明
//void ReadASingleData(u8 AINP,u8 AINN);
//void ReadManyData(void);

//int main(void)
//{
//	GPIO_DataBus_Init();	
//	USART1_Config();
//	NVIC_Configuration();
//	printf("ADS1256准备初始化......");
//	
//	if(ADS1255_Init())     //初始化ADS1256的寄存器
//		printf("ADS1256初始化失败......");
//	else
//		printf("ADS1256初始化成功......");	
//	
//	printf("......1通道组测试......");	
//	ReadASingleData(0x00,0x01);     //连续采集8个数据并发送到上位机,A1为Vp,A0为Vn
//	ReadASingleData(0x01,0x00);     //连续采集8个数据并发送到上位机,A1为Vp,A0为Vn
//	printf("......2通道组测试......");	
//	ReadASingleData(0x02,0x03);     //连续采集8个数据并发送到上位机,A1为Vp,A0为Vn
//	ReadASingleData(0x03,0x02);     //连续采集8个数据并发送到上位机,A1为Vp,A0为Vn
//	printf("......3通道组测试......");	
//	ReadASingleData(0x04,0x05);     //连续采集8个数据并发送到上位机,A1为Vp,A0为Vn
//	ReadASingleData(0x05,0x04);     //连续采集8个数据并发送到上位机,A1为Vp,A0为Vn
//	printf("......4通道组测试......");	
//	ReadASingleData(0x06,0x07);     //连续采集8个数据并发送到上位机,A1为Vp,A0为Vn
//  ReadASingleData(0x07,0x06);     //连续采集8个数据并发送到上位机,A1为Vp,A0为Vn
//	while(1);	
//}


///****************************************************
//功能：单次单通道采集数据并把数据发送到上位机,AINP为高输入通道，AINN是低输入通道，输入0-7
//****************************************************/
//void ReadASingleData(u8 AINP,u8 AINN)
//{
//	double ReadVoltage;
//	u32 Data;
//	u16 i;
//	
//	ADS1255_write_reg(0x01,(AINP<<4) | AINN );//通道选择器配置为A0为差分输入P,A1为差分输入N 
//	ADS1255_write_reg(0x03,0x00);//数据速度2.5SPS
//	ADS1255_SELFCAL();	//补偿和增益自校准
//	ads1255_delayus(5);
//	ADS1255_SYNC();     //AD转换同步
//	ads1255_delayms(20);
//	ADS1255_WAKEUP();   //退出待机模式
//	ads1255_delayus(5);	
//	
//	for(i=0;i<8;i++) //采集8次数据
//	{
//		ADS1255_RDATA();             //功能:读单次数据命令
//		ads1255_delayus(20);         //至少延时50个ADS1256的时钟周期
//		Data = ADS1255_Read_a_Data();//读取AD采样的二进制值
//		ReadVoltage = ADS1255_DataFormatting( Data , 2.5 , 1);//参考电压2.5V,内置增益1倍 
//		DataUart(ReadVoltage);	     //把电压值发送到上位机
//	}

//}


///****************************************************
//功能：连续多通道循环采集数据并把数据发送到上位机
//****************************************************/
//void ReadManyData(void)
//{
//	double ReadVoltage;
//	u32 Data;
//	u16 i;
//	
//	ADS1255_write_reg(0x01,0x10);//通道选择器配置为A0为差分输入P,A1为差分输入N 
//		ADS1255_write_reg(0x03,0x00);//数据速度2.5SPS
//	ADS1255_SELFCAL();	//补偿和增益自校准
//	ads1255_delayus(5);
//	ADS1255_SYNC();     //AD转换同步
//	ads1255_delayms(20);
//	ADS1255_WAKEUP();   //退出待机模式
//	ads1255_delayus(5);	
//	
//	ADS1255_RDATAC();            //功能:连续读数据命令
//	ads1255_delayus(20);         //至少延时50个ADS1256的时钟周期
//	Data = ADS1255_Read_a_Data();//读取AD采样的二进制值
//	ReadVoltage = ADS1255_DataFormatting( Data , 2.5 , 1);//参考电压2.5V,内置增益1倍
//	DataUart(ReadVoltage);
//	for(i=0;i<7;i++)//连续7次循环采集数据，算上上一次采集一共采集8次数据
//	{ 			
//		while( ADS1255_DRDY());       //功能：读DRDY引脚状态,当DRDY引脚被拉低的时候读数据
//		Data = ADS1255_Read_a_Data();//读取AD采样的二进制值
//		ReadVoltage = ADS1255_DataFormatting( Data , 2.5 , 1);//参考电压2.5V,内置增益1倍
//		DataUart(ReadVoltage);	     //把电压值发送到上位机
//	}
//	ADS1255_SDATAC();   //停止连续读数据	
//}




///****************************************************
//功能：把浮点型数据转化成ASC码发送到上位机
//****************************************************/
//void DataUart(double ReadVoltage)
//{
//	u32 DData[12];
//	u8  character[10] = {48,49,50,51,52,53,54,55,56,57};//分别对应0~9
//	DData[0] = (u32)ReadVoltage;										//把浮点型转化为整形便于输出
//	DData[1] = ((u32)(ReadVoltage*10))        % 10;	//把浮点型转化为整形便于输出
//	DData[2] = ((u32)(ReadVoltage*100))       % 10;	//把浮点型转化为整形便于输出
//	DData[3] = ((u32)(ReadVoltage*1000))      % 10;	//把浮点型转化为整形便于输出
//	DData[4] = ((u32)(ReadVoltage*10000))     % 10;	//把浮点型转化为整形便于输出
//	DData[5] = ((u32)(ReadVoltage*100000))    % 10;	//把浮点型转化为整形便于输出
//	DData[6] = ((u32)(ReadVoltage*1000000))   % 10;	//把浮点型转化为整形便于输出
//	DData[7] = ((u32)(ReadVoltage*10000000))  % 10;	//把浮点型转化为整形便于输出
//	DData[8] = ((u32)(ReadVoltage*100000000)) % 10;	//把浮点型转化为整形便于输出
//	DData[9] = ((u32)(ReadVoltage*1000000000))% 10;	//把浮点型转化为整形便于输出
//	
//	if(ReadVoltage < 0)
//		printf("-");//如果是负数则输出负号
//	USART_SendData(USART1, character[(u16)DData[0]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);
//	printf(".");//小数点
//	ads1255_delayms(10);	
//	USART_SendData(USART1, character[(u16)DData[1]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);
//	USART_SendData(USART1, character[(u16)DData[2]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);
//	USART_SendData(USART1, character[(u16)DData[3]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);
//	USART_SendData(USART1, character[(u16)DData[4]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);
//	USART_SendData(USART1, character[(u16)DData[5]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);
//	USART_SendData(USART1, character[(u16)DData[6]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);
//	USART_SendData(USART1, character[(u16)DData[7]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);
//	USART_SendData(USART1, character[(u16)DData[8]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);	
//	USART_SendData(USART1, character[(u16)DData[9]]);//该函数把数据通过串口发送到上位机
//	ads1255_delayms(10);
//	printf("V\n");//单位V
//	ads1255_delayms(10);
//}
