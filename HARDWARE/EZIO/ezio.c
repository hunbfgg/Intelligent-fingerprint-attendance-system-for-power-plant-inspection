/*  ezio.c  */

#include "ezio.h"

/*************************** 文件说明 *******************************/
//ezio 单片机IO简明操作函数封装,不用声明和填写冗长的结构体,一个函数搞定
//像Arduino一样操作IO
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//淘宝搜索"七彩光子 太极M3 STM32开发板"购买超高性价比开发板或获取更多资料
//只供学习使用，未经作者许可，不得用于其它任何用途！
/********************************************************************/  

//版本说明
/*
 V0.001
 2017.12.15 12:53 初始版本

*/


GPIO_TypeDef *  GPIO_Array[]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG/*,GPIOH,GPIOI*/};
const u8 AllPin_Count=((sizeof(GPIO_Array)/sizeof(GPIO_TypeDef*))*PIN_COUNT_IN_GPIO);//所有引脚数量之和




//在开漏模式时，对输入数据寄存器的读访问可得到I/O状态(来自数据手册)
//也就是说,开漏模式时也可以用作输入,外接上拉电阻就可以实现像IIC一样的得线与通信
//而不需要反复切换IO状态(猜想未验证)



/*
* IO模式设置
* pin  : IO名称,可以用PA0,PA1...PG15,也可以用PA(0),PA(1)....PG(15),或者直接使用IO序号0~111
* mode : IO模式,头文件中有宏定义,
*        需要初始化为输出指定电平时可以使用mode|OUT_H或者mode|OUT_L来指定电平,不使用默认输出低电平
*        指定的电平会在IO初始化之前送到输出寄存器,这样可以避免初始化时可能产生的小毛刺
* 说明 :此函数会自动使能所设置IO口的时钟;
*/
void Pin_ModeSet(u8 pin,u8 mode){
	u8 off;                  //偏移量
	u32 tmreg;
	u8 GPIO_Pin;             //0~15
	__IO u32* ctrl;           //
	GPIO_TypeDef * GPIO_t;   //GPIOA~GPIOB
	//检查数据合法性
	if(pin>=AllPin_Count){
		return;
	}
	
	RCC->APB2ENR |= 1<<(pin/PIN_COUNT_IN_GPIO+2);//端口时钟使能
	
	GPIO_t = GPIO_Array[pin/PIN_COUNT_IN_GPIO];   //GPIOA~GPIOB
	GPIO_Pin  =  (pin)%PIN_COUNT_IN_GPIO;           //0~15
	ctrl   =  (u32*)(&((&GPIO_t->CRL)[(GPIO_Pin)/8]));  //
	off    =  GPIO_Pin%8*4;//偏移量
	tmreg  =  *ctrl;
	tmreg &= ~(0x0F<<off);
	
	switch(mode&(~0x80)){
		case INPUT_FL:{	//浮空输入
			tmreg |= INPUT_FL_VALUE<<off;
			break;
		}
		case INPUT_PU:{	//上拉输入
			tmreg |= INPUT_PU_VALUE<<off;
			GPIO_t->BSRR = 1<<GPIO_Pin;
			break;
		}
		case INPUT_PD:{	//下拉输入
			tmreg |= INPUT_PD_VALUE<<off;
			GPIO_t->BRR = 1<<GPIO_Pin;
			break;
		}
		case OUTPUT_PP:{	//推挽输出
			tmreg |= OUTPUT_PP_VALUE<<off;
			if((mode&OUT_H)!=0){
				GPIO_t->BSRR = 1<<GPIO_Pin;
			}
			else{
				GPIO_t->BRR = 1<<GPIO_Pin;
			}
			break;
		}
		case OUTPUT_OD:{	//开漏输出无上下拉
			tmreg |= OUTPUT_OD_VALUE<<off;
			if((mode&OUT_H)!=0){
				GPIO_t->BSRR = 1<<GPIO_Pin;
			}
			else{
				GPIO_t->BRR = 1<<GPIO_Pin;
			}
			break;
		}
//		case OUTPUT_OD_PU:{	//开漏输出带上拉 (F103不支持)
//			
//			break;
//		}
//		case OUTPUT_OD_PD:{	//开漏输出带下拉 (F103不支持)
//			
//			break;
//		}
		
	}
	*ctrl = tmreg;
}
 
/*
* 设置IO输出电平
* pin : IO名称,同上
* value:电平,0 低电平 1 高电平
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
* 设置IO输出低电平
* pin : IO名称,同上
*/
void Pin_WriteLow(u8 pin){
	if(pin>=AllPin_Count){
		return;
	}
	GPIO_Array[(pin)/PIN_COUNT_IN_GPIO]->BRR = 1<<(pin%PIN_COUNT_IN_GPIO);
}
/*
* 设置IO输出高电平
* pin : IO名称,同上
*/
void Pin_WriteHigh(u8 pin){
	if(pin>=AllPin_Count){
		return;
	}
	GPIO_Array[(pin)/PIN_COUNT_IN_GPIO]->BSRR = 1<<(pin%PIN_COUNT_IN_GPIO);
}

/*
* 翻转IO输出电平
* pin : IO名称,同上
*/
void Pin_Toggle(u8 pin){
	if(pin>=AllPin_Count){
		return;
	}
	GPIO_Array[(pin)/PIN_COUNT_IN_GPIO]->ODR ^= 1<<(pin%PIN_COUNT_IN_GPIO);
}
/*
* 获取IO输入状态
* pin : IO名称,同上
* 返回值: 0 低电平  1 高电平
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









