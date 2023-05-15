/**************************************************************************************************
//�������� �� STC_EEPROMӦ�ú�������
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

#ifndef  _STC_EEPROM_H_
#define  _STC_EEPROM_H_

/**************************************************************************************************
** ����Ԥ���� ���ļ��������궨�壻������������������
** Ӧ������ ��
** ����˵�� ����
**************************************************************************************************/
/*---------------����ͷ�ļ�--------------------*/
#include"main.h"
 
/*---------------Ӧ�ú궨��--------------------*/

#define RdCommand		0x01  //������
#define PrgCommand		0x02  //д����
#define EraseCommand     	0x03  //������������
#define Error   1
#define Ok      0
#define WaitTime	0x01   //���õȴ�ʱ��
#define PerSector	512	  //����ÿ��������Ч��ַ

//unsigned char xdata Ttotal[512];  //�������ݻ�����

/*---------------Ӧ�ñ�������------------------*/

 

/*---------------Ӧ�ú�������------------------*/
void ISP_sectorerase(unsigned int sector_addr);	// ��������
unsigned char ISP_byte_read(unsigned int byte_addr);		// byte��
void ISP_byte_write(unsigned int byte_addr, unsigned char original_data);	// byteд
unsigned char ISP_byte_write_verify(unsigned int byte_addr, unsigned char original_data);// byteд��У��
unsigned char ISP_arraywrite(unsigned int begin_addr, unsigned int len,unsigned char *array);	// byte����д��У��
void ISP_arrayread(unsigned int begin_addr, unsigned char len, unsigned char *array);		// ����, ������������


#endif