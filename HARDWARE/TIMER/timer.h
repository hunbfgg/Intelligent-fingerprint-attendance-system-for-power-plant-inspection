#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//extern u8 flag2;
extern u8 flag3;
extern u8 flag5;
extern u8 flag4;
extern u8 min_five;
extern u8 count;
extern u8 return_time_flag;
extern int clock_set[4];
extern u8 time_save[7];
void TIM7_Int_Init(u16 arr,u16 psc);
void TIM6_Int_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);

#endif
