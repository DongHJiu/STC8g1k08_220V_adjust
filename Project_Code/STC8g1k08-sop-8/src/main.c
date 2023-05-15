/*
  工 程 功 能: 220V-TM1605调压控制
  主 控 芯 片: STC8G1K08-sop-8
  TM1602-KEY1: 切换输出电压
	TM1602-KEY2: 挡位+1
	TM1602-KEY3: 挡位—1
*/

/*引脚配置
  过零点检测  = P3^2 
  PWM输出信号 = P3^3
  TM1605-CLK  = P5^4   
  TM1605-DIO  = P5^5;
*/

#include"main.h"


#define FOSC 11059200L
#define T1MS (65536-FOSC/20000)      //1000 == 1ms

//**********8级亮度调节***********************************
uchar code liangdu[]={0xFF,0x11,0x21,0x31,0x41,0x51,0x61,0x71,0x01};//1-8级亮度调节
uchar code duanma[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
                     0x77,0x7c,0x39,0x5e,0x79,0x71,0x80};
					 //************共阴数码管显示0-F

uchar Student_max_num; //班级最大人数
uchar Mode;			   //模式
uint Time,Tms1,Tms2;			   //自动关机时间
bit Stop_Start; 	   //停止_启动
uchar light;
unsigned char bdata dat; //dat是可位寻址的变量

sbit dat7=dat^7;
sbit dat6=dat^6;
sbit dat5=dat^5;
sbit dat4=dat^4;
sbit dat3=dat^3;
sbit dat2=dat^2;
sbit dat1=dat^1;
sbit dat0=dat^0; //取出dat的各个位

										 
sbit IN_Data = P3^2;    //过零点信号输入
sbit PWM_Out = P3^3;		//PWM输出信号								  
sbit LEDS = P3^1;      //判断定时中断是否正常
sbit LEDLS = P3^0;     //判断外部中断是否正常

uint TIME_INT = 0;
uint Data_s = 0;
long Time_SM = 0;

bit LEDLS_D = 0;

/*---------------应用函数声明------------------*/
void Systerm_init(void);   //系统初始化
void Control(void);       //键盘函数
void EXINT_Init(void);
void Timer0_Init(void);


void delay(uint t)   
{
	uchar x;
	while(t--)for(x=120;x>0;x--);
}
/******************************************************************
 - 功能描述：主函数
 - 隶属模块：无
 - 函数属性：无
 - 参数说明：无      
 - 返回说明：无
 - 注：无
 ******************************************************************/
void main()
{
  uint a=0;
	uint d=0;
  TM1650_Send(0x48,0x61);// 开启显示、1级亮度  	
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
		dat=TM1650_Read_Button();                        //读取按键模式,有按键按下将返回一个8位是数据
		if(dat6==1)                                      //这个位置一应该就是有按键按下了
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
	//PWM_Out = 0; // 初始设置P1.1为低电平 熄灭LED
	IT0 = 1; // 设置INT0的中断类型 (1:仅下降沿 0:上升沿和下降沿)
	EX0 = 1; // 使能INT0中断
	EA = 1;  // 打开总中断
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

//外部中断服务函数
void Exint0() interrupt 0 //INT0中断入口
{
	  PWM_Out = 1;
		TIME_INT = 1;   //标志位	
	if(LEDLS_D){LEDLS = ~LEDLS;}

}

//定时中断1服务函数
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



