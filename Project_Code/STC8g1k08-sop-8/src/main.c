/*
  �� �� �� ��: 220V-TM1605��ѹ����
  �� �� о Ƭ: STC8G1K08-sop-8
  TM1602-KEY1: �л������ѹ
	TM1602-KEY2: ��λ+1
	TM1602-KEY3: ��λ��1
*/

/*��������
  �������  = P3^2 
  PWM����ź� = P3^3
  TM1605-CLK  = P5^4   
  TM1605-DIO  = P5^5;
*/

#include"main.h"


#define FOSC 11059200L
#define T1MS (65536-FOSC/20000)      //1000 == 1ms

//**********8�����ȵ���***********************************
uchar code liangdu[]={0xFF,0x11,0x21,0x31,0x41,0x51,0x61,0x71,0x01};//1-8�����ȵ���
uchar code duanma[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
                     0x77,0x7c,0x39,0x5e,0x79,0x71,0x80};
					 //************�����������ʾ0-F

uchar Student_max_num; //�༶�������
uchar Mode;			   //ģʽ
uint Time,Tms1,Tms2;			   //�Զ��ػ�ʱ��
bit Stop_Start; 	   //ֹͣ_����
uchar light;
unsigned char bdata dat; //dat�ǿ�λѰַ�ı���

sbit dat7=dat^7;
sbit dat6=dat^6;
sbit dat5=dat^5;
sbit dat4=dat^4;
sbit dat3=dat^3;
sbit dat2=dat^2;
sbit dat1=dat^1;
sbit dat0=dat^0; //ȡ��dat�ĸ���λ

										 
sbit IN_Data = P3^2;    //������ź�����
sbit PWM_Out = P3^3;		//PWM����ź�								  
sbit LEDS = P3^1;      //�ж϶�ʱ�ж��Ƿ�����
sbit LEDLS = P3^0;     //�ж��ⲿ�ж��Ƿ�����

uint TIME_INT = 0;
uint Data_s = 0;
long Time_SM = 0;

bit LEDLS_D = 0;

/*---------------Ӧ�ú�������------------------*/
void Systerm_init(void);   //ϵͳ��ʼ��
void Control(void);       //���̺���
void EXINT_Init(void);
void Timer0_Init(void);


void delay(uint t)   
{
	uchar x;
	while(t--)for(x=120;x>0;x--);
}
/******************************************************************
 - ����������������
 - ����ģ�飺��
 - �������ԣ���
 - ����˵������      
 - ����˵������
 - ע����
 ******************************************************************/
void main()
{
  uint a=0;
	uint d=0;
  TM1650_Send(0x48,0x61);// ������ʾ��1������  	
	Mode=1;
	
	PWM_Out = 1;
	EXINT_Init();
	Timer0_Init();
	P3M0 = 0x00; P3M1 = 0x00; 
	P5M0 = 0x00; P5M1 = 0x00; 
	//P1M0 = 0x02; P1M1 = 0x00; 

	LEDLS = 1;
	Data_s = 1000;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[2]);TM1650_Send(0X6A,duanma[2]);TM1650_Send(0X6C,duanma[0]);
	while(1)
  {
		
		if(d == 0)
		{
			switch(a)
			{
				case 0: Data_s = 1000;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[2]);TM1650_Send(0X6A,duanma[2]);TM1650_Send(0X6C,duanma[0]); break;
				case 1: Data_s = 3100;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[1]);TM1650_Send(0X6A,duanma[8]);TM1650_Send(0X6C,duanma[0]); break;
				case 2: Data_s = 4800;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[1]);TM1650_Send(0X6A,duanma[2]);TM1650_Send(0X6C,duanma[0]); break;
				case 3: Data_s = 6040;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[0]);TM1650_Send(0X6A,duanma[8]);TM1650_Send(0X6C,duanma[0]); break;
				case 4: Data_s = 7420;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[0]);TM1650_Send(0X6A,duanma[4]);TM1650_Send(0X6C,duanma[8]); break;					
			}
		}		
		if(d != 0)
		{
			if(Time_SM < 10000)
			{
				switch(a)
				{
					case 0: Data_s = 1000;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[2]);TM1650_Send(0X6A,duanma[2]);TM1650_Send(0X6C,duanma[0]); break;
					case 1: Data_s = 3140;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[1]);TM1650_Send(0X6A,duanma[8]);TM1650_Send(0X6C,duanma[0]); break;
					case 2: Data_s = 4800;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[1]);TM1650_Send(0X6A,duanma[2]);TM1650_Send(0X6C,duanma[0]); break;
					case 3: Data_s = 6040;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[0]);TM1650_Send(0X6A,duanma[8]);TM1650_Send(0X6C,duanma[0]); break;
					case 4: Data_s = 7420;TM1650_Send(0x48,0x61);TM1650_Send(0X68,duanma[0]);TM1650_Send(0X6A,duanma[4]);TM1650_Send(0X6C,duanma[8]); break;			
				}
			}
			else{TM1650_Send(0x48,0x00);}
		}		


//		Data_s = 4800;
		if(a > 4){a = 0;}
		dat=TM1650_Read_Button();                        //��ȡ����ģʽ,�а������½�����һ��8λ������
		if(dat6==1)                                      //���λ��һӦ�þ����а���������
		{
			if(dat3==0 && dat4==0) {d = ~d;}   
			if(dat3==1 && dat4==0) 
			{
				if(d != 0)
				{
					a++;
				}
			}
			if(dat3==0 && dat4==1)  
			{
				if(d != 0)
				{
					a--;
				}
			}	
			while(dat6==1)dat=TM1650_Read_Button(); 
			dat=0XFF;
		}
	}

}




void EXINT_Init()
{
	//PWM_Out = 0; // ��ʼ����P1.1Ϊ�͵�ƽ Ϩ��LED
	IT0 = 1; // ����INT0���ж����� (1:���½��� 0:�����غ��½���)
	EX0 = 1; // ʹ��INT0�ж�
	EA = 1;  // �����ж�
}

////50us
void Timer0_Init(void)		//100??@11.0592MHz
{
    AUXR |= 0x80;                   //???0?1T??
//  AUXR &= 0x7f;                   //???0?12T??

    TMOD = 0x00;                    //????????0(16??????)
    TL0 = T1MS;                     //??????
    TH0 = T1MS >> 8;
    TR0 = 1;                        //???0????
    ET0 = 1;                        //?????0??
    EA = 1;
}

//�ⲿ�жϷ�����
void Exint0() interrupt 0 //INT0�ж����
{
	  PWM_Out = 1;
		TIME_INT = 1;   //��־λ	
	if(LEDLS_D){LEDLS = ~LEDLS;}

}

//��ʱ�ж�1������
void Time0() interrupt 1
{	  
	
	static uint i = 0;
	static uint x = 0;
	static uint CP_Time = 0;

	if(TIME_INT == 1)
	{
		i++;
		CP_Time = (Data_s + 2000) / 50;
		if(i == CP_Time)
		{
			PWM_Out = 0;// 
			TIME_INT = 0;
			i = 0;
		}
	}
	
	if(++x > 10000)
	{
		LEDLS_D = ~LEDLS_D;
		LEDS = ~LEDS;
		x = 0;
	}
	
	Time_SM++;	
	if(Time_SM > 20000){Time_SM = 0;}
	
}



