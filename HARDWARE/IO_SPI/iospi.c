/*   iospi.c   */

#include "iospi.h"



/***********************************************************************/
//IO��ģ��SPI������������ֲ�棩
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//Ϊ�˷�����ֲ��Ӳ���ӿ�ȫ���Ժ궨�巽ʽ����
//ע�⣬������Ϊ�����ģ��SPI���ٶȣ������ṩ�˶����Ķ�д��������ѡ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 

//ģ��SPI��ʼ����������Ҫ��ʼ����IO��ģʽ
void IO_SPI_Init(void){                //IOģ��SPI��س�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(IO_SPI_CS_RCC_CLK|IO_SPI_SCLK_RCC_CLK\
	     |IO_SPI_MOSI_RCC_CLK|IO_SPI_MISO_RCC_CLK, ENABLE);	 //ʹ�ܶ˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = IO_SPI_CS_PIN;			     //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
	GPIO_Init(IO_SPI_CS_GPIO, &GPIO_InitStructure);		     //�����趨������ʼ��
	GPIO_SetBits(IO_SPI_CS_GPIO,IO_SPI_CS_PIN);		         //�����

	GPIO_InitStructure.GPIO_Pin = IO_SPI_SCLK_PIN;	       //�˿�����, �������
	GPIO_Init(IO_SPI_SCLK_GPIO, &GPIO_InitStructure);	 		 //�����趨������ʼ��
	GPIO_SetBits(IO_SPI_SCLK_GPIO,IO_SPI_SCLK_PIN); 	     //����� 

	GPIO_InitStructure.GPIO_Pin = IO_SPI_MOSI_PIN;	 	     //�˿�����, �������
	GPIO_Init(IO_SPI_MOSI_GPIO, &GPIO_InitStructure);	  	 //�����趨������ʼ��
	GPIO_SetBits(IO_SPI_MOSI_GPIO,IO_SPI_MOSI_PIN); 		   //����� 

	GPIO_InitStructure.GPIO_Pin = IO_SPI_MISO_PIN;	 	     //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		     //��������
	GPIO_Init(IO_SPI_MISO_GPIO, &GPIO_InitStructure);	  	 //���ݲ�������
	
}



//ģ��SPI��ȡһ���ֽڣ���˫����
//δʹ��ѭ��������ٶ�
//ע�⣺�ڶ�ȡ�����л�д��0xFF��Ҳ��д��0x00,����������޸�
uint8_t IO_SPI_Read_Byte(void){           //IOģ��SPI��ȡһ���ֽ�
	uint8_t r=0;
	
	IO_SPI_SCLK_H();
	IO_SPI_MOSI_H();//д��0xFF
	
	//bit7
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit6
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit5
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit4
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit3
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit2
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit1
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit0
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();

	return r;
}



//IOģ��SPIдһ���ֽڣ���˫����
//δʹ��ѭ��������ٶ�
void IO_SPI_Write_Byte(uint8_t byte){  
	uint8_t cnt=0x80;
	
	IO_SPI_SCLK_H();
	
	//BIT7
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit6
	cnt >>= 1;
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit5
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit4
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit3
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit2
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit1
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit0
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
}



//ģ��SPIȫ˫����дһ���ֽ�
uint8_t IO_SPI_RW_Byte(uint8_t byte){    //IOģ��SPI�ֽڶ�д
	uint8_t r=0;
	uint8_t i;
	IO_SPI_SCLK_H();
	for(i=0;i<8;i++){
		(byte&0x80)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
		IO_SPI_SCLK_L();
		byte <<= 1;
		r <<= 1;
		if(IO_SPI_MISO_GET_IN())r++;
		IO_SPI_SCLK_H();
	}
	return r;
}
































































































































