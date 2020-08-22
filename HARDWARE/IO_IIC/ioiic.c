/*   ioiic.c   */

#include "ioiic.h"
#include "delay.h"



void IO_IIC_Init(void){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(IO_IIC_SCL_RCC_CLK|IO_IIC_SDA_RCC_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = IO_IIC_SCL_PIN;			     //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
	GPIO_Init(IO_IIC_SCL_GPIO, &GPIO_InitStructure);      //根据设定参数初始化
	GPIO_SetBits(IO_IIC_SCL_GPIO,IO_IIC_SCL_PIN);		       //输出高
	
	GPIO_InitStructure.GPIO_Pin = IO_IIC_SDA_PIN;			     //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //推挽输出
	GPIO_Init(IO_IIC_SDA_GPIO, &GPIO_InitStructure);      //根据设定参数初始化
	GPIO_SetBits(IO_IIC_SDA_GPIO,IO_IIC_SDA_PIN);		       //输出高

}

/************ 起始信号 ****************/
//              ____________
// SCL ________/            \______
//     ______________
// SDA               \_____________
//
/*************************************/
void IO_IIC_Start(void){
	IO_IIC_SCL_L();
	IO_IIC_SDA_H();
	IO_IIC_SCL_H();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SDA_L();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_L();
	delay_us(IIC_DELAY_TIME);	
}

/************ 结束信号 ****************/
//              ___________________
// SCL ________/            
//                    _____________
// SDA ______________/            
//
/*************************************/
void IO_IIC_Stop(void){
	IO_IIC_SCL_L();
	IO_IIC_SDA_L();
	IO_IIC_SCL_H();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SDA_H();
	delay_us(IIC_DELAY_TIME);
}


void IO_IIC_Ack(){
	IO_IIC_SCL_L();
	IO_IIC_SDA_L();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_H();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_H();
}

void IO_IIC_NoAck(){
	IO_IIC_SCL_L();
	IO_IIC_SDA_H();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_H();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_H();
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IO_IIC_Wait_Ack(){
	u8 t=0;
	IO_IIC_SDA_H();//释放总线
	IO_IIC_SDA_SET_IN();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_H();
	delay_us(IIC_DELAY_TIME);
	while(IO_IIC_SDA_GET_IN()){
		t++;
		if(t>250){
			IO_IIC_SDA_SET_OUT();
			IO_IIC_Stop();
			return 1;//未接收到ACK信号
		}
	}
	IO_IIC_SCL_L();
	IO_IIC_SDA_SET_OUT();
	return 0;//接收到应答
}

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IO_IIC_Write_Byte(uint8_t byte){
	uint8_t i;
	IO_IIC_SCL_L();
	for(i=0;i<8;i++){
		if((byte&0x80)!=0){
			IO_IIC_SDA_H();
		}
		else{
			IO_IIC_SDA_L();
		}
		byte <<= 1;
		delay_us(IIC_DELAY_TIME);
		IO_IIC_SCL_H();
		delay_us(IIC_DELAY_TIME);
		IO_IIC_SCL_L();
		delay_us(IIC_DELAY_TIME);
	}
}


//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IO_IIC_Read_Byte(uint8_t ack){
	uint8_t i;
	uint8_t r=0;
	IO_IIC_SCL_L();
	IO_IIC_SDA_H();//释放总线
	IO_IIC_SDA_SET_IN();
	delay_us(IIC_DELAY_TIME);
	for(i=0;i<8;i++){
		IO_IIC_SCL_H();
		delay_us(IIC_DELAY_TIME);
		r <<= 1;
		if(IO_IIC_SDA_GET_IN()){
			r++;
		}
		IO_IIC_SCL_L();
		delay_us(IIC_DELAY_TIME);
	}
	IO_IIC_SDA_SET_OUT();
	
	//ACK
	if(ack==0){
		IO_IIC_SDA_H();//1 非应答
	}
	else{
		IO_IIC_SDA_L();//0 应答
	}
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_H();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_L();
	
	return r;
}



