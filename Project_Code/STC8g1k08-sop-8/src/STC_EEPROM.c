/**************************************************************************************************
//�������� ��STC_EEPROM
//Ӧ��оƬ ��
//��Ƶ�λ ��
//������� ��Yanggang
//�������� ��2011��8��8��
//�޸����� �� 
//�޸����� �� 
//�汾 �� V1.0
//��Ȩ ��
//------------------------------------------------------------------------------------------------
//���������� �� 
//--------------
//--------------
//--------------
//------------------------------------------------------------------------------------------------
**************************************************************************************************/

/**************************************************************************************************
** ����Ԥ���� ���ļ��������궨�壻������������������
** Ӧ������ ��
** ����˵�� ����
**************************************************************************************************/

/*---------------����ͷ�ļ�--------------------*/
#include"main.h"



/******************************************************************
 - ������������ ISP/IAP ����
 - ����ģ�飺STC_EEPROM ģ��
 - �������ԣ��ڲ������ڲ�ʹ��
 - ����˵������      
 - ����˵������
 - ע����
 ******************************************************************/
void ISP_IAP_enable()
{
	EA=0;				   // ���ж� 	
	IAP_CONTR&=0x18;       //0001,1000ȷ������λΪ��
	IAP_CONTR|=WaitTime;   // д��Ӳ����ʱ
	IAP_CONTR|=0x80;       //ISPEN=1�������̸ı�Flash
}


/******************************************************************
 - �����������ر� ISP/IAP ����
 - ����ģ�飺STC_EEPROM ģ��
 - �������ԣ��ڲ������ڲ�ʹ��
 - ����˵������      
 - ����˵������
 - ע����
 ******************************************************************/
void ISP_IAP_disable()
{
	IAP_CONTR&=0x7f;	//ISPEN = 0����ֹISP/IAP��̸ı�Flash 
	IAP_TRIG=0x00;
	EA=1;			// ���ж�
}

/******************************************************************
 - ����������ISP/IAP���õĴ�������
 - ����ģ�飺STC_EEPROM ģ��
 - �������ԣ��ڲ������ڲ�ʹ��
 - ����˵������      
 - ����˵������
 - ע����
 ******************************************************************/
void ISPgoon()
{
	ISP_IAP_enable();	//�� ISP,IAP ����	
	IAP_TRIG=0x5A;		//����ISP_IAP�����ֽ�1
	IAP_TRIG=0xA5;		//����ISP_IAP�����ֽ�2
	_nop_();
}


/******************************************************************
 - ����������ISP/IAP��������
 - ����ģ�飺STC_EEPROM ģ��
 - �������ԣ��ⲿ�����û�ʹ��
 - ����˵����sector_addr:Ҫ������������ַ      
 - ����˵������
 - ע����
 ******************************************************************/
void ISP_sectorerase(unsigned int sector_addr)
{
	unsigned int iSectorAddr;
	iSectorAddr=(sector_addr&0xfe00);    //ȡ������ַ
	IAP_ADDRH=(unsigned char)(iSectorAddr>>8);
	IAP_ADDRL=0x00;

	IAP_CMD&=0xf8;			//��յ�3λ 
	IAP_CMD|=EraseCommand;	//��������3

	ISPgoon();						//����ִ��	
	ISP_IAP_disable();				// �ر�ISP,IAP����

}

/******************************************************************
 - ����������ISP/IAP�ֽڶ�ȡ
 - ����ģ�飺STC_EEPROM ģ��
 - �������ԣ��ⲿ�����û�ʹ��
 - ����˵����byte_addr��Ҫ��ȡ��STC_EEPROM�ĵ�Ԫ��ַ      
 - ����˵������
 - ע����
 ******************************************************************/
unsigned char ISP_byte_read(unsigned int byte_addr)
{
	IAP_ADDRH=(unsigned char)(byte_addr>>8);	 //��ַ��ֵ
	IAP_ADDRL=(unsigned char)(byte_addr&0x00ff);

	IAP_CMD&=0xf8;			//�����3λ 
	IAP_CMD|=RdCommand;	   //д�������

	ISPgoon();						//����ִ��
	ISP_IAP_disable();				//�ر�ISP,IAP����
	return (IAP_DATA);				//���ض���������
}


/******************************************************************
 - ����������ISP/IAP�ֽ�д��
 - ����ģ�飺STC_EEPROM ģ��
 - �������ԣ��ⲿ�����û�ʹ��
 - ����˵����byte_addr��Ҫд���STC_EEPROM�ĵ�Ԫ��ַ
             original_data��Ҫд�������      
 - ����˵������
 - ע����
 ******************************************************************/
void ISP_byte_write(unsigned int byte_addr, unsigned char original_data)
{
	IAP_ADDRH =	(unsigned char)(byte_addr>>8); 	//ȡ��ַ
	IAP_ADDRL =	(unsigned char)(byte_addr&0x00ff);

	IAP_CMD&=0xf8;				//���3λ
	IAP_CMD|=PrgCommand;		//д����2
	IAP_DATA=original_data;		//д������׼��

	ISPgoon();							//����ִ��
	ISP_IAP_disable();					//�ر�IAP����
}

