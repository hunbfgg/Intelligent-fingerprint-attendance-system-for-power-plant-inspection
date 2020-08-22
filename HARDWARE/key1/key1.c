///************************************************************
//正面朝上黑引脚为行，白引脚为列 
//A、B 、C 、D  分别返回 10 11 12 13
//*为 14
//#为 15
//0为 16
//无按键按下返回0
//*************************************************************/

#include "key1.h"
#include "delay.h"
#include "sys.h" 

u8 flag=0,x;

//矩阵键盘引脚初始化
void Key_init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG,ENABLE);//使能PORTB,PORTD，PORTG时钟

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_9;  //键盘输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOG,&GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_4|GPIO_Pin_2; //键盘输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOG,&GPIO_InitStructure);	
}

//mode:0,不支持连续按;1,支持连续按;
u8 KEY_scan(u8 mode)
{
//	int KeyVal=0;
	static u8 key0_up=1;//按键按松开标志
	static u8 key1_up=1;//按键按松开标志
	static u8 key2_up=1;//按键按松开标志
	static u8 key3_up=1;//按键按松开标志
	static u8 key4_up=1;//按键按松开标志
	static u8 key5_up=1;//按键按松开标志
	static u8 key6_up=1;//按键按松开标志
	static u8 key7_up=1;//按键按松开标志
	static u8 key8_up=1;//按键按松开标志
	static u8 key9_up=1;//按键按松开标志
	static u8 keyA_up=1;//按键按松开标志
	static u8 keyB_up=1;//按键按松开标志
	static u8 keyC_up=1;//按键按松开标志
	static u8 keyD_up=1;//按键按松开标志
	static u8 keyX_up=1;//按键按松开标志
	static u8 keyJ_up=1;//按键按松开标志
	
	if(mode)
	{
		key0_up=1;
    key1_up=1;
	  key2_up=1;
		key3_up=1;
		key4_up=1;
		key5_up=1;
		key6_up=1;
		key7_up=1;
		key8_up=1;
		key9_up=1;
		keyA_up=1;
		keyB_up=1;
		keyC_up=1;
		keyD_up=1;
		keyX_up=1;
		keyJ_up=1;	
	}
	
    //第一行
	Hang_00_L;//把第一行输出低电平
	Hang_01_H;
	Hang_02_H;
	Hang_03_H;
		if(key1_up&&Lie_00_V==0)
		{    
		   delay_ms(jpys); //延时20秒，软件消抖
			
		   key1_up=0;
		   if(Lie_00_V==0) //如果第一列是低电平，说明有键被按下，如果没有直接退出if语句
		   {
			  return 1;
				
		   }
		}else if(Lie_00_V==1)key1_up=1;
	 
		if(key2_up&&Lie_01_V==0)//如果第二列是低电平，
		{    
		   delay_ms(jpys);//延时20秒，软件消抖
		   key2_up=0;
		   if(Lie_01_V==0)//如果第二列是低电平，说明有键被按下，如果没有直接退出if语句
		   {
			  return 2; 
			
		   }
		}else if(Lie_01_V==1)key2_up=1;
	 
		if(key3_up&&Lie_02_V==0)
		{    
		   delay_ms(jpys);
		   key3_up=0;
		   if(Lie_02_V==0)
		   {
			  return 3;
			
		   }
		}else if(Lie_02_V==1)key3_up=1;
	 
		if(keyA_up&&Lie_03_V==0)//如果第四列是低电平
		{    
		   delay_ms(jpys);
		   keyA_up=0;
		   if(Lie_03_V==0)//如果第四列是低电平，说明有键被按下，如果没有直接退出if语句
		   {
			  return 10;
			
		   }
		}else if(Lie_03_V==1)keyA_up=1;
 
	//第二行
	Hang_00_H;
	Hang_01_L;//把第二行拉低
	Hang_02_H;
	Hang_03_H;
		if(key4_up&&Lie_00_V==0)//如果第一列是低电平
		{    
		   delay_ms(jpys);
		   key4_up=0;
		   if(Lie_00_V==0)//说明有键被按下，如果没有直接退出if语句
		   {
				return 4;
				
		   }
		}else if(Lie_00_V==1)key4_up=1;
		 
		if(key5_up&&Lie_01_V==0)
		{    
		   delay_ms(jpys);
		   key5_up=0;
		   if(Lie_01_V==0)
		   {
		       return 5;
				
		   }
		}else if(Lie_01_V==1)key5_up=1;
		 
		if(key6_up&&Lie_02_V==0)
		{    
		   delay_ms(jpys);
		   key6_up=0;
		   if(Lie_02_V==0)
		   {
			   return 6;
				
		   }
		}else if(Lie_02_V==1)key6_up=1;
		 
		if(keyB_up&&Lie_03_V==0)
		{    
		   delay_ms(jpys);
		   keyB_up=0;
		   if(Lie_03_V==0)
		   {
		       return 11; 
						 
		   }
		}else if(Lie_03_V==1)keyB_up=1;
 
	//第三行
	Hang_00_H;
	Hang_01_H;
	Hang_02_L;//把第三行置低
	Hang_03_H;
		if(key7_up&&Lie_00_V==0) //如果第一列是低电平
		{    
		   delay_ms(jpys);//延时20秒
		   key7_up=0;
		   if(Lie_00_V==0)//说明有键被按下，如果没有直接退出if语句
		   {
			   return 7;
			
		   }
		}else if(Lie_00_V==1)key7_up=1;
		 
		if(key8_up&&Lie_01_V==0)
		{    
		   delay_ms(jpys);
		   key8_up=0;
		   if(Lie_01_V==0)
		   {
		       return 8;
				
		   }
		}else if(Lie_01_V==1)key8_up=1;
		 
		if(key9_up&&Lie_02_V==0)
		{    
		   delay_ms(jpys);
		   key9_up=0;
		   if(Lie_02_V==0)
		   {
		       return 9;
				
		   }
		}else if(Lie_02_V==1)key9_up=1;
		 
		if(keyC_up&&Lie_03_V==0)
		{    
		   delay_ms(jpys);
		   keyC_up=0;
		   if(Lie_03_V==0)
		   {
		       return 12; 
				
		   }
		}else if(Lie_03_V==1)keyC_up=1;
 
	//第四行
	Hang_00_H;
	Hang_01_H;
	Hang_02_H;
	Hang_03_L;//把第四行置低
		if(keyX_up&&Lie_00_V==0)//如果第一列是低电平
		{    
		   delay_ms(jpys);
		   keyX_up=0;
		   if(Lie_00_V==0)//说明有键被按下，如果没有直接退出if语句
		   {
		       return 14;
			
		   }
		}else if(Lie_00_V==1)keyX_up=1;
		 
		if(key0_up&&Lie_01_V==0)
		{    
		   delay_ms(10);
		   key0_up=0;
		   if(Lie_01_V==0)
		   {
		       return 16;
			
		   }
		}else if(Lie_01_V==1)key0_up=1;
		 
		if(keyJ_up&&Lie_02_V==0)//如果第三列是低电平
		{    
		   delay_ms(jpys);
		   keyJ_up=0;
		   if(Lie_02_V==0)//说明有键被按下，如果没有直接退出if语句
		   {
		       return 15;
				
		   }
		}else if(Lie_02_V==1)keyJ_up=1;
		 
		if(keyD_up&&Lie_03_V==0)
		{    
		   delay_ms(jpys);
		   keyD_up=0;
		   if(Lie_03_V==0)
		   {
		       return 13;
				
		   }
		}else if(Lie_03_V==1)keyD_up=1;
		
		return 20;
}






