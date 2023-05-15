/**************************************************************************************************
//程序名称 ：STC_EEPROM
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

/**************************************************************************************************
** 编译预处理 ：文件包含；宏定义；变量声明；函数声明
** 应用描述 ：
** 其他说明 ：无
**************************************************************************************************/

/*---------------包含头文件--------------------*/
#include"main.h"



/******************************************************************
 - 功能描述：打开 ISP/IAP 功能
 - 隶属模块：STC_EEPROM 模块
 - 函数属性：内部，供内部使用
 - 参数说明：无      
 - 返回说明：无
 - 注：无
 ******************************************************************/
void ISP_IAP_enable()
{
	EA=0;				   // 关中断 	
	IAP_CONTR&=0x18;       //0001,1000确认其余位为零
	IAP_CONTR|=WaitTime;   // 写入硬件延时
	IAP_CONTR|=0x80;       //ISPEN=1；允许编程改变Flash
}


/******************************************************************
 - 功能描述：关闭 ISP/IAP 功能
 - 隶属模块：STC_EEPROM 模块
 - 函数属性：内部，供内部使用
 - 参数说明：无      
 - 返回说明：无
 - 注：无
 ******************************************************************/
void ISP_IAP_disable()
{
	IAP_CONTR&=0x7f;	//ISPEN = 0；禁止ISP/IAP编程改变Flash 
	IAP_TRIG=0x00;
	EA=1;			// 开中断
}

/******************************************************************
 - 功能描述：ISP/IAP公用的触发代码
 - 隶属模块：STC_EEPROM 模块
 - 函数属性：内部，供内部使用
 - 参数说明：无      
 - 返回说明：无
 - 注：无
 ******************************************************************/
void ISPgoon()
{
	ISP_IAP_enable();	//打开 ISP,IAP 功能	
	IAP_TRIG=0x5A;		//触发ISP_IAP命令字节1
	IAP_TRIG=0xA5;		//触发ISP_IAP命令字节2
	_nop_();
}


/******************************************************************
 - 功能描述：ISP/IAP扇区擦除
 - 隶属模块：STC_EEPROM 模块
 - 函数属性：外部，供用户使用
 - 参数说明：sector_addr:要擦除的扇区地址      
 - 返回说明：无
 - 注：无
 ******************************************************************/
void ISP_sectorerase(unsigned int sector_addr)
{
	unsigned int iSectorAddr;
	iSectorAddr=(sector_addr&0xfe00);    //取扇区地址
	IAP_ADDRH=(unsigned char)(iSectorAddr>>8);
	IAP_ADDRL=0x00;

	IAP_CMD&=0xf8;			//清空低3位 
	IAP_CMD|=EraseCommand;	//擦除命令3

	ISPgoon();						//触发执行	
	ISP_IAP_disable();				// 关闭ISP,IAP功能

}

/******************************************************************
 - 功能描述：ISP/IAP字节读取
 - 隶属模块：STC_EEPROM 模块
 - 函数属性：外部，供用户使用
 - 参数说明：byte_addr：要读取的STC_EEPROM的单元地址      
 - 返回说明：无
 - 注：无
 ******************************************************************/
unsigned char ISP_byte_read(unsigned int byte_addr)
{
	IAP_ADDRH=(unsigned char)(byte_addr>>8);	 //地址赋值
	IAP_ADDRL=(unsigned char)(byte_addr&0x00ff);

	IAP_CMD&=0xf8;			//清除低3位 
	IAP_CMD|=RdCommand;	   //写入读命令

	ISPgoon();						//触发执行
	ISP_IAP_disable();				//关闭ISP,IAP功能
	return (IAP_DATA);				//返回读到的数据
}


/******************************************************************
 - 功能描述：ISP/IAP字节写入
 - 隶属模块：STC_EEPROM 模块
 - 函数属性：外部，供用户使用
 - 参数说明：byte_addr：要写入的STC_EEPROM的单元地址
             original_data：要写入的数据      
 - 返回说明：无
 - 注：无
 ******************************************************************/
void ISP_byte_write(unsigned int byte_addr, unsigned char original_data)
{
	IAP_ADDRH =	(unsigned char)(byte_addr>>8); 	//取地址
	IAP_ADDRL =	(unsigned char)(byte_addr&0x00ff);

	IAP_CMD&=0xf8;				//清低3位
	IAP_CMD|=PrgCommand;		//写命令2
	IAP_DATA=original_data;		//写入数据准备

	ISPgoon();							//触发执行
	ISP_IAP_disable();					//关闭IAP功能
}

