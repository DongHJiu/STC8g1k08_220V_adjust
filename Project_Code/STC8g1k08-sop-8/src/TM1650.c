#include"TM1650.h"

/*
	�� �� д �� �� �裺Start->Address->Data->Ack->Stop��
*/

/*
	��    �ܣ�TM1650��ʼ
*/
void TM1650_Start(void)			
{
	TM_SCL=1;//ʱ��
	TM_SDA=1;
	_nop_();
	_nop_();
	TM_SDA=0;
	_nop_();
	_nop_();
	TM_SCL=0;
}

/*
	��    �ܣ�TM1650����
*/
void TM1650_Stop(void)		
{
	TM_SCL=1;
	TM_SDA=0;
	_nop_();
	_nop_();
	TM_SDA=1;
	_nop_();
	_nop_();
}
/*
	��    �ܣ�TM1650д�ֽ�
*/
void TM1650_WriteByte(unsigned char date)	
{
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		if(date&0x80)
		{
		TM_SDA=1;	 
		}
		else
		{
		TM_SDA=0;
		}
		_nop_();
		_nop_();
		TM_SCL=1;
		date<<=1;
		_nop_();
		_nop_();
		TM_SCL=0;	 
	}
	TM_SDA=1;
	_nop_();
	_nop_();
	TM_SCL=1;
	_nop_();
	_nop_();
	TM_SCL=0;
}
/*
	��    �ܣ�TM1650��������
*/
void TM1650_Send(unsigned char date1,unsigned char date2)
{
	TM1650_Start();
	TM1650_WriteByte(date1);
	TM1650_WriteByte(date2);
	TM1650_Stop();
}
					/*
	��    �ܣ�TM1650���ֽ�
*/
unsigned char TM1650_ReadByte()
{
	uchar dat, i;
	TM_SDA=1;
	dat=0;
	for(i=0;i<8;i++)
	{		
		TM_SCL=1; //ʱ������
		dat<<=1;
		if(TM_SDA)
		 dat++;
		TM_SCL=0;
	}
      TM_SDA=1;
	  TM_SCL=1;
	  TM_SCL=0;	  
	  return dat;
}
/*
	��    �ܣ�TM1650������
*/
unsigned char TM1650_Read_Button()
{
	unsigned char key;
	TM1650_Start();
    TM1650_WriteByte(Key_Mode); //������ָ��	
	key=TM1650_ReadByte();
	TM1650_Stop();
	return key;
}
