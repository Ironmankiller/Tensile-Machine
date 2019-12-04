#include "ADS1255.h"
#include "Printf_Uart.h"
#include "APP\Math\My_Math.h"

void ADS1255_GPIO_Init(void)//初始化
{
  	GPIO_InitTypeDef GPIO_InitDataBus;
    RCC_AHB1PeriphClockCmd(ADS1255_SCLK_GPIO_CLK | ADS1255_DIN_GPIO_CLK | ADS1255_DOUT_GPIO_CLK | ADS1255_DRDY_GPIO_CLK | ADS1255_CS_GPIO_CLK, ENABLE);

	//ADS1255 DOUT		     DRDY    INIT
  	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_IN;//输入
  	GPIO_InitDataBus.GPIO_Speed = GPIO_Speed_50MHz; 

    GPIO_InitDataBus.GPIO_Pin = ADS1255_DOUT_GPIO_PIN;
  	GPIO_Init(ADS1255_DOUT_GPIO_PORT, &GPIO_InitDataBus);
 	GPIO_InitDataBus.GPIO_Pin = ADS1255_DRDY_GPIO_PIN ;
    GPIO_Init(ADS1255_DRDY_GPIO_PORT, &GPIO_InitDataBus);
	
	//ADS1255   SCLK          DIN          CS      INIT       
	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_OUT;//推挽输出
    GPIO_InitDataBus.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitDataBus.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitDataBus.GPIO_PuPd = GPIO_PuPd_DOWN;
    
    GPIO_InitDataBus.GPIO_Pin = ADS1255_SCLK_GPIO_PIN;
  	GPIO_Init(ADS1255_SCLK_GPIO_PORT, &GPIO_InitDataBus);
    GPIO_InitDataBus.GPIO_Pin = ADS1255_DIN_GPIO_PIN;
  	GPIO_Init(ADS1255_DIN_GPIO_PORT, &GPIO_InitDataBus);
    GPIO_InitDataBus.GPIO_Pin = ADS1255_CS_GPIO_PIN;
  	GPIO_Init(ADS1255_CS_GPIO_PORT, &GPIO_InitDataBus);
	
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
		delay_us(1);	 
		ADS1255_Write_SCLK_L;
		delay_us(1);
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
		delay_us(1);
		ADS1255_Write_SCLK_L;
		date= date | ADS1255_Read_DOUT;
		delay_us(1);
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
	delay_ms(2);
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
  delay_us(200);
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
    
    ADS1255_GPIO_Init();               //初始化ADS1255GPIO
                                                    
	ADS1255_Write_CS_H;
	ADS1255_Write_SCLK_L;
	delay_ms(1);
	ADS1255_Write_CS_L;	
	delay_ms(1);												
													
	ADS1255_write_reg(0x00,ADS1255_reg_Init[0]);//状态寄存器初始化
	delay_us(1);
	
	ADS1255_write_reg(0x01,ADS1255_reg_Init[1]);//模拟多路选择器初始化
	delay_us(1);
	
	ADS1255_write_reg(0x02,ADS1255_reg_Init[2]);//AD控制寄存器初始化
	delay_us(1);
	
	ADS1255_write_reg(0x03,ADS1255_reg_Init[3]);//数据速度寄存器初始化	
	delay_us(1);
	
	ADS1255_write_reg(0x04,ADS1255_reg_Init[4]);//I/O控制寄存器初始化
	delay_us(1);
	
  if(ADS1255_reg_Init[1] != ADS1255_read_reg(0x01))  ReturnData = 1;

  if(ADS1255_reg_Init[2] != ADS1255_read_reg(0x02))  ReturnData = 1;
	delay_us(1);
	
  if(ADS1255_reg_Init[3] != ADS1255_read_reg(0x03))  ReturnData = 1;
	delay_us(1);
	
  if(ADS1255_reg_Init[4] != ADS1255_read_reg(0x04))  ReturnData = 1;
	delay_us(1);
	
	while(ADS1255_Read_DRDY);	
	ADS1255_SELFCAL();	//补偿和增益自校准
    delay_us(5);
	ADS1255_SYNC();     //AD转换同步
	delay_ms(20);
	ADS1255_WAKEUP();   //退出待机模式
	delay_us(5);	
	
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



/****************************************************
功能：单次单通道采集数据并把数据发送到上位机,AINP为高输入通道，AINN是低输入通道，输入0-7
****************************************************/
double ReadASingleData(u8 AINP,u8 AINN)
{
	double ReadVoltage[9];
	u32 Data;
	u16 i;
	
	ADS1255_write_reg(0x01,(AINP<<4) | AINN );//通道选择器配置为A0为差分输入P,A1为差分输入N 
	ADS1255_write_reg(0x03,0x23);//数据速度2.5SPS
	ADS1255_SELFCAL();	//补偿和增益自校准
	delay_us(5);
	ADS1255_SYNC();     //AD转换同步
	delay_ms(20);
	ADS1255_WAKEUP();   //退出待机模式
	delay_us(5);	
	
	for(i=0;i<9;i++) //采集9次数据
	{
		ADS1255_RDATA();             //功能:读单次数据命令
		delay_us(20);         //至少延时50个ADS1256的时钟周期
		Data = ADS1255_Read_a_Data();//读取AD采样的二进制值
		ReadVoltage[i] = ADS1255_DataFormatting( Data , 2.5 , 1);//参考电压2.5V,内置增益1倍 
        //u1_printf("%f\r\n",ReadVoltage);
		//DataUart(ReadVoltage);	     //把电压值发送到上位机
	}
    DBubble_Sort(ReadVoltage, 9);
    return ReadVoltage[4];

}




