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
void GPIO_DataBus_Init(void)//��ʼ��
{
  	GPIO_InitTypeDef GPIO_InitDataBus;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//ADS1255
  	GPIO_InitDataBus.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4 ;
	//                            DOUT		     DRDY
  	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_IN;//����
    
  	GPIO_InitDataBus.GPIO_Speed = GPIO_Speed_50MHz;   
  	GPIO_Init(GPIOF, &GPIO_InitDataBus); 	
	
	GPIO_InitDataBus.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6;
	//                            SCLK          DIN          CS           REST          SYNC             
	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_OUT;//�������
    GPIO_InitDataBus.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitDataBus.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitDataBus.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_Init(GPIOF, &GPIO_InitDataBus);  //��ʼ��B1
	
	GPIO_InitDataBus.GPIO_Pin = GPIO_Pin_4;   
	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_OUT;//�������
    GPIO_InitDataBus.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDataBus.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitDataBus.GPIO_Speed = GPIO_Speed_50MHz;   
  	GPIO_Init(GPIOA, &GPIO_InitDataBus);  //LED
	
}


/**********************************************************************/
/****************************************
��ʱuS  
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
���ܣ���ʱMs
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
���ܣ�дһ�ֽ�����
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
���ܣ���һ�ֽ�����
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
���ܣ���DRDY����״̬
*****************************************/
u8 ADS1255_DRDY(void)
{
	return ADS1255_Read_DRDY;
}

/****************************************
���ܣ���������������
*****************************************/
void ADS1255_RDATA(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0x01);
}


/****************************************
����:��������������
*****************************************/
void ADS1255_RDATAC(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0x03);
}


/****************************************
����:ֹͣ��������������
*****************************************/
void ADS1255_SDATAC(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0x0F);
}


/****************************************
����:��������������У׼����
*****************************************/
void ADS1255_SELFCAL(void)
{
  while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF0);
}


/****************************************
����:��������У׼
*****************************************/
void ADS1255_SELFOCAL(void)
{
  while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF1);
}


/****************************************
����:��������У׼
*****************************************/
void ADS1255_SELFGCAL(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF2);
}


/****************************************
����:ϵͳ����У׼
*****************************************/
void ADS1255_SYSOCAL(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF3);
}


/****************************************
����:ϵͳ����У׼
*****************************************/
void ADS1255_SYSGCAL(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xF4);
}


/****************************************
����:ADת��ͬ��
*****************************************/
void ADS1255_SYNC(void)
{
	while(ADS1255_Read_DRDY);
	ADS1255_write_bit(0xFC);
}


/****************************************
����:��������ģʽ
*****************************************/
void ADS1255_ATANDBY(void)
{
	 ADS1255_write_bit(0xFD);
}


/****************************************
����:ϵͳ��λ
*****************************************/
void ADS1255_RESET(void)
{
	 ADS1255_write_bit(0xFE);
}


/****************************************
����:�˳�����ģʽ
*****************************************/
void ADS1255_WAKEUP(void)
{
	 ADS1255_write_bit(0xFF);
}


/****************************************
���ܣ�ADS1255д�Ĵ���
˵��������Ҫ��д��Ĵ�����������
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
���ܣ�ADS1255���Ĵ���
˵��������Ҫ��д��Ĵ�����ַ
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
���ܣ��Ĵ������ó�ʼ��,�����ʼ���ɹ�����0��ʧ�ܷ���1
*****************************************/
u8 ADS1255_Init(void)
{
	u8 ReturnData = 0;
	u8 ADS1255_reg_Init[5]={													
		                       0x02,  //״̬�Ĵ�����ʼ��ֵ
				                   0x01,  //ģ���·ѡ������ʼ��ֵ
				                   0x00,  //AD���ƼĴ�����ʼ��ֵ
				                   0x03,  //�����ٶȼĴ�����ʼ��ֵ	
				                   0x00, //I/O���ƼĴ�����ʼ��ֵ
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
													
	ADS1255_write_reg(0x00,ADS1255_reg_Init[0]);//״̬�Ĵ�����ʼ��
	ads1255_delayus(1);
	
	ADS1255_write_reg(0x01,ADS1255_reg_Init[1]);//ģ���·ѡ������ʼ��
	ads1255_delayus(1);
	
	ADS1255_write_reg(0x02,ADS1255_reg_Init[2]);//AD���ƼĴ�����ʼ��
	ads1255_delayus(1);
	
	ADS1255_write_reg(0x03,ADS1255_reg_Init[3]);//�����ٶȼĴ�����ʼ��	
	ads1255_delayus(1);
	
	ADS1255_write_reg(0x04,ADS1255_reg_Init[4]);//I/O���ƼĴ�����ʼ��
	ads1255_delayus(1);
	
  if(ADS1255_reg_Init[1] != ADS1255_read_reg(0x01))  ReturnData = 1;

  if(ADS1255_reg_Init[2] != ADS1255_read_reg(0x02))  ReturnData = 1;
	ads1255_delayus(1);
	
  if(ADS1255_reg_Init[3] != ADS1255_read_reg(0x03))  ReturnData = 1;
	ads1255_delayus(1);
	
  if(ADS1255_reg_Init[4] != ADS1255_read_reg(0x04))  ReturnData = 1;
	ads1255_delayus(1);
	
	while(ADS1255_Read_DRDY);	
	ADS1255_SELFCAL();	//������������У׼
	ads1255_delayus(5);
	ADS1255_SYNC();     //ADת��ͬ��
	ads1255_delayms(20);
	ADS1255_WAKEUP();   //�˳�����ģʽ
	ads1255_delayus(5);	
	
	return(ReturnData);
}
/****************************************
//����:��һ��ת����ɵ�����
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
//����:�Ѷ���ת���ɵ�ѹֵ,����ֱ�Ϊ �� ���صĶ�����ֵ   �ο���ѹ   ��������
*****************************************/
double ADS1255_DataFormatting(u32 Data , double Vref ,u8 PGA)
{
	/*
	��ѹ���㹫ʽ��
			�裺AD�����ĵ�ѹΪVin ,AD����������ֵΪX���ο���ѹΪ Vr ,�ڲ������˷�����ΪG
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








