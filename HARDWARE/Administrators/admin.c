#include "admin.h"
#include "lcd.h"
#include "text.h"
#include "touch.h"
#include "delay.h"
#include "rtc.h"
#include "key.h"
#include "stmflash.h"
#include "usart.h"
#include "fattester.h"	
#include "led.h"

void show_duty_student(void);

//设置上下班签到时间
//设置系统时间

u8 *p;
u8 *q;
struct duty_student
{
	u8 Monday[20];
	u8 Tuesday[20];
	u8 Wednesday[20];
	u8 Thursday[20];
	u8 Friday[20];
	u8 Saturday[20];
}stu1;

FIL fil;
FRESULT res;
UINT bww;
u8 buffer[6553];

u8 abc_1[4]={'1','2','3','4'};
u8 time_save[7]={' ',' ','-',' ',' ',' ',' '};

u8 flag6=0;  //缺勤人数
//u8 depart_flag;

//#define FLASH_SAVE_ADDR 0X08070000
//#define SIZE sizeof(abc_1)

#define FLASH_SAVE_ADDR_2 0x08000800
#define SIZE_2 sizeof(abc_1)
	
u8 hanshu_flag;	
u8 set_hour,set_min;
u8 return_time_flag=1;

u8** kbd_tbl_2;
const  u8* kbd_menu_2[15]={"delete"," : ","input","1","2","3","4","5","6","7","8","9"," ","0"," "};//按键表

int clock_set[4];
u8 TIME_storage[4]={0};

void zhuanhua(u8 flag)
{
	u8 int_to_char[8]={'0','0','0','0','0','0','0','0'};
	u8 i,u=0;
	if(flag==1)
	{
		for(i=0;i<4;i++)
		{
			int_to_char[u]=clock_set[i]/10+'0';
			u++;
			int_to_char[u]=clock_set[i]%10+'0';
			u++;
		}
		STMFLASH_Write(FLASH_SAVE_ADDR_2,(u16 *)int_to_char ,SIZE_2 );
	}
	else
	{	
		STMFLASH_Read(FLASH_SAVE_ADDR_2,(u16 *)int_to_char ,SIZE_2);
		for(i=0;i<4;i++)
		{
			clock_set[i]=((int_to_char[u]-'0')*10+(int_to_char[u+1]-'0'));
			u=u+2;
		}
	}
}


u8 RTC_Set_2()
{
	u16 t;
	u16 syear;
	u8 sday,hour,min,sec,smon;
	u32 seccount=0;
	syear=calendar.w_year ;
	smon=calendar.w_month ;
	sday=calendar .w_date ;
	hour=set_hour;
	min=set_min;
	sec=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	seccount+=(u32)(sday-1)*86400;//把前面日期的秒钟数相加 
	seccount+=(u32)hour*3600;//小时秒钟数
    seccount+=(u32)min*60;	 //分钟秒钟数
	seccount+=sec;//最后的秒钟加上去

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟  
	PWR_BackupAccessCmd(ENABLE);	//使能RTC和后备寄存器访问 
	RTC_SetCounter(seccount);	//设置RTC计数器的值

	RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成  	
	return 0;	    
}



//加载按键界面（尺寸x,y为240*150）
//x,y:界面起始坐标（240*320分辨率的时候，x必须为0）
void keyboard_2(u16 x,u16 y,u8 **kbtbl)
{
	u16 i;
	
	POINT_COLOR=RED;
	kbd_tbl_2=kbtbl;
	LCD_Fill(x,y,x+240,y+150,WHITE);
	
	LCD_DrawLine(x,207,x,320);
	LCD_DrawLine(x+240,207,x+240,320);
	LCD_DrawLine(x+80,200,x+80,320);
	LCD_DrawLine(x+160,200,x+160,320);
	LCD_DrawLine(x+80,y+150,x+160,y+150);
	LCD_DrawLine(x,320,x+240,320);
	LCD_DrawRectangle(x,y+30,x+240,y+60);
	LCD_DrawRectangle(x,y+90,x+240,y+120);
	POINT_COLOR=BLUE;
	for(i=3;i<15;i++)
	{
		if(i==1)//按键表第2个‘:’不需要中间显示
			Show_Str(x+(i%3)*80+2,y+7+30*(i/3),80,30,(u8*)kbd_tbl_2[i],16,0);	
		
			
		if(i==13)
		{
			if(s_1==1)
				LCD_ShowString(20,300,200,16,16,"DEL");
			else
				Show_Str(20,300,200,16,"返回",16,1);
		}
			if(i==14)
			{
				Show_Str(180,300,200,16,"确认",16,1); 
			}
		if(i!=13||i!=14)
			Show_Str_Mid(x+(i%3)*80,y+7+30*(i/3),(u8*)kbd_tbl_2[i],16,80);
	} 
}

