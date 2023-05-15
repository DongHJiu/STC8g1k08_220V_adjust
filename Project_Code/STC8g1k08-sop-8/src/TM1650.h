#ifndef  _TM1650_H_
#define  _TM1650_H_

#include "main.h"

#define DIG1  0x68  //��һλ��
#define DIG2  0x6A  //�ڶ�λ��
#define DIG3  0x6C  //����λ��
#define DIG4  0x6E  //����λ��

#define Display_Mode 0x48  //��ʾģʽ
#define Key_Mode  0x49	  //����ģʽ

#define Brightness_Level8	0x00	//���ȼ���8
#define Brightness_Level7	0x70	//���ȼ���7
#define Brightness_Level6	0x60	//���ȼ���6
#define Brightness_Level5	0x50	//���ȼ���5
#define Brightness_Level4	0x40	//���ȼ���4
#define Brightness_Level3	0x30	//���ȼ���3
#define Brightness_Level2	0x20	//���ȼ���2
#define Brightness_Level1	0x10	//���ȼ���1

#define Display_Block8	0x00	//8����ʾģʽ
#define Display_Block7	0x80	//7����ʾģʽ

#define Start_Display	0x01	//����ʾ
#define Stop_Display	0x00	//����ʾ

sbit TM_SCL=P5^4;//ʱ����
sbit TM_SDA=P5^5;//������

///*
//	����ܶ����
//*/
//unsigned char code duanma[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x80};
//					/*	  0		1	  2		3	  4	    5	  6	    7	  8	    9	  a     b     c     d     e     f    .   */

void TM1650_Send(unsigned char date1,unsigned char date2);
unsigned char TM1650_Read_Button();
//void TM1650_WriteByte(unsigned char date);
#endif 
