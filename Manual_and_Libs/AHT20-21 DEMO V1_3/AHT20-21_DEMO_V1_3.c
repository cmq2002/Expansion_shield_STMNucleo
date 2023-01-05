/*******************************************/
/*@��Ȩ���У����ݰ��ɵ������޹�˾          */
/*@���ߣ���ʪ�ȴ�������ҵ��                */
/*@�汾��V1.2                              */
/*******************************************/
#include "stm32f10x.h" 
#include "AHT20-21_DEMO_V1_3.h" 




void Delay_N10us(uint32_t t)//��ʱ����
{
  uint32_t k;

   while(t--)
  {
    for (k = 0; k < 2; k++);//110
  }
}

void SensorDelay_us(uint32_t t)//��ʱ����
{
		
	for(t = t-2; t>0; t--)
	{
		Delay_N10us(1);
	}
}

void Delay_4us(void)		//��ʱ����
{	
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
}
void Delay_5us(void)		//��ʱ����
{	
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);

}

void Delay_1ms(uint32_t t)		//��ʱ����
{
   while(t--)
  {
    SensorDelay_us(1000);//////��ʱ1ms
  }
}


void AHT20_Clock_Init(void)		//��ʱ����
{
	RCC_APB2PeriphClockCmd(CC_APB2Periph_GPIOB,ENABLE);
}

void SDA_Pin_Output_High(void)   //��PB15����Ϊ��� �� ������Ϊ�ߵ�ƽ�� PB15��ΪI2C��SDA
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,& GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

void SDA_Pin_Output_Low(void)  //��P15����Ϊ���  ������Ϊ�͵�ƽ
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,& GPIO_InitStruct);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void SDA_Pin_IN_FLOATING(void)  //SDA����Ϊ��������
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOB,&GPIO_InitStruct);
}

void SCL_Pin_Output_High(void) //SCL����ߵ�ƽ��P14��ΪI2C��SCL
{
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
}

void SCL_Pin_Output_Low(void) //SCL����͵�ƽ
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

void Init_I2C_Sensor_Port(void) //��ʼ��I2C�ӿ�,���Ϊ�ߵ�ƽ
{	
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,& GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);//����ߵ�ƽ
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,& GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);//����ߵ�ƽ
	
}
void I2C_Start(void)		 //I2C��������START�ź�
{
	SDA_Pin_Output_High();
	SensorDelay_us(8);
	SCL_Pin_Output_High();
	SensorDelay_us(8);
	SDA_Pin_Output_Low();
	SensorDelay_us(8);
	SCL_Pin_Output_Low();
	SensorDelay_us(8);   
}


void AHT20_WR_Byte(uint8_t Byte) //��AHT20дһ���ֽ�
{
	uint8_t Data,N,i;	
	Data=Byte;
	i = 0x80;
	for(N=0;N<8;N++)
	{
		SCL_Pin_Output_Low(); 
		Delay_4us();	
		if(i&Data)
		{
			SDA_Pin_Output_High();
		}
		else
		{
			SDA_Pin_Output_Low();
		}	
			
    SCL_Pin_Output_High();
		Delay_4us();
		Data <<= 1;
		 
	}
	SCL_Pin_Output_Low();
	SensorDelay_us(8);   
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
}	


uint8_t AHT20_RD_Byte(void)//��AHT20��ȡһ���ֽ�
{
	uint8_t Byte,i,a;
	Byte = 0;
	SCL_Pin_Output_Low();
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
	for(i=0;i<8;i++)
	{
    SCL_Pin_Output_High();		
		Delay_5us();
		a=0;
		if(  (GPIOB,GPIO_Pin_15)) a=1;
		Byte = (Byte<<1)|a;
		SCL_Pin_Output_Low();
		Delay_5us();
	}
  SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
	return Byte;
}


uint8_t Receive_ACK(void)   //��AHT20�Ƿ��лظ�ACK
{
	uint16_t CNT;
	CNT = 0;
	SCL_Pin_Output_Low();	
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
	SCL_Pin_Output_High();	
	SensorDelay_us(8);	
	while((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15))  && CNT < 100) 
	CNT++;
	if(CNT == 100)
	{
		return 0;
	}
 	SCL_Pin_Output_Low();	
	SensorDelay_us(8);	
	return 1;
}

