#ifndef __KEY1_H
#define __KEY1_H	 
#include "stm32f10x.h"
#include "sys.h" 


#define Hang_00_L  GPIO_ResetBits(GPIOG, GPIO_Pin_9)//行00
#define Hang_00_H  GPIO_SetBits(GPIOG, GPIO_Pin_9)
 
#define Hang_01_L  GPIO_ResetBits(GPIOG, GPIO_Pin_7)//行01
#define Hang_01_H  GPIO_SetBits(GPIOG, GPIO_Pin_7)
 
#define Hang_02_L  GPIO_ResetBits(GPIOG, GPIO_Pin_5)//行02
#define Hang_02_H  GPIO_SetBits(GPIOG, GPIO_Pin_5)

#define Hang_03_L  GPIO_ResetBits(GPIOG, GPIO_Pin_3)//行03
#define Hang_03_H  GPIO_SetBits(GPIOG, GPIO_Pin_3)


#define Lie_00_V GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8)//列00
#define Lie_01_V GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_6)//列01
#define Lie_02_V GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4)//列02
#define Lie_03_V GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2)//列03


#define  jpys 1   //宏定义，约定jpys==20，方便以后程序移植


void Key_init1(void);//IO初始化
u8 KEY_scan(u8 mode);  	//按键扫描函数
extern u8 flag;

#endif


