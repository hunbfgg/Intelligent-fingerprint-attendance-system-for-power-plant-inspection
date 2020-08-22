#include "common.h"
#include <sql.h>

//ATK-ESP8266 AP+STAģʽ����
//���ڲ���TCP/UDP����
//����ֵ:0,����
//    ����,�������

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
	u8 ipbuf[16]; 	//IP����
	u8 *p;
	u16 t=999;		//���ٵ�һ�λ�ȡ����״̬
	u8 res=0,a=0;
	u16 rlen=0;
	u8 constate=0;	//����״̬
	LCD_ShowString(30,240,200,16,16,"    -  -  ");	   
	LCD_ShowString(50,200,200,16,24," :  ");	
	p=mymalloc(SRAMIN,100);							//����32�ֽ��ڴ�
	atk_8266_send_cmd("AT+CWMODE=3","OK",50);		//����WIFI AP+STAģʽ
	//����ģ��APģʽ��WIFI��������/���ܷ�ʽ/���룬�⼸���������Լ�ϲ������
	sprintf((char*)p,"AT+CWSAP=\"%s\",\"%s\",1,4",wifiap_ssid,wifiap_password);//�������߲���:ssid,����
	atk_8266_send_cmd(p,"OK",1000);					//����APģʽ����
	//�������ӵ���WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!! 
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//�������߲���:ssid,����
	atk_8266_send_cmd(p,"WIFI GOT IP",1000);						//����Ŀ��·�����������IP
	while(atk_8266_send_cmd("AT+CIFSR","STAIP",20));   //����Ƿ���STA IP
	while(atk_8266_send_cmd("AT+CIFSR","APIP",20));   //����Ƿ���AP IP
	atk_8266_send_cmd("AT+CIPMUX=1","OK",50);   //0�������ӣ�1��������
	delay_ms(500);
	sprintf((char*)p,"AT+CIPSERVER=1,%s",(u8*)portnum);
	atk_8266_send_cmd(p,"OK",50);     //����Serverģʽ���˿ں�Ϊ8086
	delay_ms(500);
	atk_8266_send_cmd("AT+CIPSTO=1200","OK",50);     //���÷�������ʱʱ��
	
PRESTA:
	netpro=atk_8266_netpro_sel(50,30,(u8*)ATK_ESP8266_CWMODE_TBL[0]);	//AP+STAģʽ����ģʽѡ��
	if(netpro&0X02)   //STA UDP
	{
			if(atk_8266_ip_set("WIFI-STAԶ��UDP IP����","UDPģʽ",(u8*)portnum,ipbuf))goto PRESTA;	//IP����
			sprintf((char*)p,"AT+CIPSTART=0,\"UDP\",\"%s\",%s",ipbuf,(u8*)portnum);    //����Ŀ��UDP������,��ID�ţ�STAģʽ��Ϊ0
			atk_8266_send_cmd(p,"OK",200);
			netpro=atk_8266_mode_cofig(netpro);     //APģʽ����ģʽ����			
	}
	else     //TCP
	{
		if(netpro&0X01)     //STA TCP Client  
		{
			if(atk_8266_ip_set("WIFI-STA Զ��IPS sitting",(u8*)ATK_ESP8266_WORKMODE_TBL[netpro],(u8*)portnum,ipbuf))goto PRESTA;	//IP����
			sprintf((char*)p,"AT+CIPSTART=0,\"TCP\",\"%s\",%s",ipbuf,(u8*)portnum);    //����Ŀ��TCP������,��ID�ţ�STAģʽ��Ϊ0
			while(atk_8266_send_cmd(p,"OK",200))
			{
				key=KEY_Scan(0);
				if(key==WKUP_PRES)goto PRESTA;
			}	
			netpro=atk_8266_mode_cofig(netpro);     //APģʽ����ģʽ����	
		}
		else netpro=atk_8266_mode_cofig(netpro);     //TCP SERVER��������
	}
	
//	xianshi();
	LCD_ShowString(30,240,200,16,16,"    -  -  ");	   
	LCD_ShowString(50,200,200,16,24," :  ");
	atk_8266_get_ip(15,65);//STA+APģʽ,��ȡ IP,����ʾ	
	USART3_RX_STA=0;
	while(1)
	{
		if(a==0)
		{
			Show_Str(30,100,200,16,"SEND MESSAGEING ....",16,1); 
		
			a=1;
		}
		delay_ms(300);
		if(key==WKUP_PRES)			//WK_UP �˳�����		 
		{ 
			res=0;	
			break;												 
		}
		else if(key==KEY0_PRES)	//KEY0 ��ID0�������� 
		{
			time_flag++;
  		sprintf((char*)p,"people's num:%d ducha:%d ; cehua:%d ; caiwu:%d ; xuanchuan:%d ; keji:%d ; bangongshi:%d ; shijian:%d \r\n",
				shu_flag,ducha,cehua,caiwu,xuanchuan,keji,bangongshi,shijian);//��������
			atk_8266_send_cmd("AT+CIPSEND=0,110","OK",200);  //����ָ�����ȵ�����
			delay_ms(200);
			atk_8266_send_data(p,"OK",100);  //����ָ�����ȵ�����
			timex=100;	
		}
	 if(timex)timex--;
 	 if(timex==1)LCD_Fill(30+54,125,239,122,WHITE);
	 t++;
	 delay_ms(10);
	 if(USART3_RX_STA&0X8000)		//���յ�һ��������
	 { 
			rlen=USART3_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
			USART3_RX_BUF[rlen]=0;		//��ӽ����� 
			sprintf((char*)p,"receive%dbytes,is",rlen);//���յ����ֽ��� 
			USART3_RX_STA=0;
			if(constate!='+')t=1000;		//״̬Ϊ��δ����,������������״̬
			else t=0;                   //״̬Ϊ�Ѿ�������,10����ټ��
	}  
	if(t==1000)//����10����û���յ��κ�����,��������ǲ��ǻ�����.
	{
		constate=atk_8266_consta_check();//�õ�����״̬
		if(constate=='+')
		{	
			Show_Str(100,120,200,12,"Connection success",16,0);
			if(time_flag<=3)
				key=KEY0_PRES;
			else
				key=KEY_Scan(0);
		}			//����״̬
		else 
		{
			Show_Str(100,120,200,12,"Connection failure",16,0);
			key=KEY_Scan(0);
		}			
		t=0;
	}
	atk_8266_at_response(1);
}
	myfree(SRAMIN,p);		//�ͷ��ڴ� 
	return res;		
} 


























