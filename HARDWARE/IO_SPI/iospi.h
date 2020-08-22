/*   iospi.h   */

#ifndef __IO_SPI_H_
#define __IO_SPI_H_

#include "sys.h"


/***********************************************************************/
//IO��ģ��SPI������������ֲ�棩
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//Ϊ�˷�����ֲ��Ӳ���ӿ�ȫ���Ժ궨�巽ʽ����
//ע�⣬������Ϊ�����ģ��SPI���ٶȣ������ṩ�˶����Ķ�д��������ѡ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/



/********************* ģ��SPI�ܽż�ʱ�Ӷ��� **************************/
//GPIO����
#define IO_SPI_CS_GPIO       GPIOB
#define IO_SPI_SCLK_GPIO     GPIOB
#define IO_SPI_MISO_GPIO     GPIOB
#define IO_SPI_MOSI_GPIO     GPIOB

#define IO_SPI_CS_PIN         GPIO_Pin_12
#define IO_SPI_SCLK_PIN       GPIO_Pin_13
#define IO_SPI_MISO_PIN       GPIO_Pin_14
#define IO_SPI_MOSI_PIN       GPIO_Pin_15
//ʱ�Ӷ���
#define IO_SPI_CS_RCC_CLK     RCC_APB2Periph_GPIOB
#define IO_SPI_SCLK_RCC_CLK   RCC_APB2Periph_GPIOB
#define IO_SPI_MISO_RCC_CLK   RCC_APB2Periph_GPIOB
#define IO_SPI_MOSI_RCC_CLK   RCC_APB2Periph_GPIOB
/****************************** end *********************************/


/********************* ģ��SPIGPIO�������� **************************/
#define IO_SPI_CS_H()     IO_SPI_CS_GPIO->BSRR = IO_SPI_CS_PIN     //CS�ܽ��ø�
#define IO_SPI_CS_L()     IO_SPI_CS_GPIO->BRR  = IO_SPI_CS_PIN     //CS�ܽ��õ�
#define IO_SPI_SCLK_H()   IO_SPI_SCLK_GPIO->BSRR = IO_SPI_SCLK_PIN //SCLK�ܽ��ø�
#define IO_SPI_SCLK_L()   IO_SPI_SCLK_GPIO->BRR  = IO_SPI_SCLK_PIN //SCLK�ܽ��õ�
#define IO_SPI_MOSI_H()   IO_SPI_MOSI_GPIO->BSRR = IO_SPI_MOSI_PIN //MOSI�ܽ��ø�
#define IO_SPI_MOSI_L()   IO_SPI_MOSI_GPIO->BRR  = IO_SPI_MOSI_PIN //MOSI�ܽ��õ�

//��ȡMISO�ܽ�����״̬
#define IO_SPI_MISO_GET_IN()  ((IO_SPI_MISO_GPIO->IDR & IO_SPI_MISO_PIN)?(1):(0))
/****************************** end *********************************/


/************************* ģ��SPI�������� **************************/
void    IO_SPI_Init(void);                //IOģ��SPI��س�ʼ��
uint8_t IO_SPI_Read_Byte(void);           //IOģ��SPI��ȡһ���ֽ�
void    IO_SPI_Write_Byte(uint8_t byte);  //IOģ��SPIдһ���ֽ�
uint8_t IO_SPI_RW_Byte(uint8_t byte);     //IOģ��SPI�ֽڶ�д
/****************************** end *********************************/


























#endif


































