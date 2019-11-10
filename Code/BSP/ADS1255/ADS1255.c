#include "ADS1255.h"

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

//---------------------------------------------------------------
void GPIO_DataBus_Init(void)//初始化
{
  	GPIO_InitTypeDef GPIO_InitDataBus;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//ADS1255
  	GPIO_InitDataBus.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4 ;
	//                            DOUT		     DRDY
  	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_IN;//输入
    
  	GPIO_InitDataBus.GPIO_Speed = GPIO_Speed_50MHz;   
  	GPIO_Init(GPIOF, &GPIO_InitDataBus); 	
	
	GPIO_InitDataBus.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6;
	//                            SCLK          DIN          CS           REST          SYNC             
	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_OUT;//推挽输出
    GPIO_InitDataBus.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitDataBus.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitDataBus.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_Init(GPIOF, &GPIO_InitDataBus);  //初始化B1
	
	GPIO_InitDataBus.GPIO_Pin = GPIO_Pin_4;   
	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_OUT;//推挽输出
    GPIO_InitDataBus.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDataBus.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitDataBus.GPIO_Speed = GPIO_Speed_50MHz;   
  	GPIO_Init(GPIOA, &GPIO_InitDataBus);  //LED
	
}


/**********************************************************************/
/****************************************
延时uS  
*****************************************/

void ads1255_delayus(u16 time)						  
{
	u16 i=0;
	while(time--)
	{
		i=3;
		while(i--);
  }
}

/****************************************
功能：延时Ms
*****************************************/
void ads1255_delayms(u16 time)
{
 u16 i;
 while(time--)
 {
	 i=4000;
	 while(i--);
 }  
}

/****************************************
功能：写一字节数据
*****************************************/

void ADS1255_write_bit(u8 temp)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		ADS1255_Write_SCLK_H; 
		if(temp&0x80) 
			ADS1255_Write_DIN_H;
		else
			ADS1255_Write_DIN_L;
		temp=temp<<1;
		ads1255_delayus(1);	 
		ADS1255_Write_SCLK_L;
		ads1255_delayus(1);
	}
}

/****************************************
功能：读一字节数据
*****************************************/

u8 ADS1255_read_bit(void)
{
 u8 i;
 u8 date;
	for(i=0;i<8;i++)
	{
		ADS1255_Write_SCLK_H;
		date=date<<1;
		ads1255_delayus(1);
		ADS1255_Write_SCLK_L;
		date= date | ADS1255_Read_DOUT;
		ads1255_delayus(1);
	}
  return date;
}

/****************************************
功能：读DRDY引脚状态
*****************************************/
u8 ADS1255_DRDY(void)
{
	return ADS1255_Read_DRDY;
}

/****************************************
功能：读单次数据命令
*****************************************/
void ADS1255_RDATA(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0x01);
}


/****************************************
功能:连续读数据命令
*****************************************/
void ADS1255_RDATAC(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0x03);
}


/****************************************
功能:停止连续读数据命令
*****************************************/
void ADS1255_SDATAC(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0x0F);
}


/****************************************
功能:补偿和增益自我校准命令
*****************************************/
void ADS1255_SELFCAL(void)
{
  while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF0);
}


/****************************************
功能:补偿自我校准
*****************************************/
void ADS1255_SELFOCAL(void)
{
  while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF1);
}


/****************************************
功能:增益自我校准
*****************************************/
void ADS1255_SELFGCAL(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF2);
}


/****************************************
功能:系统补偿校准
*****************************************/
void ADS1255_SYSOCAL(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF3);
}


/****************************************
功能:系统增益校准
*****************************************/
void ADS1255_SYSGCAL(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF4);
}


/****************************************
功能:AD转换同步
*****************************************/
void ADS1255_SYNC(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xFC);
}


/****************************************
功能:启动待机模式
*****************************************/
void ADS1255_ATANDBY(void)
{
	 ADS1255_write_bit(0xFD);
}


/****************************************
功能:系统复位
*****************************************/
void ADS1255_RESET(void)
{
	 ADS1255_write_bit(0xFE);
}


/****************************************
功能:退出待机模式
*****************************************/
void ADS1255_WAKEUP(void)
{
	 ADS1255_write_bit(0xFF);
}


/****************************************
功能：ADS1255写寄存器
说明：根据要求写入寄存器和命令字
*****************************************/

