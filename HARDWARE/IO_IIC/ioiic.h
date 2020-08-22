/*   ioiic.h   */

#ifndef __IO_IIC_H_
#define __IO_IIC_H_

#include "sys.h"


#define IO_IIC_SCL_GPIO  GPIOB
#define IO_IIC_SDA_GPIO  GPIOB


#define IO_IIC_SCL_PIN  GPIO_Pin_6
#define IO_IIC_SDA_PIN  GPIO_Pin_7


#define IO_IIC_SCL_RCC_CLK RCC_APB2Periph_GPIOB
#define IO_IIC_SDA_RCC_CLK RCC_APB2Periph_GPIOB


#define IO_IIC_SDA_SET_OUT()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
#define IO_IIC_SDA_SET_IN()   {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}


#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}




#define IO_IIC_SCL_H()  IO_IIC_SCL_GPIO->BSRR = IO_IIC_SCL_PIN
#define IO_IIC_SCL_L()  IO_IIC_SCL_GPIO->BRR  = IO_IIC_SCL_PIN
#define IO_IIC_SDA_H()  IO_IIC_SDA_GPIO->BSRR = IO_IIC_SDA_PIN
#define IO_IIC_SDA_L()  IO_IIC_SDA_GPIO->BRR  = IO_IIC_SDA_PIN


#define IO_IIC_SDA_GET_IN()  (((IO_IIC_SDA_GPIO->IDR & IO_IIC_SDA_PIN)!=0)?(1):(0))



#define IIC_DELAY_TIME	(4)


//IO²Ù×÷º¯Êý	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //ÊäÈëSDA 






void IO_IIC_Init(void);
void IO_IIC_Start(void);
void IO_IIC_Stop(void);
void IO_IIC_Ack(void);
void IO_IIC_NoAck(void);
uint8_t IO_IIC_Wait_Ack(void);
void IO_IIC_Write_Byte(uint8_t byte);
uint8_t IO_IIC_Read_Byte(uint8_t ack);




#endif
















