#include "ADS1255.h"
#include "Printf_Uart.h"
#include "APP\Math\My_Math.h"

void ADS1255_GPIO_Init(void)//��ʼ��
{
  	GPIO_InitTypeDef GPIO_InitDataBus;
    RCC_AHB1PeriphClockCmd(ADS1255_SCLK_GPIO_CLK | ADS1255_DIN_GPIO_CLK | ADS1255_DOUT_GPIO_CLK | ADS1255_DRDY_GPIO_CLK | ADS1255_CS_GPIO_CLK, ENABLE);

	//ADS1255 DOUT		     DRDY    INIT
  	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_IN;//����
  	GPIO_InitDataBus.GPIO_Speed = GPIO_Speed_50MHz; 

    GPIO_InitDataBus.GPIO_Pin = ADS1255_DOUT_GPIO_PIN;
  	GPIO_Init(ADS1255_DOUT_GPIO_PORT, &GPIO_InitDataBus);
 	GPIO_InitDataBus.GPIO_Pin = ADS1255_DRDY_GPIO_PIN ;
    GPIO_Init(ADS1255_DRDY_GPIO_PORT, &GPIO_InitDataBus);
	
	//ADS1255   SCLK          DIN          CS      INIT       
	GPIO_InitDataBus.GPIO_Mode = GPIO_Mode_OUT;//�������
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
		delay_us(1);	 
		ADS1255_Write_SCLK_L;
		delay_us(1);
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
		delay_us(1);
		ADS1255_Write_SCLK_L;
		date= date | ADS1255_Read_DOUT;
		delay_us(1);
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
	delay_ms(2);
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
  delay_us(200);
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
    
    ADS1255_GPIO_Init();               //��ʼ��ADS1255GPIO
                                                    
	ADS1255_Write_CS_H;
	ADS1255_Write_SCLK_L;
	delay_ms(1);
	ADS1255_Write_CS_L;	
	delay_ms(1);												
													
	ADS1255_write_reg(0x00,ADS1255_reg_Init[0]);//״̬�Ĵ�����ʼ��
	delay_us(1);
	
	ADS1255_write_reg(0x01,ADS1255_reg_Init[1]);//ģ���·ѡ������ʼ��
	delay_us(1);
	
	ADS1255_write_reg(0x02,ADS1255_reg_Init[2]);//AD���ƼĴ�����ʼ��
	delay_us(1);
	
	ADS1255_write_reg(0x03,ADS1255_reg_Init[3]);//�����ٶȼĴ�����ʼ��	
	delay_us(1);
	
	ADS1255_write_reg(0x04,ADS1255_reg_Init[4]);//I/O���ƼĴ�����ʼ��
	delay_us(1);
	
  if(ADS1255_reg_Init[1] != ADS1255_read_reg(0x01))  ReturnData = 1;

  if(ADS1255_reg_Init[2] != ADS1255_read_reg(0x02))  ReturnData = 1;
	delay_us(1);
	
  if(ADS1255_reg_Init[3] != ADS1255_read_reg(0x03))  ReturnData = 1;
	delay_us(1);
	
  if(ADS1255_reg_Init[4] != ADS1255_read_reg(0x04))  ReturnData = 1;
	delay_us(1);
	
	while(ADS1255_Read_DRDY);	
	ADS1255_SELFCAL();	//������������У׼
    delay_us(5);
	ADS1255_SYNC();     //ADת��ͬ��
	delay_ms(20);
	ADS1255_WAKEUP();   //�˳�����ģʽ
	delay_us(5);	
	
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



/****************************************************
���ܣ����ε�ͨ���ɼ����ݲ������ݷ��͵���λ��,AINPΪ������ͨ����AINN�ǵ�����ͨ��������0-7
****************************************************/
double ReadASingleData(u8 AINP,u8 AINN)
{
	double ReadVoltage[9];
	u32 Data;
	u16 i;
	
	ADS1255_write_reg(0x01,(AINP<<4) | AINN );//ͨ��ѡ��������ΪA0Ϊ�������P,A1Ϊ�������N 
	ADS1255_write_reg(0x03,0x23);//�����ٶ�2.5SPS
	ADS1255_SELFCAL();	//������������У׼
	delay_us(5);
	ADS1255_SYNC();     //ADת��ͬ��
	delay_ms(20);
	ADS1255_WAKEUP();   //�˳�����ģʽ
	delay_us(5);	
	
	for(i=0;i<9;i++) //�ɼ�9������
	{
		ADS1255_RDATA();             //����:��������������
		delay_us(20);         //������ʱ50��ADS1256��ʱ������
		Data = ADS1255_Read_a_Data();//��ȡAD�����Ķ�����ֵ
		ReadVoltage[i] = ADS1255_DataFormatting( Data , 2.5 , 1);//�ο���ѹ2.5V,��������1�� 
        //u1_printf("%f\r\n",ReadVoltage);
		//DataUart(ReadVoltage);	     //�ѵ�ѹֵ���͵���λ��
	}
    DBubble_Sort(ReadVoltage, 9);
    return ReadVoltage[4];

}