void Send_ACK(void)		  //�����ظ�ACK�ź�
{
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);	
	SDA_Pin_Output_Low();
	SensorDelay_us(8);	
	SCL_Pin_Output_High();	
	SensorDelay_us(8);
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);
}

void Send_NOT_ACK(void)	//�������ظ�ACK
{
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);
	SDA_Pin_Output_High();
	SensorDelay_us(8);
	SCL_Pin_Output_High();	
	SensorDelay_us(8);		
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);
    SDA_Pin_Output_Low();
	SensorDelay_us(8);
}

void Stop_I2C(void)	  //һ��Э�����
{
	SDA_Pin_Output_Low();
	SensorDelay_us(8);
	SCL_Pin_Output_High();	
	SensorDelay_us(8);
	SDA_Pin_Output_High();
	SensorDelay_us(8);
}

uint8_t AHT20_Read_Status(void)//��ȡAHT20��״̬�Ĵ���
{

	uint8_t Byte_first;	
	I2C_Start();
	AHT20_WR_Byte(0x71);
	Receive_ACK();
	Byte_first = AHT20_RD_Byte();
	Send_NOT_ACK();
	Stop_I2C();
	return Byte_first;
}

uint8_t AHT20_Read_Cal_Enable(void)  //��ѯcal enableλ��û��ʹ��
{
	uint8_t val = 0;//ret = 0,
  val = AHT20_Read_Status();
	 if((val & 0x68)==0x08)
		 return 1;
   else  return 0;
 }

void AHT20_SendAC(void) //��AHT20����AC����
{

	I2C_Start();
	AHT20_WR_Byte(0x70);
	Receive_ACK();
	AHT20_WR_Byte(0xac);//0xAC�ɼ�����
	Receive_ACK();
	AHT20_WR_Byte(0x33);
	Receive_ACK();
	AHT20_WR_Byte(0x00);
	Receive_ACK();
	Stop_I2C();

}

//CRCУ�����ͣ�CRC8/MAXIM
//����ʽ��X8+X5+X4+1
//Poly��0011 0001  0x31
//��λ�ŵ�����ͱ�� 1000 1100 0x8c
//C��ʵ���룺
uint8_t Calc_CRC8(uint8_t *message,uint8_t Num)
{
        uint8_t i;
        uint8_t byte;
        uint8_t crc=0xFF;
  for(byte=0; byte<Num; byte++)
  {
    crc^=(message[byte]);
    for(i=8;i>0;--i)
    {
      if(crc&0x80) crc=(crc<<1)^0x31;
      else crc=(crc<<1);
    }
  }
        return crc;
}

void AHT20_Read_CTdata(uint32_t *ct) //û��CRCУ�飬ֱ�Ӷ�ȡAHT20���¶Ⱥ�ʪ������
{
	volatile uint8_t  Byte_1th=0;
	volatile uint8_t  Byte_2th=0;
	volatile uint8_t  Byte_3th=0;
	volatile uint8_t  Byte_4th=0;
	volatile uint8_t  Byte_5th=0;
	volatile uint8_t  Byte_6th=0;
	 uint32_t RetuData = 0;
	uint16_t cnt = 0;
	AHT20_SendAC();//��AHT10����AC����
	Delay_1ms(80);//��ʱ80ms����	
    cnt = 0;
	while(((AHT20_Read_Status()&0x80)==0x80))//ֱ��״̬bit[7]Ϊ0����ʾΪ����״̬����Ϊ1����ʾæ״̬
	{
		SensorDelay_us(1508);
		if(cnt++>=100)
		{
		 break;
		 }
	}
	I2C_Start();
	AHT20_WR_Byte(0x71);
	Receive_ACK();
	Byte_1th = AHT20_RD_Byte();//״̬�֣���ѯ��״̬Ϊ0x98,��ʾΪæ״̬��bit[7]Ϊ1��״̬Ϊ0x1C������0x0C������0x08��ʾΪ����״̬��bit[7]Ϊ0
	Send_ACK();
	Byte_2th = AHT20_RD_Byte();//ʪ��
	Send_ACK();
	Byte_3th = AHT20_RD_Byte();//ʪ��
	Send_ACK();
	Byte_4th = AHT20_RD_Byte();//ʪ��/�¶�
	Send_ACK();
	Byte_5th = AHT20_RD_Byte();//�¶�
	Send_ACK();
	Byte_6th = AHT20_RD_Byte();//�¶�
	Send_NOT_ACK();
	Stop_I2C();

	RetuData = (RetuData|Byte_2th)<<8;
	RetuData = (RetuData|Byte_3th)<<8;
	RetuData = (RetuData|Byte_4th);
	RetuData =RetuData >>4;
	ct[0] = RetuData;//ʪ��
	RetuData = 0;
	RetuData = (RetuData|Byte_4th)<<8;
	RetuData = (RetuData|Byte_5th)<<8;
	RetuData = (RetuData|Byte_6th);
	RetuData = RetuData&0xfffff;
	ct[1] =RetuData; //�¶�

}


