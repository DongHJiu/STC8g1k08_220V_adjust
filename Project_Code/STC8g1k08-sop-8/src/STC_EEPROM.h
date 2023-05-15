/**************************************************************************************************
//程序名称 ： STC_EEPROM应用函数声明
//应用芯片 ：
//设计单位 ：
//设计作者 ：Yanggang
//创建日期 ：2011年8月8日
//修改作者 ： 
//修改日期 ： 
//版本 ： V1.0
//版权 ：
//------------------------------------------------------------------------------------------------
//程序功能描述 ： 
//--------------
//--------------
//--------------
//------------------------------------------------------------------------------------------------
**************************************************************************************************/

#ifndef  _STC_EEPROM_H_
#define  _STC_EEPROM_H_

/**************************************************************************************************
** 编译预处理 ：文件包含；宏定义；变量声明；函数声明
** 应用描述 ：
** 其他说明 ：无
**************************************************************************************************/
/*---------------包含头文件--------------------*/
#include"main.h"
 
/*---------------应用宏定义--------------------*/

#define RdCommand		0x01  //读命令
#define PrgCommand		0x02  //写命令
#define EraseCommand     	0x03  //扇区擦除命令
#define Error   1
#define Ok      0
#define WaitTime	0x01   //设置等待时间
#define PerSector	512	  //定义每个扇区有效地址

//unsigned char xdata Ttotal[512];  //定义数据缓冲区

/*---------------应用变量声明------------------*/

 

/*---------------应用函数声明------------------*/
void ISP_sectorerase(unsigned int sector_addr);	// 扇区擦除
unsigned char ISP_byte_read(unsigned int byte_addr);		// byte读
void ISP_byte_write(unsigned int byte_addr, unsigned char original_data);	// byte写
unsigned char ISP_byte_write_verify(unsigned int byte_addr, unsigned char original_data);// byte写并校验
unsigned char ISP_arraywrite(unsigned int begin_addr, unsigned int len,unsigned char *array);	// byte数组写并校验
void ISP_arrayread(unsigned int begin_addr, unsigned char len, unsigned char *array);		// 读出, 保存在数组中


#endif