/******************************************************************
 - 功能描述：ISP/IAP字节写并校验
 - 隶属模块：STC_EEPROM 模块
 - 函数属性：外部，供用户使用
 - 参数说明：byte_addr：要写入的STC_EEPROM的单元地址
             original_data：要写入的数据       
 - 返回说明：无
 - 注：无
 ***************************************************************** 
unsigned char ISP_byte_write_verify(unsigned int byte_addr, unsigned char original_data) 
{ 
	 ISP_ADDRH=(unsigned char)(byte_addr>>8); //取地址
	 ISP_ADDRL=(unsigned char)(byte_addr&0xff); 
	
	 ISP_CMD&=0xf8;  //清低3位 								
	 ISP_CMD|=PrgCommand;  // 写命令2
	 ISP_DATA=original_data; 
	
	 ISPgoon();   // 触发执行
	
	 // 开始读，没有在此重复给地址，地址不会被自动改变 
	 ISP_DATA=0x00;  // 清数据传递寄存器 
	
	 ISP_CMD&=0xf8;  // 清低3位
	 ISP_CMD|=RdCommand;// 读命令1 
	
	 ISP_TRIG=0x46;  // 触发ISP_IAP命令字节1 
	 ISP_TRIG=0xb9;  // 触发ISP_IAP命令字节2 
	 _nop_();   //延时 										
	
	 ISP_IAP_disable();  //关闭IAP功能 
	
	 if(ISP_DATA==original_data)// 读写数据校验 
	    return Ok;   //返回校验结果 
	 else 
	    return Error; 
}
*/
/******************************************************************
 - 功能描述：ISP/IAP数组写入
 - 隶属模块：STC_EEPROM 模块
 - 函数属性：外部，供用户使用
 - 参数说明：begin_addr：要写入的STC_EEPROM的单元地址
             len：要写入的个数
			 array：指向要写入数据缓冲区的指针
 - 返回说明：无
 - 注：无
 *****************************************************************
unsigned char ISP_arraywrite(unsigned int begin_addr,unsigned int len,unsigned char *array)
{ 
	unsigned int  i; 
	unsigned int  in_addr; 

	// 判是否是有效范围,此函数不允许跨扇区操作 //
	if(len>PerSector) 
	return Error; 
	in_addr=begin_addr&0x01ff; // 扇区内偏移量 
	if((in_addr+len)>PerSector) 
	return Error; 								  
	in_addr=begin_addr; 
	// 逐个写入并校对 //
	for(i=0;i<len;i++) 
	{ 
		// 写一个字节 //
		ISP_ADDRH=(unsigned char)(in_addr>>8); 
		ISP_ADDRL=(unsigned char)(in_addr&0x00ff); 
		ISP_DATA=array[i];  // 取数据   				   
		ISP_CMD&=0xf8;   // 清低3位                                 
		ISP_CMD|=PrgCommand;   //  写命令0x02   

		ISPgoon();							//触发执行		
		
		// 开始读，没有在此重复给地址，地址不会被自动改变 //
		ISP_DATA=0x00; // 清数据传递寄存器 
		
		ISP_CMD&=0xf8; // 清低3位 
		ISP_CMD|=RdCommand; // 读命令1 
															
		ISPgoon();							// 触发执行
		
    	// 比较对错 //
		if(ISP_DATA!=array[i]) 
		{ 
			ISP_IAP_disable(); 
			return Error; 
		} 
		in_addr++;  // 指向下一个字节 
	} 
	ISP_IAP_disable(); 	// 关闭IAP功能
	return Ok; 
} 
*/
/******************************************************************
 - 功能描述：ISP/IAP扇区读出
 - 隶属模块：STC_EEPROM 模块
 - 函数属性：外部，供用户使用
 - 参数说明：begin_addr：要读取的STC_EEPROM的单元地址
             len：要读取的个数
			 array：指向要存放的数据缓冲区的指针      
 - 返回说明：无
 - 注：程序对地址没有作有效性判断，请调用前事先保证他在规定范围内
 ***************************************************************** 
void ISP_arrayread(unsigned int begin_addr,unsigned char len, unsigned char *array) 
{ 
	unsigned int iSectorAddr; 
	unsigned int i; 
	iSectorAddr=begin_addr;  //&0xfe00; 取扇区地址 	    
	for(i=0;i<len;i++) 
	{ 
		ISP_ADDRH=(unsigned char)(iSectorAddr>>8); 
		ISP_ADDRL=(unsigned char)(iSectorAddr&0x00ff); 
																
		ISP_CMD&=0xf8;   // 清低3位 
		ISP_CMD|=RdCommand;  // 读命令1 
		ISP_DATA=0x00; 
				
		ISPgoon();							// 触发执行	
						
		array[i]=ISP_DATA; 
		iSectorAddr++; 
	} 
	ISP_IAP_disable();  // 关闭IAP功能 			  
}
 */