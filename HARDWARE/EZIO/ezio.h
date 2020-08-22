
/*  ezio.h  */

#ifndef __EZ_IO_H_
#define __EZ_IO_H_

#include "sys.h"



/*************************** 文件说明 *******************************/
//ezio 单片机IO简明操作函数封装,不用声明和填写冗长的结构体,一个函数搞定
//像Arduino一样操作IO
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/ 




/***************** IO命名方式1名称定义 *********************/

#define	PA0 	0
#define	PA1 	1
#define	PA2 	2
#define	PA3 	3
#define	PA4 	4
#define	PA5 	5
#define	PA6 	6
#define	PA7 	7
#define	PA8 	8
#define	PA9 	9
#define	PA10	10
#define	PA11	11
#define	PA12	12
#define	PA13	13
#define	PA14	14
#define	PA15	15
#define	PB0 	16
#define	PB1 	17
#define	PB2 	18
#define	PB3 	19
#define	PB4 	20
#define	PB5 	21
#define	PB6 	22
#define	PB7 	23
#define	PB8 	24
#define	PB9 	25
#define	PB10	26
#define	PB11	27
#define	PB12	28
#define	PB13	29
#define	PB14	30
#define	PB15	31
#define	PC0 	32
#define	PC1 	33
#define	PC2 	34
#define	PC3 	35
#define	PC4 	36
#define	PC5 	37
#define	PC6 	38
#define	PC7 	39
#define	PC8 	40
#define	PC9 	41
#define	PC10	42
#define	PC11	43
#define	PC12	44
#define	PC13	45
#define	PC14	46
#define	PC15	47
#define	PD0 	48
#define	PD1 	49
#define	PD2 	50
#define	PD3 	51
#define	PD4 	52
#define	PD5 	53
#define	PD6 	54
#define	PD7 	55
#define	PD8 	56
#define	PD9 	57
#define	PD10	58
#define	PD11	59
#define	PD12	60
#define	PD13	61
#define	PD14	62
#define	PD15	63
#define	PE0 	64
#define	PE1 	65
#define	PE2 	66
#define	PE3 	67
#define	PE4 	68
#define	PE5 	69
#define	PE6 	70
#define	PE7 	71
#define	PE8 	72
#define	PE9 	73
#define	PE10	74
#define	PE11	75
#define	PE12	76
#define	PE13	77
#define	PE14	78
#define	PE15	79
#define	PF0 	80
#define	PF1 	81
#define	PF2 	82
#define	PF3 	83
#define	PF4 	84
#define	PF5 	85
#define	PF6 	86
#define	PF7 	87
#define	PF8 	88
#define	PF9 	89
#define	PF10	90
#define	PF11	91
#define	PF12	92
#define	PF13	93
#define	PF14	94
#define	PF15	95
#define	PG0 	96
#define	PG1 	97
#define	PG2 	98
#define	PG3 	99
#define	PG4 	100
#define	PG5 	101
#define	PG6 	102
#define	PG7 	103
#define	PG8 	104
#define	PG9 	105
#define	PG10	106
#define	PG11	107
#define	PG12	108
#define	PG13	109
#define	PG14	110
#define	PG15	111
//#define	PH0 	112
//#define	PH1 	113
//#define	PH2 	114
//#define	PH3 	115
//#define	PH4 	116
//#define	PH5 	117
//#define	PH6 	118
//#define	PH7 	119
//#define	PH8 	120
//#define	PH9 	121
//#define	PH10	122
//#define	PH11	123
//#define	PH12	124
//#define	PH13	125
//#define	PH14	126
//#define	PH15	127
//#define	PI0 	128
//#define	PI1 	129
//#define	PI2 	130
//#define	PI3 	131
//#define	PI4 	132
//#define	PI5 	133
//#define	PI6 	134
//#define	PI7 	135
//#define	PI8 	136
//#define	PI9 	137
//#define	PI10	138
//#define	PI11	139
//#define	PI12	140
//#define	PI13	141
//#define	PI14	142
//#define	PI15	143
//#define	PJ0 	144
//#define	PJ1 	145
//#define	PJ2 	146
//#define	PJ3 	147
//#define	PJ4 	148
//#define	PJ5 	149
//#define	PJ6 	150
//#define	PJ7 	151
//#define	PJ8 	152
//#define	PJ9 	153
//#define	PJ10	154
//#define	PJ11	155
//#define	PJ12	156
//#define	PJ13	157
//#define	PJ14	158
//#define	PJ15	159
//#define	PK0 	160
//#define	PK1 	161
//#define	PK2 	162
//#define	PK3 	163
//#define	PK4 	164
//#define	PK5 	165
//#define	PK6 	166
//#define	PK7 	167
//#define	PK8 	168
//#define	PK9 	169
//#define	PK10	170
//#define	PK11	171
//#define	PK12	172
//#define	PK13	173
//#define	PK14	174
//#define	PK15	175
/****************************** end *********************************/


/******************** 一些默认值定义(不必关心) **********************/
#define PIN_COUNT_IN_GPIO 16//每组GPIO的IO数量

