#ifndef __KEY1_H
#define __KEY1_H	 
#include "stm32f10x.h"
#include "sys.h" 


#define Hang_00_L  GPIO_ResetBits(GPIOG, GPIO_Pin_9)//��00
#define Hang_00_H  GPIO_SetBits(GPIOG, GPIO_Pin_9)
 
#define Hang_01_L  GPIO_ResetBits(GPIOG, GPIO_Pin_7)//��01
#define Hang_01_H  GPIO_SetBits(GPIOG, GPIO_Pin_7)
 
#define Hang_02_L  GPIO_ResetBits(GPIOG, GPIO_Pin_5)//��02
#define Hang_02_H  GPIO_SetBits(GPIOG, GPIO_Pin_5)

#define Hang_03_L  GPIO_ResetBits(GPIOG, GPIO_Pin_3)//��03
#define Hang_03_H  GPIO_SetBits(GPIOG, GPIO_Pin_3)


#define Lie_00_V GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8)//��00
#define Lie_01_V GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_6)//��01
#define Lie_02_V GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4)//��02
#define Lie_03_V GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2)//��03


#define  jpys 1   //�궨�壬Լ��jpys==20�������Ժ������ֲ


void Key_init1(void);//IO��ʼ��
u8 KEY_scan(u8 mode);  	//����ɨ�躯��
extern u8 flag;

#endif