void ADS1255_write_reg(u8 ADS1255_command,u8 ADS1255_data)
{
	while(ADS1255_Read_DRDY); 
	ADS1255_write_bit(ADS1255_command | 0x50);
	ADS1255_write_bit(0x00);
	ADS1255_write_bit(ADS1255_data);
	ads1255_delayms(2);
}


/****************************************
功能：ADS1255读寄存器
说明：根据要求写入寄存器地址
*****************************************/

u8 ADS1255_read_reg(u8 ADS1255_command)
{
  u8 reg_date;
	while(ADS1255_Read_DRDY);
  ADS1255_write_bit(ADS1255_command | 0x10);
  ADS1255_write_bit(0x00);
  ads1255_delayus(50);
  reg_date=ADS1255_read_bit();
  return reg_date;
}


/****************************************
功能：寄存器设置初始化,如果初始化成功返回0，失败返回1
*****************************************/
u8 ADS1255_Init(void)
{
	u8 ReturnData = 0;
	u8 ADS1255_reg_Init[5]={													
		                       0x02,  //状态寄存器初始化值
				                   0x01,  //模拟多路选择器初始化值
				                   0x00,  //AD控制寄存器初始化值
				                   0x03,  //数据速度寄存器初始化值	
				                   0x00, //I/O控制寄存器初始化值
													};
	ADS1255_Write_CS_H;
	ADS1255_Write_SYNC_H;
	ADS1255_Write_SCLK_L;
	ADS1255_Write_RST_L;
	ads1255_delayms(1);
	ADS1255_Write_RST_H;
	ads1255_delayms(1);
	ADS1255_Write_CS_L;	
	ads1255_delayms(1);												
													
	ADS1255_write_reg(0x00,ADS1255_reg_Init[0]);//状态寄存器初始化
	ads1255_delayus(1);
	
	ADS1255_write_reg(0x01,ADS1255_reg_Init[1]);//模拟多路选择器初始化
	ads1255_delayus(1);
	
	ADS1255_write_reg(0x02,ADS1255_reg_Init[2]);//AD控制寄存器初始化
	ads1255_delayus(1);
	
	ADS1255_write_reg(0x03,ADS1255_reg_Init[3]);//数据速度寄存器初始化	
	ads1255_delayus(1);
	
	ADS1255_write_reg(0x04,ADS1255_reg_Init[4]);//I/O控制寄存器初始化
	ads1255_delayus(1);
	
  if(ADS1255_reg_Init[1] != ADS1255_read_reg(0x01))  ReturnData = 1;

  if(ADS1255_reg_Init[2] != ADS1255_read_reg(0x02))  ReturnData = 1;
	ads1255_delayus(1);
	
  if(ADS1255_reg_Init[3] != ADS1255_read_reg(0x03))  ReturnData = 1;
	ads1255_delayus(1);
	
  if(ADS1255_reg_Init[4] != ADS1255_read_reg(0x04))  ReturnData = 1;
	ads1255_delayus(1);
	
	while(ADS1255_Read_DRDY);	
	ADS1255_SELFCAL();	//补偿和增益自校准
	ads1255_delayus(5);
	ADS1255_SYNC();     //AD转换同步
	ads1255_delayms(20);
	ADS1255_WAKEUP();   //退出待机模式
	ads1255_delayus(5);	
	
	return(ReturnData);
}
/****************************************
//功能:读一次转化完成的数据
*****************************************/
u32 ADS1255_Read_a_Data(void)
{
	u32 Data,Data1,Data2,Data3; 
	Data1 = ADS1255_read_bit();
	Data2 = ADS1255_read_bit();
	Data3 = ADS1255_read_bit();
	Data = (Data1<<16) | (Data2<<8) | Data3;
	return (Data);
}

/****************************************
//功能:把读数转化成电压值,输入分别为 ： 读回的二进制值   参考电压   内置增益
*****************************************/
double ADS1255_DataFormatting(u32 Data , double Vref ,u8 PGA)
{
	/*
	电压计算公式；
			设：AD采样的电压为Vin ,AD采样二进制值为X，参考电压为 Vr ,内部集成运放增益为G
			Vin = ( (2*Vr) / G ) * ( x / (2^23 -1))
	*/
	double ReadVoltage;
	if(Data & 0x00800000)
	{
		Data = (~Data) & 0x00FFFFFF;
		ReadVoltage = -(((double)Data) / 8388607) * ((2*Vref) / ((double)PGA));
	}
	else
		ReadVoltage =  (((double)Data) / 8388607) * ((2*Vref) / ((double)PGA));
	
	return(ReadVoltage);
}








