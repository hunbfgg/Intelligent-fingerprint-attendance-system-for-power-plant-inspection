/*   ioiic.c   */

#include "ioiic.h"
#include "delay.h"



void IO_IIC_Init(void){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(IO_IIC_SCL_RCC_CLK|IO_IIC_SDA_RCC_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = IO_IIC_SCL_PIN;			     //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
	GPIO_Init(IO_IIC_SCL_GPIO, &GPIO_InitStructure);      //�����趨������ʼ��
	GPIO_SetBits(IO_IIC_SCL_GPIO,IO_IIC_SCL_PIN);		       //�����
	
	GPIO_InitStructure.GPIO_Pin = IO_IIC_SDA_PIN;			     //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //�������
	GPIO_Init(IO_IIC_SDA_GPIO, &GPIO_InitStructure);      //�����趨������ʼ��
	GPIO_SetBits(IO_IIC_SDA_GPIO,IO_IIC_SDA_PIN);		       //�����

}

/************ ��ʼ�ź� ****************/
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

/************ �����ź� ****************/
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

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IO_IIC_Wait_Ack(){
	u8 t=0;
	IO_IIC_SDA_H();//�ͷ�����
	IO_IIC_SDA_SET_IN();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_H();
	delay_us(IIC_DELAY_TIME);
	while(IO_IIC_SDA_GET_IN()){
		t++;
		if(t>250){
			IO_IIC_SDA_SET_OUT();
			IO_IIC_Stop();
			return 1;//δ���յ�ACK�ź�
		}
	}
	IO_IIC_SCL_L();
	IO_IIC_SDA_SET_OUT();
	return 0;//���յ�Ӧ��
}

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
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


//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IO_IIC_Read_Byte(uint8_t ack){
	uint8_t i;
	uint8_t r=0;
	IO_IIC_SCL_L();
	IO_IIC_SDA_H();//�ͷ�����
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
		IO_IIC_SDA_H();//1 ��Ӧ��
	}
	else{
		IO_IIC_SDA_L();//0 Ӧ��
	}
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_H();
	delay_us(IIC_DELAY_TIME);
	IO_IIC_SCL_L();
	
	return r;
}