u8 admin_key_input()
{
  u8 x=0;
	
	while(!x)
	{
		TP_Scan(0);
		if(tp_dev.x>0&&tp_dev.x<80&&tp_dev.y>207&&tp_dev.y<236)
		{
			x=1;		
			GPIO_SetBits(GPIOB,GPIO_Pin_8);//输出0，关闭蜂鸣器输出
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);//输出0，关闭蜂鸣器输出
			tp_dev.y=0;
		}
		if(tp_dev.x>80&&tp_dev.x<160&&tp_dev.y>207&&tp_dev.y<236)
		{
			x=2;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>160&&tp_dev.x<240&&tp_dev.y>207&&tp_dev.y<236)
		{
			x=3;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>0&&tp_dev.x<80&&tp_dev.y>237&&tp_dev.y<266)
		{
			x=4;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>80&&tp_dev.x<160&&tp_dev.y>237&&tp_dev.y<266)
		{
			x=5;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>160&&tp_dev.x<240&&tp_dev.y>237&&tp_dev.y<266)
		{
			x=6;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>0&&tp_dev.x<80&&tp_dev.y>267&&tp_dev.y<296)
		{
			x=7;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>80&&tp_dev.x<160&&tp_dev.y>267&&tp_dev.y<296)
		{
			x=8;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);	
			tp_dev.y=0;
		}
		if(tp_dev.x>160&&tp_dev.x<240&&tp_dev.y>267&&tp_dev.y<296)
		{
			x=9;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>80&&tp_dev.x<160&&tp_dev.y>297&&tp_dev.y<320)
		{
			x=10;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		
		if(tp_dev.x>160&&tp_dev.x<240&&tp_dev.y>297&&tp_dev.y<320)  //确认
		{
			x=11;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		
		if(tp_dev.x>0&&tp_dev.x<80&&tp_dev.y>297&&tp_dev.y<320)  //DEL
		{
			x=12;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
	}
	return x;
}

u8 timeset_input()
{
	u8 x,flag=0,Time_flag=0;
	u8 suc_flag;
//	LCD_Clear(WHITE); 
//	LCD_ShowString(10,20,200,16,16,"Time SET:");	
	LCD_ShowChar(30+20*2,60,':',16,16);	
	keyboard_2(0,170,(u8**)kbd_menu_2);//加载虚拟键盘
	
	while(flag==0)
	{
		x=admin_key_input();
		if(x<=10)
		{	
			if(x==10) x=0;		
			TIME_storage[Time_flag]=x;
			if(Time_flag>=2)
				LCD_ShowNum(30+20*(Time_flag+1),60,TIME_storage[Time_flag] ,2,16);
			else
				LCD_ShowNum(30+20*Time_flag,60,TIME_storage[Time_flag] ,2,16);
			Time_flag++;
			if(Time_flag>4)
				Time_flag=0;
		}
		if(x==12)  //返回
		{
			suc_flag=0;
			flag=1;
		}
		if(x==11)  //确定
		{
			set_hour=(u8)(TIME_storage[0]*10+TIME_storage[1]);
			set_min =(u8)(TIME_storage[2]*10+TIME_storage[3]);
			delay_ms (500);
			suc_flag=1;
			flag=1;
		}
	}
	LCD_Clear (WHITE );
	return suc_flag;
}

void Local_time_set()
{
	LCD_Clear(WHITE); 
	Show_Str(40,20,200,16,"请设置本地时间:",16,0);	
	if(timeset_input()==1)	
		RTC_Set_2();
}	


u8 password_input()
{
	u8 password[4]={0};
	u8 i=0,a,b=0,Flag=0;
	LCD_Clear(WHITE);
	STMFLASH_Read(FLASH_SAVE_ADDR_2,(u16 *)abc_1,SIZE_2);
	Show_Str(40,20,200,16,"请输入密码:",16,0); 
	keyboard_2(0,170,(u8**)kbd_menu_2);//显示键盘 
	while(i!=1)
	{
			a=admin_key_input();
			if(a<=10)
			{	
				if(a==10) a=0;
				LCD_ShowxNum(80+15*b,40,a,1,16,0);
				password[b]=a+'0';
				b++;
			}
			if(b==4)
			{

				if(password[0]==abc_1[0]&&password[1]==abc_1[1]&&password[2]==abc_1[2]&&password[3]==abc_1[3])
				{
					Show_Str(40,70,200,16,"密码正确",16,0); 
					delay_ms(1000);
					delay_ms(1000);
					delay_ms(1000);
					i=1;
					Flag =1;
				}
				else
				{
					Show_Str(40,70,200,16,"密码错误",16,0); 
					delay_ms (1000);
					LCD_ShowChar(80+15*0,40,' ',16,0);
					LCD_ShowChar(80+15*1,40,' ',16,0);
					LCD_ShowChar(80+15*2,40,' ',16,0);
					LCD_ShowChar(80+15*3,40,' ',16,0);
					LCD_Fill(40,70,120,100,WHITE );	
					i=0;
					b=0;
					Flag =0;
				}
			}
			if(a==11)
			{
				b--;
				LCD_ShowChar(80+15*b,40,' ',16,0);
			}
			if(a==12)  //返回
			{
				i=1;
				Flag =0;
			}
			
	}
	LCD_Clear(WHITE);
	return Flag ;
}

void worktime_set()
{
	LCD_Clear(WHITE); 
	Show_Str(40,20,200,16,"请设置签到时间:",16,0);
	if(timeset_input()==1)	
	{
		clock_set[0]=set_hour;
		clock_set[1]=set_min;
		zhuanhua(1);
		zhuanhua(0);
	}
}

void finworktime_set()
{
	LCD_Clear(WHITE); 
	Show_Str(40,20,200,16,"请设置签退时间:",16,0);
	if(timeset_input()==1)	
	{
		clock_set[2]=set_hour;
		clock_set[3]=set_min;
		zhuanhua(1);
		zhuanhua(0);
	}
}

//void password_set()
//{
//	u8 password_set;
//	u8 b=0;
//	u8 flag=1;
//	LCD_Clear(WHITE); 
//	Show_Str(40,20,200,16,"请设置管理员密码:",16,0);
//	
//	keyboard_2(0,170,(u8**)kbd_menu_2);//加载虚拟键盘
//	while(flag)
//	{
//		password_set=admin_key_input();
//		if(password_set<=10)
//		{	
//			if(b<4)
//			{	
//				if(password_set==10) password_set=0;
//				LCD_ShowxNum(80+15*b,40,password_set,1,16,0);
//				abc_1[b]=password_set+'0';
//				b++;
//			}
//		}
//		
//		if(password_set==12)
//		{
//			if(b!=0)
//				b--;
//			LCD_ShowChar(80+15*b,40,' ',16,0);

//		}
//		
//		if(password_set==11)
//		{
//			Show_Str(60,80,200,16,"密码设置成功",16,0);
//			delay_ms(1000);
//			STMFLASH_Write(FLASH_SAVE_ADDR,(u16 *)abc_1,SIZE );
//			flag=0;
//		}
//	}
//}


void File_xianshi()
{
	u8 key,Flag=1;
	f_open (&fil,"0:/message.txt", FA_READ); //打开可读文件
	f_read (&fil, buffer,fil.fsize ,&bww);	//读出内容
	Show_Str(0,0+45*calendar.w_date%7,240,320,buffer,16,0);
	f_close(&fil);  //关闭文件
	while(Flag)
	{
		key=KEY_Scan(0);
		if(key==KEY2_PRES ||key==KEY0_PRES ||key==KEY1_PRES )
		{
			Flag=0;
		}
	}
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );
	LCD_Clear(WHITE);
	return_time_flag=1;
}


