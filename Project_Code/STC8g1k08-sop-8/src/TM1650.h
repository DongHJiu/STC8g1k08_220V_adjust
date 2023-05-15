#ifndef  _TM1650_H_
#define  _TM1650_H_

#include "main.h"

#define DIG1  0x68  //第一位码
#define DIG2  0x6A  //第二位码
#define DIG3  0x6C  //第三位码
#define DIG4  0x6E  //第四位码

#define Display_Mode 0x48  //显示模式
#define Key_Mode  0x49	  //按键模式

#define Brightness_Level8	0x00	//亮度级别：8
#define Brightness_Level7	0x70	//亮度级别：7
#define Brightness_Level6	0x60	//亮度级别：6
#define Brightness_Level5	0x50	//亮度级别：5
#define Brightness_Level4	0x40	//亮度级别：4
#define Brightness_Level3	0x30	//亮度级别：3
#define Brightness_Level2	0x20	//亮度级别：2
#define Brightness_Level1	0x10	//亮度级别：1

#define Display_Block8	0x00	//8段显示模式
#define Display_Block7	0x80	//7段显示模式

#define Start_Display	0x01	//开显示
#define Stop_Display	0x00	//关显示

sbit TM_SCL=P5^4;//时钟线
sbit TM_SDA=P5^5;//数据线

///*
//	数码管段码表
//*/
//unsigned char code duanma[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x80};
//					/*	  0		1	  2		3	  4	    5	  6	    7	  8	    9	  a     b     c     d     e     f    .   */

void TM1650_Send(unsigned char date1,unsigned char date2);
unsigned char TM1650_Read_Button();
//void TM1650_WriteByte(unsigned char date);
#endif 
