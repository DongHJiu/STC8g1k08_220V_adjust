#ifndef  _MAIN_H_
#define  _MAIN_H_


/**************************************************************************************************
** ����Ԥ���� ���ļ��������궨�壻������������������
** Ӧ������ ��
** ����˵�� ����
**************************************************************************************************/
/*---------------����ͷ�ļ�--------------------*/
#include <STC8.H>
#include"intrins.h"
//#include"Time0.h"
//#include"DS18b20.h"
#include"STC_EEPROM.h"
#include"TM1650.h"
#include<stdio.h>
#include <stdlib.h>
//sfr AUXR=0X8E;
/*---------------�궨��------------------*/
#define uint unsigned int
#define uchar unsigned char	

#define address 0x0000	   // EEPROM������ַ

/*---------------Ӧ�ñ�������------------------*/
//sbit key1=P3^2;   //����1
//sbit key2=P3^4;   //����1


void Display(uint T);
extern bit Stop_Start;
extern uchar Mode;
extern uint Time,Tms1,Tms2;

#endif