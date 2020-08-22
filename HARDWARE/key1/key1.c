///************************************************************
//���泯�Ϻ�����Ϊ�У�������Ϊ�� 
//A��B ��C ��D  �ֱ𷵻� 10 11 12 13
//*Ϊ 14
//#Ϊ 15
//0Ϊ 16
//�ް������·���0
//*************************************************************/

#include "key1.h"
#include "delay.h"
#include "sys.h" 

u8 flag=0,x;

//����������ų�ʼ��
void Key_init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG,ENABLE);//ʹ��PORTB,PORTD��PORTGʱ��

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_9;  //�������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOG,&GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_4|GPIO_Pin_2; //��������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOG,&GPIO_InitStructure);	
}

//mode:0,��֧��������;1,֧��������;
u8 KEY_scan(u8 mode)
{
//	int KeyVal=0;
	static u8 key0_up=1;//�������ɿ���־
	static u8 key1_up=1;//�������ɿ���־
	static u8 key2_up=1;//�������ɿ���־
	static u8 key3_up=1;//�������ɿ���־
	static u8 key4_up=1;//�������ɿ���־
	static u8 key5_up=1;//�������ɿ���־
	static u8 key6_up=1;//�������ɿ���־
	static u8 key7_up=1;//�������ɿ���־
	static u8 key8_up=1;//�������ɿ���־
	static u8 key9_up=1;//�������ɿ���־
	static u8 keyA_up=1;//�������ɿ���־
	static u8 keyB_up=1;//�������ɿ���־
	static u8 keyC_up=1;//�������ɿ���־
	static u8 keyD_up=1;//�������ɿ���־
	static u8 keyX_up=1;//�������ɿ���־
	static u8 keyJ_up=1;//�������ɿ���־
	
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
	
    //��һ��
	Hang_00_L;//�ѵ�һ������͵�ƽ
	Hang_01_H;
	Hang_02_H;
	Hang_03_H;
		if(key1_up&&Lie_00_V==0)
		{    
		   delay_ms(jpys); //��ʱ20�룬�������
			
		   key1_up=0;
		   if(Lie_00_V==0) //�����һ���ǵ͵�ƽ��˵���м������£����û��ֱ���˳�if���
		   {
			  return 1;
				
		   }
		}else if(Lie_00_V==1)key1_up=1;
	 
		if(key2_up&&Lie_01_V==0)//����ڶ����ǵ͵�ƽ��
		{    
		   delay_ms(jpys);//��ʱ20�룬�������
		   key2_up=0;
		   if(Lie_01_V==0)//����ڶ����ǵ͵�ƽ��˵���м������£����û��ֱ���˳�if���
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
	 
		if(keyA_up&&Lie_03_V==0)//����������ǵ͵�ƽ
		{    
		   delay_ms(jpys);
		   keyA_up=0;
		   if(Lie_03_V==0)//����������ǵ͵�ƽ��˵���м������£����û��ֱ���˳�if���
		   {
			  return 10;
			
		   }
		}else if(Lie_03_V==1)keyA_up=1;
 
	//�ڶ���
	Hang_00_H;
	Hang_01_L;//�ѵڶ�������
	Hang_02_H;
	Hang_03_H;
		if(key4_up&&Lie_00_V==0)//�����һ���ǵ͵�ƽ
		{    
		   delay_ms(jpys);
		   key4_up=0;
		   if(Lie_00_V==0)//˵���м������£����û��ֱ���˳�if���
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
 
	//������
	Hang_00_H;
	Hang_01_H;
	Hang_02_L;//�ѵ������õ�
	Hang_03_H;
		if(key7_up&&Lie_00_V==0) //�����һ���ǵ͵�ƽ
		{    
		   delay_ms(jpys);//��ʱ20��
		   key7_up=0;
		   if(Lie_00_V==0)//˵���м������£����û��ֱ���˳�if���
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
 
	//������
	Hang_00_H;
	Hang_01_H;
	Hang_02_H;
	Hang_03_L;//�ѵ������õ�
		if(keyX_up&&Lie_00_V==0)//�����һ���ǵ͵�ƽ
		{    
		   delay_ms(jpys);
		   keyX_up=0;
		   if(Lie_00_V==0)//˵���м������£����û��ֱ���˳�if���
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
		 
		if(keyJ_up&&Lie_02_V==0)//����������ǵ͵�ƽ
		{    
		   delay_ms(jpys);
		   keyJ_up=0;
		   if(Lie_02_V==0)//˵���м������£����û��ֱ���˳�if���
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