/******************************************************************
 - ����������ISP/IAP�ֽ�д��У��
 - ����ģ�飺STC_EEPROM ģ��
 - �������ԣ��ⲿ�����û�ʹ��
 - ����˵����byte_addr��Ҫд���STC_EEPROM�ĵ�Ԫ��ַ
             original_data��Ҫд�������       
 - ����˵������
 - ע����
 ***************************************************************** 
unsigned char ISP_byte_write_verify(unsigned int byte_addr, unsigned char original_data) 
{ 
	 ISP_ADDRH=(unsigned char)(byte_addr>>8); //ȡ��ַ
	 ISP_ADDRL=(unsigned char)(byte_addr&0xff); 
	
	 ISP_CMD&=0xf8;  //���3λ 								
	 ISP_CMD|=PrgCommand;  // д����2
	 ISP_DATA=original_data; 
	
	 ISPgoon();   // ����ִ��
	
	 // ��ʼ����û���ڴ��ظ�����ַ����ַ���ᱻ�Զ��ı� 
	 ISP_DATA=0x00;  // �����ݴ��ݼĴ��� 
	
	 ISP_CMD&=0xf8;  // ���3λ
	 ISP_CMD|=RdCommand;// ������1 
	
	 ISP_TRIG=0x46;  // ����ISP_IAP�����ֽ�1 
	 ISP_TRIG=0xb9;  // ����ISP_IAP�����ֽ�2 
	 _nop_();   //��ʱ 										
	
	 ISP_IAP_disable();  //�ر�IAP���� 
	
	 if(ISP_DATA==original_data)// ��д����У�� 
	    return Ok;   //����У���� 
	 else 
	    return Error; 
}
*/
/******************************************************************
 - ����������ISP/IAP����д��
 - ����ģ�飺STC_EEPROM ģ��
 - �������ԣ��ⲿ�����û�ʹ��
 - ����˵����begin_addr��Ҫд���STC_EEPROM�ĵ�Ԫ��ַ
             len��Ҫд��ĸ���
			 array��ָ��Ҫд�����ݻ�������ָ��
 - ����˵������
 - ע����
 *****************************************************************
unsigned char ISP_arraywrite(unsigned int begin_addr,unsigned int len,unsigned char *array)
{ 
	unsigned int  i; 
	unsigned int  in_addr; 

	// ���Ƿ�����Ч��Χ,�˺������������������ //
	if(len>PerSector) 
	return Error; 
	in_addr=begin_addr&0x01ff; // ������ƫ���� 
	if((in_addr+len)>PerSector) 
	return Error; 								  
	in_addr=begin_addr; 
	// ���д�벢У�� //
	for(i=0;i<len;i++) 
	{ 
		// дһ���ֽ� //
		ISP_ADDRH=(unsigned char)(in_addr>>8); 
		ISP_ADDRL=(unsigned char)(in_addr&0x00ff); 
		ISP_DATA=array[i];  // ȡ����   				   
		ISP_CMD&=0xf8;   // ���3λ                                 
		ISP_CMD|=PrgCommand;   //  д����0x02   

		ISPgoon();							//����ִ��		
		
		// ��ʼ����û���ڴ��ظ�����ַ����ַ���ᱻ�Զ��ı� //
		ISP_DATA=0x00; // �����ݴ��ݼĴ��� 
		
		ISP_CMD&=0xf8; // ���3λ 
		ISP_CMD|=RdCommand; // ������1 
															
		ISPgoon();							// ����ִ��
		
    	// �Ƚ϶Դ� //
		if(ISP_DATA!=array[i]) 
		{ 
			ISP_IAP_disable(); 
			return Error; 
		} 
		in_addr++;  // ָ����һ���ֽ� 
	} 
	ISP_IAP_disable(); 	// �ر�IAP����
	return Ok; 
} 
*/
/******************************************************************
 - ����������ISP/IAP��������
 - ����ģ�飺STC_EEPROM ģ��
 - �������ԣ��ⲿ�����û�ʹ��
 - ����˵����begin_addr��Ҫ��ȡ��STC_EEPROM�ĵ�Ԫ��ַ
             len��Ҫ��ȡ�ĸ���
			 array��ָ��Ҫ��ŵ����ݻ�������ָ��      
 - ����˵������
 - ע������Ե�ַû������Ч���жϣ������ǰ���ȱ�֤���ڹ涨��Χ��
 ***************************************************************** 
void ISP_arrayread(unsigned int begin_addr,unsigned char len, unsigned char *array) 
{ 
	unsigned int iSectorAddr; 
	unsigned int i; 
	iSectorAddr=begin_addr;  //&0xfe00; ȡ������ַ 	    
	for(i=0;i<len;i++) 
	{ 
		ISP_ADDRH=(unsigned char)(iSectorAddr>>8); 
		ISP_ADDRL=(unsigned char)(iSectorAddr&0x00ff); 
																
		ISP_CMD&=0xf8;   // ���3λ 
		ISP_CMD|=RdCommand;  // ������1 
		ISP_DATA=0x00; 
				
		ISPgoon();							// ����ִ��	
						
		array[i]=ISP_DATA; 
		iSectorAddr++; 
	} 
	ISP_IAP_disable();  // �ر�IAP���� 			  
}
 */