void write_to_file()
{
	LED0=0;
	f_open (&fil,"0:/message.txt", FA_OPEN_ALWAYS|FA_WRITE);
	f_lseek (&fil,fil.fsize );
	f_write (&fil, time_save, 7, &bww); 
	f_lseek (&fil,fil.fsize );
	f_write (&fil, "今日到勤人数：", 13, &bww); 
	f_lseek (&fil,fil.fsize );
	f_write (&fil, cun , 10, &bww); 
	f_close(&fil);  //关闭文件
	LED0=1;
}

u8 choose_depart()
{
  u8 x=0;
	
	while(!x)
	{
		TP_Scan(0);
		if(tp_dev.y>60&&tp_dev.y<89)
		{
			depart_flag=x=1;	
			
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);//输出0，关闭蜂鸣器输出
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);//输出0，关闭蜂鸣器输出
			tp_dev.y=0;
		}
		if(tp_dev.y>90&&tp_dev.y<119)
		{
			depart_flag=x=2;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>120&&tp_dev.y<149)
		{
			depart_flag=x=3;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>150&&tp_dev.y<179)
		{
			depart_flag=x=4;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>180&&tp_dev.y<209)
		{
			depart_flag=x=5;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>210&&tp_dev.y<239)
		{
			depart_flag=x=6;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>240&&tp_dev.y<269)
		{
			depart_flag=x=7;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>270&&tp_dev.y<299)
		{
			depart_flag=x=8;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>160&&tp_dev.x<240&&tp_dev.y>297&&tp_dev.y<320)  //确认
		{
			x=11;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>0&&tp_dev.x<80&&tp_dev.y>297&&tp_dev.y<320)  //返回
		{
			x=12;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
	}
	return x;
}

