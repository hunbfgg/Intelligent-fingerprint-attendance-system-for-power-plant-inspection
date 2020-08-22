#include "common.h"
#include <sql.h>

//ATK-ESP8266 AP+STA模式测试
//用于测试TCP/UDP连接
//返回值:0,正常
//    其他,错误代码

//u8 ducha;
//u8 xuanchuan;
//u8 keji;
//u8 caiwu;
//u8 cehua;
//u8 bangongshi;
//u8 shijian;
//u8 lishi;

u8 atk_8266_apsta_test(void)
{
	u8 time_flag=0;
	u8 netpro;
	u8 key=0;
	u8 timex=0; 
	u8 ipbuf[16]; 	//IP缓存
	u8 *p;
	u16 t=999;		//加速第一次获取链接状态
	u8 res=0,a=0;
	u16 rlen=0;
	u8 constate=0;	//连接状态
	LCD_ShowString(30,240,200,16,16,"    -  -  ");	   
	LCD_ShowString(50,200,200,16,24," :  ");	
	p=mymalloc(SRAMIN,100);							//申请32字节内存
	atk_8266_send_cmd("AT+CWMODE=3","OK",50);		//设置WIFI AP+STA模式
	//设置模块AP模式的WIFI网络名称/加密方式/密码，这几个参数看自己喜好设置
	sprintf((char*)p,"AT+CWSAP=\"%s\",\"%s\",1,4",wifiap_ssid,wifiap_password);//设置无线参数:ssid,密码
	atk_8266_send_cmd(p,"OK",1000);					//设置AP模式参数
	//设置连接到的WIFI网络名称/加密方式/密码,这几个参数需要根据您自己的路由器设置进行修改!! 
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//设置无线参数:ssid,密码
	atk_8266_send_cmd(p,"WIFI GOT IP",1000);						//连接目标路由器，并获得IP
	while(atk_8266_send_cmd("AT+CIFSR","STAIP",20));   //检测是否获得STA IP
	while(atk_8266_send_cmd("AT+CIFSR","APIP",20));   //检测是否获得AP IP
	atk_8266_send_cmd("AT+CIPMUX=1","OK",50);   //0：单连接，1：多连接
	delay_ms(500);
	sprintf((char*)p,"AT+CIPSERVER=1,%s",(u8*)portnum);
	atk_8266_send_cmd(p,"OK",50);     //开启Server模式，端口号为8086
	delay_ms(500);
	atk_8266_send_cmd("AT+CIPSTO=1200","OK",50);     //设置服务器超时时间
	
PRESTA:
	netpro=atk_8266_netpro_sel(50,30,(u8*)ATK_ESP8266_CWMODE_TBL[0]);	//AP+STA模式网络模式选择
	if(netpro&0X02)   //STA UDP
	{
			if(atk_8266_ip_set("WIFI-STA远端UDP IP设置","UDP模式",(u8*)portnum,ipbuf))goto PRESTA;	//IP输入
			sprintf((char*)p,"AT+CIPSTART=0,\"UDP\",\"%s\",%s",ipbuf,(u8*)portnum);    //配置目标UDP服务器,及ID号，STA模式下为0
			atk_8266_send_cmd(p,"OK",200);
			netpro=atk_8266_mode_cofig(netpro);     //AP模式网络模式配置			
	}
	else     //TCP
	{
		if(netpro&0X01)     //STA TCP Client  
		{
			if(atk_8266_ip_set("WIFI-STA 远端IPS sitting",(u8*)ATK_ESP8266_WORKMODE_TBL[netpro],(u8*)portnum,ipbuf))goto PRESTA;	//IP输入
			sprintf((char*)p,"AT+CIPSTART=0,\"TCP\",\"%s\",%s",ipbuf,(u8*)portnum);    //配置目标TCP服务器,及ID号，STA模式下为0
			while(atk_8266_send_cmd(p,"OK",200))
			{
				key=KEY_Scan(0);
				if(key==WKUP_PRES)goto PRESTA;
			}	
			netpro=atk_8266_mode_cofig(netpro);     //AP模式网络模式配置	
		}
		else netpro=atk_8266_mode_cofig(netpro);     //TCP SERVER不用配置
	}
	
//	xianshi();
	LCD_ShowString(30,240,200,16,16,"    -  -  ");	   
	LCD_ShowString(50,200,200,16,24," :  ");
	atk_8266_get_ip(15,65);//STA+AP模式,获取 IP,并显示	
	USART3_RX_STA=0;
	while(1)
	{
		if(a==0)
		{
			Show_Str(30,100,200,16,"SEND MESSAGEING ....",16,1); 
		
			a=1;
		}
		delay_ms(300);
		if(key==WKUP_PRES)			//WK_UP 退出测试		 
		{ 
			res=0;	
			break;												 
		}
		else if(key==KEY0_PRES)	//KEY0 向ID0发送数据 
		{
			time_flag++;
  		sprintf((char*)p,"people's num:%d ducha:%d ; cehua:%d ; caiwu:%d ; xuanchuan:%d ; keji:%d ; bangongshi:%d ; shijian:%d \r\n",
				shu_flag,ducha,cehua,caiwu,xuanchuan,keji,bangongshi,shijian);//测试数据
			atk_8266_send_cmd("AT+CIPSEND=0,110","OK",200);  //发送指定长度的数据
			delay_ms(200);
			atk_8266_send_data(p,"OK",100);  //发送指定长度的数据
			timex=100;	
		}
	 if(timex)timex--;
 	 if(timex==1)LCD_Fill(30+54,125,239,122,WHITE);
	 t++;
	 delay_ms(10);
	 if(USART3_RX_STA&0X8000)		//接收到一次数据了
	 { 
			rlen=USART3_RX_STA&0X7FFF;	//得到本次接收到的数据长度
			USART3_RX_BUF[rlen]=0;		//添加结束符 
			sprintf((char*)p,"receive%dbytes,is",rlen);//接收到的字节数 
			USART3_RX_STA=0;
			if(constate!='+')t=1000;		//状态为还未连接,立即更新连接状态
			else t=0;                   //状态为已经连接了,10秒后再检查
	}  
	if(t==1000)//连续10秒钟没有收到任何数据,检查连接是不是还存在.
	{
		constate=atk_8266_consta_check();//得到连接状态
		if(constate=='+')
		{	
			Show_Str(100,120,200,12,"Connection success",16,0);
			if(time_flag<=3)
				key=KEY0_PRES;
			else
				key=KEY_Scan(0);
		}			//连接状态
		else 
		{
			Show_Str(100,120,200,12,"Connection failure",16,0);
			key=KEY_Scan(0);
		}			
		t=0;
	}
	atk_8266_at_response(1);
}
	myfree(SRAMIN,p);		//释放内存 
	return res;		
} 


























