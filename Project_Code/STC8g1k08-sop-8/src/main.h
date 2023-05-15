#ifndef  _MAIN_H_
#define  _MAIN_H_


/**************************************************************************************************
** 编译预处理 ：文件包含；宏定义；变量声明；函数声明
** 应用描述 ：
** 其他说明 ：无
**************************************************************************************************/
/*---------------包含头文件--------------------*/
#include <STC8.H>
#include"intrins.h"
//#include"Time0.h"
//#include"DS18b20.h"
#include"STC_EEPROM.h"
#include"TM1650.h"
#include<stdio.h>
#include <stdlib.h>
//sfr AUXR=0X8E;
/*---------------宏定义------------------*/
#define uint unsigned int
#define uchar unsigned char	

#define address 0x0000	   // EEPROM扇区地址

/*---------------应用变量声明------------------*/
//sbit key1=P3^2;   //按键1
//sbit key2=P3^4;   //按键1


void Display(uint T);
extern bit Stop_Start;
extern uchar Mode;
extern uint Time,Tms1,Tms2;

#endif