void AHT20_Read_CTdata_crc(uint32_t *ct) //CRCУ��󣬶�ȡAHT20���¶Ⱥ�ʪ������
{
	volatile uint8_t  Byte_1th=0;
	volatile uint8_t  Byte_2th=0;
	volatile uint8_t  Byte_3th=0;
	volatile uint8_t  Byte_4th=0;
	volatile uint8_t  Byte_5th=0;
	volatile uint8_t  Byte_6th=0;
	volatile uint8_t  Byte_7th=0;
	 uint32_t RetuData = 0;
	 uint16_t cnt = 0;
	// uint8_t  CRCDATA=0;
	 uint8_t  CTDATA[6]={0};//����CRC��������
	
	AHT20_SendAC();//��AHT10����AC����
	Delay_1ms(80);//��ʱ80ms����	
    cnt = 0;
	while(((AHT20_Read_Status()&0x80)==0x80))//ֱ��״̬bit[7]Ϊ0����ʾΪ����״̬����Ϊ1����ʾæ״̬
	{
		SensorDelay_us(1508);
		if(cnt++>=100)
		{
		 break;
		}
	}
	
	I2C_Start();

	AHT20_WR_Byte(0x71);
	Receive_ACK();
	CTDATA[0]=Byte_1th = AHT20_RD_Byte();//״̬�֣���ѯ��״̬Ϊ0x98,��ʾΪæ״̬��bit[7]Ϊ1��״̬Ϊ0x1C������0x0C������0x08��ʾΪ����״̬��bit[7]Ϊ0
	Send_ACK();
	CTDATA[1]=Byte_2th = AHT20_RD_Byte();//ʪ��
	Send_ACK();
	CTDATA[2]=Byte_3th = AHT20_RD_Byte();//ʪ��
	Send_ACK();
	CTDATA[3]=Byte_4th = AHT20_RD_Byte();//ʪ��/�¶�
	Send_ACK();
	CTDATA[4]=Byte_5th = AHT20_RD_Byte();//�¶�
	Send_ACK();
	CTDATA[5]=Byte_6th = AHT20_RD_Byte();//�¶�
	Send_ACK();
	Byte_7th = AHT20_RD_Byte();//CRC����
	Send_NOT_ACK();                           //ע��: ����Ƿ���NAK
	Stop_I2C();
	
	if(Calc_CRC8(CTDATA,6)==Byte_7th)
	{
	RetuData = (RetuData|Byte_2th)<<8;
	RetuData = (RetuData|Byte_3th)<<8;
	RetuData = (RetuData|Byte_4th);
	RetuData =RetuData >>4;
	ct[0] = RetuData;//ʪ��
	RetuData = 0;
	RetuData = (RetuData|Byte_4th)<<8;
	RetuData = (RetuData|Byte_5th)<<8;
	RetuData = (RetuData|Byte_6th);
	RetuData = RetuData&0xfffff;
	ct[1] =RetuData; //�¶�
		
	}
	else
	{
		ct[0]=0x00;
		ct[1]=0x00;//У����󷵻�ֵ���ͻ����Ը����Լ���Ҫ����
	}//CRC����
}


