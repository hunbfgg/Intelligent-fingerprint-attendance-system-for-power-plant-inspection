
/*  ezio.h  */

#ifndef __EZ_IO_H_
#define __EZ_IO_H_

#include "sys.h"



/*************************** �ļ�˵�� *******************************/
//ezio ��Ƭ��IO��������������װ,������������д�߳��Ľṹ��,һ�������㶨
//��Arduinoһ������IO
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/ 




/***************** IO������ʽ1���ƶ��� *********************/

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


/******************** һЩĬ��ֵ����(���ع���) **********************/
#define PIN_COUNT_IN_GPIO 16//ÿ��GPIO��IO����

#define INPUT_FL_VALUE      0x04
#define INPUT_PU_VALUE      0x08
#define INPUT_PD_VALUE      0x08
#define OUTPUT_PP_VALUE     0x03
#define OUTPUT_OD_VALUE     0x07
//#define OUTPUT_OD_PU_VALUE  0x00
//#define OUTPUT_OD_PD_VALUE  0x00
/****************************** end *********************************/


/********************* IO������ʽ2���ƶ��� **************************/
//����������ʽ����ÿ��GPIOΪ��λ���� ��PA(0) ... PA(15)
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


/*********************** IOģʽ���� *********************************/
//IOģʽ
#define INPUT_FL      1	//��������          0100         0x04
#define INPUT_PU      2	//��������          1000    1    0x08
#define INPUT_PD      3	//��������          1000    0    0x08
#define OUTPUT_PP     4	//�������          00xx         0x03
#define OUTPUT_OD     5	//��©�����������  01xx         0x07
#define OUTPUT_OD_PU  6	//��©��������� (F103��֧��)
#define OUTPUT_OD_PD  7	//��©��������� (F103��֧��)
#define INPUT         INPUT_PU   //Ĭ������Ϊ��������
#define OUTPUT        OUTPUT_PP  //Ĭ�����Ϊ�������

//��ʼ�����õ�ƽ
#define OUT_H  0x80  //�����
#define OUT_L  0x00  //�����
/****************************** end *********************************/


/*************************** �ļ�˵�� *******************************/
//ezio ��Ƭ��IO��������������װ,������������д�߳��Ľṹ��,һ�������㶨
//��Arduinoһ������IO
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/  

/*************************** ����˵�� *******************************/
/*��:
1����ʼ��PB8Ϊ��������͵�ƽ(4��д��)(�͵�ƽ��ʡ��"|OUT_L",��ΪĬ�Ͼ��������)
	 Pin_ModeSet(PB8,OUTPUT);//���Ĭ��Ϊ�������
	 Pin_ModeSet(PB8,OUTPUT_PP);
	 Pin_ModeSet(PB(8),OUTPUT);
	 Pin_ModeSet(PB(8),OUTPUT);
1����ʼ��PB8Ϊ��������ߵ�ƽ(4��д��)
	 Pin_ModeSet(PB8,OUTPUT|OUT_H);//���Ĭ��Ϊ�������
	 Pin_ModeSet(PB8,OUTPUT_PP|OUT_H);
	 Pin_ModeSet(PB(8),OUTPUT|OUT_H);
	 Pin_ModeSet(PB(8),OUTPUT|OUT_H);
3��PD9����ߵ�ƽ
	 Pin_Write(PD9,1);
	 Pin_WriteHigh(PD9);
4����ȡPG5����״̬
	 r=Pin_Read(PG5);
*/
/****************************** end *********************************/




/************************* �������� *********************************/
/*
* ��ȡIO����״̬
* pin : IO����,ͬ��
* ����ֵ: 0 �͵�ƽ  1 �ߵ�ƽ
*/
u8 Pin_Read(u8 pin);
/*
* ��תIO�����ƽ
* pin : IO����,ͬ��
*/
void Pin_Toggle(u8 pin);
/*
* ����IO����ߵ�ƽ
* pin : IO����,ͬ��
*/
void Pin_WriteHigh(u8 pin);
/*
* ����IO����͵�ƽ
* pin : IO����,ͬ��
*/
void Pin_WriteLow(u8 pin);
/*
* ����IO�����ƽ
* pin : IO����,ͬ��
* value:��ƽ,0 �͵�ƽ 1 �ߵ�ƽ
*/
void Pin_Write(u8 pin,u8 value);
/*
* IOģʽ����
* pin  : IO����,������PA0,PA1...PG15,Ҳ������PA(0),PA(1)....PG(15),����ֱ��ʹ��IO���0~111
* mode : IOģʽ,ͷ�ļ����к궨��,
*        ��Ҫ��ʼ��Ϊ���ָ����ƽʱ����ʹ��mode|OUT_H����mode|OUT_L��ָ����ƽ,��ʹ��Ĭ������͵�ƽ
*        ָ���ĵ�ƽ����IO��ʼ��֮ǰ�͵�����Ĵ���,�������Ա����ʼ��ʱ���ܲ�����Сë��
* ˵�� :�˺������Զ�ʹ��������IO�ڵ�ʱ��;
*/
void Pin_ModeSet(u8 pin,u8 mode);


/****************************** end *********************************/






		 				    
#endif