#define INPUT_FL_VALUE      0x04
#define INPUT_PU_VALUE      0x08
#define INPUT_PD_VALUE      0x08
#define OUTPUT_PP_VALUE     0x03
#define OUTPUT_OD_VALUE     0x07
//#define OUTPUT_OD_PU_VALUE  0x00
//#define OUTPUT_OD_PD_VALUE  0x00
/****************************** end *********************************/


/********************* IO命名方式2名称定义 **************************/
//此种命名方式可以每组GPIO为单位调用 如PA(0) ... PA(15)
#define PA(n)  (0*PIN_COUNT_IN_GPIO+(n))
#define PB(n)  (1*PIN_COUNT_IN_GPIO+(n))
#define PC(n)  (2*PIN_COUNT_IN_GPIO+(n))
#define PD(n)  (3*PIN_COUNT_IN_GPIO+(n))
#define PE(n)  (4*PIN_COUNT_IN_GPIO+(n))
#define PF(n)  (5*PIN_COUNT_IN_GPIO+(n))
#define PG(n)  (6*PIN_COUNT_IN_GPIO+(n))
//#define PH(n)  (7*PIN_COUNT_IN_GPIO+(n))
//#define PI(n)  (8*PIN_COUNT_IN_GPIO+(n))
//#define PJ(n)  (9*PIN_COUNT_IN_GPIO+(n))

/****************************** end *********************************/


/*********************** IO模式定义 *********************************/
//IO模式
#define INPUT_FL      1	//浮空输入          0100         0x04
#define INPUT_PU      2	//上拉输入          1000    1    0x08
#define INPUT_PD      3	//下拉输入          1000    0    0x08
#define OUTPUT_PP     4	//推挽输出          00xx         0x03
#define OUTPUT_OD     5	//开漏输出无上下拉  01xx         0x07
#define OUTPUT_OD_PU  6	//开漏输出带上拉 (F103不支持)
#define OUTPUT_OD_PD  7	//开漏输出带下拉 (F103不支持)
#define INPUT         INPUT_PU   //默认输入为上拉输入
#define OUTPUT        OUTPUT_PP  //默认输出为推挽输出

//初始化引用电平
#define OUT_H  0x80  //输出高
#define OUT_L  0x00  //输出低
/****************************** end *********************************/


/*************************** 文件说明 *******************************/
//ezio 单片机IO简明操作函数封装,不用声明和填写冗长的结构体,一个函数搞定
//像Arduino一样操作IO
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/  

/*************************** 调用说明 *******************************/
/*例:
1、初始化PB8为推挽输出低电平(4种写法)(低电平可省略"|OUT_L",因为默认就是输出低)
	 Pin_ModeSet(PB8,OUTPUT);//输出默认为推挽输出
	 Pin_ModeSet(PB8,OUTPUT_PP);
	 Pin_ModeSet(PB(8),OUTPUT);
	 Pin_ModeSet(PB(8),OUTPUT);
1、初始化PB8为推挽输出高电平(4种写法)
	 Pin_ModeSet(PB8,OUTPUT|OUT_H);//输出默认为推挽输出
	 Pin_ModeSet(PB8,OUTPUT_PP|OUT_H);
	 Pin_ModeSet(PB(8),OUTPUT|OUT_H);
	 Pin_ModeSet(PB(8),OUTPUT|OUT_H);
3、PD9输出高电平
	 Pin_Write(PD9,1);
	 Pin_WriteHigh(PD9);
4、获取PG5输入状态
	 r=Pin_Read(PG5);
*/
/****************************** end *********************************/




/************************* 函数声明 *********************************/
/*
* 获取IO输入状态
* pin : IO名称,同上
* 返回值: 0 低电平  1 高电平
*/
u8 Pin_Read(u8 pin);
/*
* 翻转IO输出电平
* pin : IO名称,同上
*/
void Pin_Toggle(u8 pin);
/*
* 设置IO输出高电平
* pin : IO名称,同上
*/
void Pin_WriteHigh(u8 pin);
/*
* 设置IO输出低电平
* pin : IO名称,同上
*/
void Pin_WriteLow(u8 pin);
/*
* 设置IO输出电平
* pin : IO名称,同上
* value:电平,0 低电平 1 高电平
*/
void Pin_Write(u8 pin,u8 value);
/*
* IO模式设置
* pin  : IO名称,可以用PA0,PA1...PG15,也可以用PA(0),PA(1)....PG(15),或者直接使用IO序号0~111
* mode : IO模式,头文件中有宏定义,
*        需要初始化为输出指定电平时可以使用mode|OUT_H或者mode|OUT_L来指定电平,不使用默认输出低电平
*        指定的电平会在IO初始化之前送到输出寄存器,这样可以避免初始化时可能产生的小毛刺
* 说明 :此函数会自动使能所设置IO口的时钟;
*/
void Pin_ModeSet(u8 pin,u8 mode);


/****************************** end *********************************/






		 				    
#endif