u8 depart_choose()
{
	u8 a;
	u8 FLAG=1;
	LCD_Clear(WHITE);
	Show_Str(40,20,240,320,"请选择所在部门：",16,0);
	Show_Str(60,60,240,320,"科技部",16,0);
	Show_Str(60,90,240,320,"督察部",16,0);
	Show_Str(60,120,240,320,"宣传部",16,0);
	Show_Str(60,150,240,320,"办公室",16,0);
	Show_Str(60,180,240,320,"财务部",16,0);
	Show_Str(60,210,240,320,"策划部",16,0);
	Show_Str(60,240,240,320,"实践部",16,0);
	Show_Str(60,270,240,320,"理事部",16,0);
	Show_Str(20,300,240,320,"确认",16,1); 
	Show_Str(200,300,240,320,"返回",16,1);
	while(FLAG)
	{
		a=choose_depart();
		if(a==11) FLAG=0;
		if(a==12)	FLAG=0;
	}
	LCD_Clear (WHITE);
	if(a==12) return 1;
	else
		return 0;
	
}

u8 choose_data()
{
  u8 x=0;
	
	while(!x)
	{
		TP_Scan(0);
		if(tp_dev.y>60&&tp_dev.y<89)
		{
			data_flag=x=1;	
			
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);//输出0，关闭蜂鸣器输出
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);//输出0，关闭蜂鸣器输出
			tp_dev.y=0;
		}
		if(tp_dev.y>90&&tp_dev.y<119)
		{
			data_flag=x=2;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>120&&tp_dev.y<149)
		{
			data_flag=x=3;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>150&&tp_dev.y<179)
		{
			data_flag=x=4;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>180&&tp_dev.y<209)
		{
			data_flag=x=5;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.y>210&&tp_dev.y<239)
		{
			data_flag=x=6;
			LCD_Fill(40,60,58,290,WHITE);
			LCD_ShowString(40,30+30*x,16,16,16,"->");
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>160&&tp_dev.x<240&&tp_dev.y>297&&tp_dev.y<320)  //确认
		{
			x=11;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
		if(tp_dev.x>0&&tp_dev.x<80&&tp_dev.y>297&&tp_dev.y<320)  //返回
		{
			x=12;
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			delay_ms(300);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			tp_dev.y=0;
		}
	}
	return x;
}

