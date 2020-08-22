/*   24cxx.c   */

#include "24cxx.h" 
#include "delay.h"
#include "ioiic.h"


#define AT24CXX_IIC_Init()         IO_IIC_Init()
#define AT24CXX_IIC_Start()        IO_IIC_Start()
#define AT24CXX_IIC_Stop()         IO_IIC_Stop()
#define AT24CXX_IIC_Write_Byte(x)  IO_IIC_Write_Byte(x)
#define AT24CXX_IIC_Read_Byte(x)   IO_IIC_Read_Byte(x)
#define AT24CXX_IIC_Wait_Ack()     IO_IIC_Wait_Ack()


//��ʼ��IIC�ӿ�
void AT24CXX_Init(void)
{
	AT24CXX_IIC_Init();
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    AT24CXX_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		AT24CXX_IIC_Write_Byte(0XA0);	   //����д����
		AT24CXX_IIC_Wait_Ack();
		AT24CXX_IIC_Write_Byte(ReadAddr>>8);//���͸ߵ�ַ
		AT24CXX_IIC_Wait_Ack();		 
	}else AT24CXX_IIC_Write_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 

	AT24CXX_IIC_Wait_Ack(); 
  AT24CXX_IIC_Write_Byte(ReadAddr%256);   //���͵͵�ַ
	AT24CXX_IIC_Wait_Ack();	    
	AT24CXX_IIC_Start();  	 	   
	AT24CXX_IIC_Write_Byte(0XA1);           //�������ģʽ			   
	AT24CXX_IIC_Wait_Ack();	 
    temp=AT24CXX_IIC_Read_Byte(0);		   
    AT24CXX_IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
  AT24CXX_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		AT24CXX_IIC_Write_Byte(0XA0);	    //����д����
		AT24CXX_IIC_Wait_Ack();
		AT24CXX_IIC_Write_Byte(WriteAddr>>8);//���͸ߵ�ַ
 	}else
	{
		AT24CXX_IIC_Write_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	AT24CXX_IIC_Wait_Ack();	   
  AT24CXX_IIC_Write_Byte(WriteAddr%256);   //���͵͵�ַ
	AT24CXX_IIC_Wait_Ack(); 	 										  		   
	AT24CXX_IIC_Write_Byte(DataToWrite);     //�����ֽ�							   
	AT24CXX_IIC_Wait_Ack();  		    	   
  AT24CXX_IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(255);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











