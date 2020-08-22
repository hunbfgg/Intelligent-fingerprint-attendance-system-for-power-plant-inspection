/*  ezio.c  */

#include "ezio.h"

/*************************** �ļ�˵�� *******************************/
//ezio ��Ƭ��IO��������������װ,������������д�߳��Ľṹ��,һ�������㶨
//��Arduinoһ������IO
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/  

//�汾˵��
/*
 V0.001
 2017.12.15 12:53 ��ʼ�汾

*/


GPIO_TypeDef *  GPIO_Array[]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG/*,GPIOH,GPIOI*/};
const u8 AllPin_Count=((sizeof(GPIO_Array)/sizeof(GPIO_TypeDef*))*PIN_COUNT_IN_GPIO);//������������֮��




//�ڿ�©ģʽʱ�����������ݼĴ����Ķ����ʿɵõ�I/O״̬(���������ֲ�)
//Ҳ����˵,��©ģʽʱҲ������������,�����������Ϳ���ʵ����IICһ���ĵ�����ͨ��
//������Ҫ�����л�IO״̬(����δ��֤)



/*
* IOģʽ����
* pin  : IO����,������PA0,PA1...PG15,Ҳ������PA(0),PA(1)....PG(15),����ֱ��ʹ��IO���0~111
* mode : IOģʽ,ͷ�ļ����к궨��,
*        ��Ҫ��ʼ��Ϊ���ָ����ƽʱ����ʹ��mode|OUT_H����mode|OUT_L��ָ����ƽ,��ʹ��Ĭ������͵�ƽ
*        ָ���ĵ�ƽ����IO��ʼ��֮ǰ�͵�����Ĵ���,�������Ա����ʼ��ʱ���ܲ�����Сë��
* ˵�� :�˺������Զ�ʹ��������IO�ڵ�ʱ��;
*/
void Pin_ModeSet(u8 pin,u8 mode){
	u8 off;                  //ƫ����
	u32 tmreg;
	u8 GPIO_Pin;             //0~15
	__IO u32* ctrl;           //
	GPIO_TypeDef * GPIO_t;   //GPIOA~GPIOB
	//������ݺϷ���
	if(pin>=AllPin_Count){
		return;
	}
	
	RCC->APB2ENR |= 1<<(pin/PIN_COUNT_IN_GPIO+2);//�˿�ʱ��ʹ��
	
	GPIO_t = GPIO_Array[pin/PIN_COUNT_IN_GPIO];   //GPIOA~GPIOB
	GPIO_Pin  =  (pin)%PIN_COUNT_IN_GPIO;           //0~15
	ctrl   =  (u32*)(&((&GPIO_t->CRL)[(GPIO_Pin)/8]));  //
	off    =  GPIO_Pin%8*4;//ƫ����
	tmreg  =  *ctrl;
	tmreg &= ~(0x0F<<off);
	
	switch(mode&(~0x80)){
		case INPUT_FL:{	//��������
			tmreg |= INPUT_FL_VALUE<<off;
			break;
		}
		case INPUT_PU:{	//��������
			tmreg |= INPUT_PU_VALUE<<off;
			GPIO_t->BSRR = 1<<GPIO_Pin;
			break;
		}
		case INPUT_PD:{	//��������
			tmreg |= INPUT_PD_VALUE<<off;
			GPIO_t->BRR = 1<<GPIO_Pin;
			break;
		}
		case OUTPUT_PP:{	//�������
			tmreg |= OUTPUT_PP_VALUE<<off;
			if((mode&OUT_H)!=0){
				GPIO_t->BSRR = 1<<GPIO_Pin;
			}
			else{
				GPIO_t->BRR = 1<<GPIO_Pin;
			}
			break;
		}
		case OUTPUT_OD:{	//��©�����������
			tmreg |= OUTPUT_OD_VALUE<<off;
			if((mode&OUT_H)!=0){
				GPIO_t->BSRR = 1<<GPIO_Pin;
			}
			else{
				GPIO_t->BRR = 1<<GPIO_Pin;
			}
			break;
		}
//		case OUTPUT_OD_PU:{	//��©��������� (F103��֧��)
//			
//			break;
//		}
//		case OUTPUT_OD_PD:{	//��©��������� (F103��֧��)
//			
//			break;
//		}
		
	}
	*ctrl = tmreg;
}
 
/*
* ����IO�����ƽ
* pin : IO����,ͬ��
* value:��ƽ,0 �͵�ƽ 1 �ߵ�ƽ
*/
void Pin_Write(u8 pin,u8 value){
	
	if(pin>=AllPin_Count){
		return;
	}
	if(value==0){
		GPIO_Array[(pin)/PIN_COUNT_IN_GPIO]->BRR = 1<<(pin%PIN_COUNT_IN_GPIO);
	}
	else{
		GPIO_Array[(pin)/PIN_COUNT_IN_GPIO]->BSRR = 1<<(pin%PIN_COUNT_IN_GPIO);
	}
}
/*
* ����IO����͵�ƽ
* pin : IO����,ͬ��
*/
void Pin_WriteLow(u8 pin){
	if(pin>=AllPin_Count){
		return;
	}
	GPIO_Array[(pin)/PIN_COUNT_IN_GPIO]->BRR = 1<<(pin%PIN_COUNT_IN_GPIO);
}
/*
* ����IO����ߵ�ƽ
* pin : IO����,ͬ��
*/
void Pin_WriteHigh(u8 pin){
	if(pin>=AllPin_Count){
		return;
	}
	GPIO_Array[(pin)/PIN_COUNT_IN_GPIO]->BSRR = 1<<(pin%PIN_COUNT_IN_GPIO);
}

/*
* ��תIO�����ƽ
* pin : IO����,ͬ��
*/
void Pin_Toggle(u8 pin){
	if(pin>=AllPin_Count){
		return;
	}
	GPIO_Array[(pin)/PIN_COUNT_IN_GPIO]->ODR ^= 1<<(pin%PIN_COUNT_IN_GPIO);
}
/*
* ��ȡIO����״̬
* pin : IO����,ͬ��
* ����ֵ: 0 �͵�ƽ  1 �ߵ�ƽ
*/
u8 Pin_Read(u8 pin){
	if(pin>=AllPin_Count){
		return 0;
	}
	if((GPIO_Array[(pin)/PIN_COUNT_IN_GPIO]->IDR&(1<<(pin%PIN_COUNT_IN_GPIO)))!=0){
		return 1;
	}
	else{
		return 0;
	}
}
//









