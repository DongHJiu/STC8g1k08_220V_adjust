#include"TM1650.h"

/*
	数 据 写 入 步 骤：Start->Address->Data->Ack->Stop。
*/

/*
	功    能：TM1650开始
*/
void TM1650_Start(void)			
{
	TM_SCL=1;//时钟
	TM_SDA=1;
	_nop_();
	_nop_();
	TM_SDA=0;
	_nop_();
	_nop_();
	TM_SCL=0;
}

/*
	功    能：TM1650结束
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
	功    能：TM1650写字节
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
	功    能：TM1650发送数据
*/
void TM1650_Send(unsigned char date1,unsigned char date2)
{
	TM1650_Start();
	TM1650_WriteByte(date1);
	TM1650_WriteByte(date2);
	TM1650_Stop();
}
					/*
	功    能：TM1650读字节
*/
unsigned char TM1650_ReadByte()
{
	uchar dat, i;
	TM_SDA=1;
	dat=0;
	for(i=0;i<8;i++)
	{		
		TM_SCL=1; //时钟上沿
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
	功    能：TM1650读按键
*/
unsigned char TM1650_Read_Button()
{
	unsigned char key;
	TM1650_Start();
    TM1650_WriteByte(Key_Mode); //读按键指令	
	key=TM1650_ReadByte();
	TM1650_Stop();
	return key;
}