void AHT20_Init(void)   //��ʼ��AHT20
{	
	Init_I2C_Sensor_Port();
	I2C_Start();
	AHT20_WR_Byte(0x70);
	Receive_ACK();
	AHT20_WR_Byte(0xa8);//0xA8����NOR����ģʽ
	Receive_ACK();
	AHT20_WR_Byte(0x00);
	Receive_ACK();
	AHT20_WR_Byte(0x00);
	Receive_ACK();
	Stop_I2C();

	Delay_1ms(10);//��ʱ10ms����

	I2C_Start();
	AHT20_WR_Byte(0x70);
	Receive_ACK();
	AHT20_WR_Byte(0xbe);//0xBE��ʼ�����AHT20�ĳ�ʼ��������0xBE,   AHT10�ĳ�ʼ��������0xE1
	Receive_ACK();
	AHT20_WR_Byte(0x08);//��ؼĴ���bit[3]��1��ΪУ׼���
	Receive_ACK();
	AHT20_WR_Byte(0x00);
	Receive_ACK();
	Stop_I2C();
	Delay_1ms(10);//��ʱ10ms����
}
void JH_Reset_REG(uint8_t addr)
{
	
	uint8_t Byte_first,Byte_second,Byte_third,Byte_fourth;
	I2C_Start();
	AHT20_WR_Byte(0x70);//ԭ����0x70
	Receive_ACK();
	AHT20_WR_Byte(addr);
	Receive_ACK();
	AHT20_WR_Byte(0x00);
	Receive_ACK();
	AHT20_WR_Byte(0x00);
	Receive_ACK();
	Stop_I2C();

	Delay_1ms(5);//��ʱ5ms����
	I2C_Start();
	AHT20_WR_Byte(0x71);//
	Receive_ACK();
	Byte_first = AHT20_RD_Byte();
	Send_ACK();
	Byte_second = AHT20_RD_Byte();
	Send_ACK();
	Byte_third = AHT20_RD_Byte();
	Send_NOT_ACK();
	Stop_I2C();
	
    Delay_1ms(10);//��ʱ10ms����
	I2C_Start();
	AHT20_WR_Byte(0x70);///
	Receive_ACK();
	AHT20_WR_Byte(0xB0|addr);////�Ĵ�������
	Receive_ACK();
	AHT20_WR_Byte(Byte_second);
	Receive_ACK();
	AHT20_WR_Byte(Byte_third);
	Receive_ACK();
	Stop_I2C();
	
	Byte_second=0x00;
	Byte_third =0x00;
}

void AHT20_Start_Init(void)
{
	JH_Reset_REG(0x1b);
	JH_Reset_REG(0x1c);
	JH_Reset_REG(0x1e);
}

int32_t main(void)
{
    uint32_t CT_data[2];
	volatile int  c1,t1;
	/***********************************************************************************/
	/**///�ٸ��ϵ磬��ƷоƬ�ڲ�������Ҫʱ�䣬��ʱ100~500ms,����500ms
	/***********************************************************************************/
	Delay_1ms(500);
	/***********************************************************************************/
	/**///���ϵ��һ�η�0x71��ȡ״̬�֣��ж�״̬���Ƿ�Ϊ0x18,�������0x18,���мĴ�����ʼ��
	/***********************************************************************************/
	if((AHT20_Read_Status()&0x18)!=0x18)
	{
	AHT20_Start_Init(); //���³�ʼ���Ĵ���
	Delay_1ms(10);
	}
	
	/***********************************************************************************/
	/**///�۸��ݿͻ��Լ����󷢲��������ȡ��ʪ�����ݣ���ǰwhile��1��ѭ�������������ȡ��ʪ�����ݣ������ο�
	/***********************************************************************************/
	while(1)
	{
	 AHT20_Read_CTdata(CT_data);       //������CRCУ�飬ֱ�Ӷ�ȡAHT20���¶Ⱥ�ʪ������    �Ƽ�ÿ������1S��һ��
    //AHT20_Read_CTdata_crc(CT_data);  //crcУ��󣬶�ȡAHT20���¶Ⱥ�ʪ������ 
	

	 c1 = CT_data[0]*100*10/1024/1024;  //����õ�ʪ��ֵc1���Ŵ���10����
	 t1 = CT_data[1]*200*10/1024/1024-500;//����õ��¶�ֵt1���Ŵ���10����
	////��һ���ͻ�������ʾ���ݣ�
	 }

 }	