u8 data_choose()
{
	u8 a;
	u8 FLAG=1;
	LCD_Clear(WHITE);
	Show_Str(40,20,240,320,"请选择值班星期：",16,0);
	Show_Str(60,60,240,320,"星期一",16,0);
	Show_Str(60,90,240,320,"星期二",16,0);
	Show_Str(60,120,240,320,"星期三",16,0);
	Show_Str(60,150,240,320,"星期四",16,0);
	Show_Str(60,180,240,320,"星期五",16,0);
	Show_Str(60,210,240,320,"星期六",16,0);
	Show_Str(20,300,240,320,"确认",16,1); 
	Show_Str(200,300,240,320,"返回",16,1);
	while(FLAG)
	{
		Show_Str(40,20,240,320,"请选择值班星期：",16,0);
		Show_Str(60,60,240,320,"星期一",16,0);
		Show_Str(60,90,240,320,"星期二",16,0);
		Show_Str(60,120,240,320,"星期三",16,0);
		Show_Str(60,150,240,320,"星期四",16,0);
		Show_Str(60,180,240,320,"星期五",16,0);
		Show_Str(60,210,240,320,"星期六",16,0);
		Show_Str(20,300,240,320,"确认",16,1); 
		Show_Str(200,300,240,320,"返回",16,1);
		a=choose_data();
		if(a==11) FLAG=0;
		if(a==12)	
		{
			show_duty_student();
		}
	}
	LCD_Clear (WHITE);
	if(a==12) return 1;
	else
		return 0;
	
}

void show_duty_student()
{
	s8 i=0;
	u8 data;
	u8 b=0;
	LCD_Clear(WHITE);
//	stu1.Monday[1] =79;
//	stu1.Monday[0] =9;
//	stu1.Tuesday [0] =19;
	keyboard_2(0,170,(u8**)kbd_menu_2);//加载虚拟键盘
	switch(data_flag )
	{
		case 1:Show_Str(40,20,240,320,"星期一",16,0);p=stu1.Monday; break;
		case 2:Show_Str(40,20,240,320,"星期二",16,0);p=stu1.Tuesday;break;
		case 3:Show_Str(40,20,240,320,"星期三",16,0);p=stu1.Wednesday;break;
		case 4:Show_Str(40,20,240,320,"星期四",16,0);p=stu1.Thursday;break;
		case 5:Show_Str(40,20,240,320,"星期五",16,0);p=stu1.Friday;break;
		case 6:Show_Str(40,20,240,320,"星期六",16,0);p=stu1.Saturday;break;
	}
	while(data!=12)
	{
		data=admin_key_input();
		
		if(data<=10)
		{
			LCD_ShowxNum(80+15*b,40,data,1,16,0);
			if(data==10)
				data=0;
			b++;
			if(b==1)
			{
				p[i]=data;
			}
			if(b==2)
			{
				p[i]=p[i]*10+data;
				b=0;
				data=11;
			}
		}
		if(data==11)  //确认
		{
			delay_ms(1000);
			LCD_Fill (80,40,220,60,WHITE);
			b=0;
			i++;
		}
		if(data==12)
		{
			i=0;
			while(p[i])
			{
				LCD_ShowNum(40+20*i,60,p[i],2,16);
				i++;
			}
			delay_ms(3000);
			LCD_Clear (WHITE);
		}
			
	}
}




void compare()
{
	u8 i,j;
//	u8 flag_1=0;  //缺勤人数
	u8 flag7=0;
	u8 jilv_1[20];   //装有缺勤人编号的数组
	u8 jilv_2[20]; 
	
	switch(calendar.week)
	{		
		case 1:
			q=stu1.Monday;break;			
		case 2:
			q=stu1.Tuesday;break;
		case 3:
			q=stu1.Wednesday;break;
		case 4:
			q=stu1.Thursday;break;
		case 5:
			q=stu1.Friday;break;
		case 6:
			q=stu1.Saturday;break;
	}
	for(i=0;i<30;i++)
	{
		for(j=0;j<30;j++)
		{
			if(q[i]==number_1[j]);
			else 
			{
				jilv_1[flag6]=q[i];    
				flag6++;
			}
		}
		j=0;
	}
	for(i=0;i<30;i++)
	{
		for(j=0;j<30;j++)
		{
			if(q[i]==number_2[j]);
			else 
			{
				jilv_2[flag7]=q[i];    
				flag7++;
			}
		}
		j=0;
	}
}



