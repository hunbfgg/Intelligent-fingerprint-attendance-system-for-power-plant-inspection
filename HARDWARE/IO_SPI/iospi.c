/*   iospi.c   */

#include "iospi.h"



/***********************************************************************/
//IO口模拟SPI驱动程序（易移植版）
//此程序适用于七彩光子太极M3—STM32F103开发板及部分兼容的STM32系统，
//为了方便移植，硬件接口全部以宏定义方式给出
//注意，本驱动为了提高模拟SPI的速度，单独提供了独立的读写函数，可选用
//只供学习使用，未经作者许可，不得用于其它任何用途！
/***********************************************************************/
 

//模拟SPI初始化函数，主要初始化了IO口模式
void IO_SPI_Init(void){                //IO模拟SPI相关初始化
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(IO_SPI_CS_RCC_CLK|IO_SPI_SCLK_RCC_CLK\
	     |IO_SPI_MOSI_RCC_CLK|IO_SPI_MISO_RCC_CLK, ENABLE);	 //使能端口时钟

	GPIO_InitStructure.GPIO_Pin = IO_SPI_CS_PIN;			     //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
	GPIO_Init(IO_SPI_CS_GPIO, &GPIO_InitStructure);		     //根据设定参数初始化
	GPIO_SetBits(IO_SPI_CS_GPIO,IO_SPI_CS_PIN);		         //输出高

	GPIO_InitStructure.GPIO_Pin = IO_SPI_SCLK_PIN;	       //端口配置, 推挽输出
	GPIO_Init(IO_SPI_SCLK_GPIO, &GPIO_InitStructure);	 		 //根据设定参数初始化
	GPIO_SetBits(IO_SPI_SCLK_GPIO,IO_SPI_SCLK_PIN); 	     //输出高 

	GPIO_InitStructure.GPIO_Pin = IO_SPI_MOSI_PIN;	 	     //端口配置, 推挽输出
	GPIO_Init(IO_SPI_MOSI_GPIO, &GPIO_InitStructure);	  	 //根据设定参数初始化
	GPIO_SetBits(IO_SPI_MOSI_GPIO,IO_SPI_MOSI_PIN); 		   //输出高 

	GPIO_InitStructure.GPIO_Pin = IO_SPI_MISO_PIN;	 	     //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		     //上拉输入
	GPIO_Init(IO_SPI_MISO_GPIO, &GPIO_InitStructure);	  	 //根据参数配置
	
}



//模拟SPI读取一个字节（半双工）
//未使用循环以提高速度
//注意：在读取过程中会写入0xFF，也可写入0x00,请根据需求修改
uint8_t IO_SPI_Read_Byte(void){           //IO模拟SPI读取一个字节
	uint8_t r=0;
	
	IO_SPI_SCLK_H();
	IO_SPI_MOSI_H();//写入0xFF
	
	//bit7
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit6
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit5
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit4
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit3
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit2
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit1
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();
	r <<= 1;
	
	//bit0
	IO_SPI_SCLK_L();
	if(IO_SPI_MISO_GET_IN())r++;
	IO_SPI_SCLK_H();

	return r;
}



//IO模拟SPI写一个字节（半双工）
//未使用循环以提高速度
void IO_SPI_Write_Byte(uint8_t byte){  
	uint8_t cnt=0x80;
	
	IO_SPI_SCLK_H();
	
	//BIT7
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit6
	cnt >>= 1;
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit5
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit4
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit3
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit2
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit1
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
	
	//bit0
	cnt >>= 1;	
	(byte&cnt)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
	IO_SPI_SCLK_L();
	IO_SPI_SCLK_H();
}



//模拟SPI全双工读写一个字节
uint8_t IO_SPI_RW_Byte(uint8_t byte){    //IO模拟SPI字节读写
	uint8_t r=0;
	uint8_t i;
	IO_SPI_SCLK_H();
	for(i=0;i<8;i++){
		(byte&0x80)?(IO_SPI_MOSI_H()):(IO_SPI_MOSI_L());
		IO_SPI_SCLK_L();
		byte <<= 1;
		r <<= 1;
		if(IO_SPI_MISO_GET_IN())r++;
		IO_SPI_SCLK_H();
	}
	return r;
}
































































































































