#include "mqtt.h"
#include "common.h"
#include "text.h"
#include "MQTTPacket.h"
#include "transport.h"
#include "cjson.h"
#include "timer.h"

char receive_data[100];

char *topic="/sys/a1ywqH8kuPn/temper/thing/event/property/post";//订阅主题

char *cjson="{\"method\":\"thing.service.property.set\",\"id\":\"1338379119\",\"params\":{\"led\":0},\"version\":\"1.0.0\"}";
u16 a=0;
u8 time;
u8 i;
unsigned char buf[200];

short temperature=39; 


//连接目标MQTT服务器
void mqtt_connect()
{
    int32_t len;
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;//配置部分可变头部的值
    
    int buflen = sizeof(buf);
		memset(buf,0,buflen);
    data.clientID.cstring = "temper|securemode=3,signmethod=hmacsha1|";//客户端标识，用于区分每个客户端xxx为自定义，后面为固定格式
    data.keepAliveInterval = 120;//保活计时器，定义了服务器收到客户端消息的最大时间间隔
    data.cleansession = 1;//该标志置1服务器必须丢弃之前保持的客户端的信息，将该连接视为“不存在”
    data.username.cstring = "temper&a1ywqH8kuPn";//用户名 DeviceName&ProductKey
    data.password.cstring = "52e31a47f6321c7dec0804144853c6813f4c0678";//密码，工具生成
    len = MQTTSerialize_connect(buf, buflen, &data); /*1 构造连接报文*/

    transport_sendPacketBuffer(USART3,buf,len);
		Show_Str(40,55,200,16,"MQTT连接成功",16,0);
}


/*----------------------------------------------------------*/
/*函数名：SUBSCRIBE订阅topic报文                            */
/*参  数：temp_buff：保存报文数据的缓冲区                                                */
/*参  数：QoS：订阅等级                                     */
/*参  数：topic_name：订阅topic报文名称                     */
/*返回值：报文长度                                                                                                                */
/*----------------------------------------------------------*/
void MQTT_Subscribe(unsigned char *temp_buff, char *topic_name, int QoS)
{
	u8 Fixed_len = 2;                                 //SUBSCRIBE报文中，固定报头长度=2
	u8 Variable_len = 2;                              //SUBSCRIBE报文中，可变报头长度=2
	u8 Payload_len = 2 + strlen(topic_name) + 1;   //计算有效负荷长度 = 2字节(topic_name长度)+ topic_name字符串的长度 + 1字节服务等级

	temp_buff[0]=0x82;                                          //第1个字节 ：固定0x82
	temp_buff[1]=Variable_len + Payload_len;                    //第2个字节 ：可变报头+有效负荷的长度
	temp_buff[2]=0x00;                                          //第3个字节 ：报文标识符高字节，固定使用0x00
	temp_buff[3]=0x01;		                                    //第4个字节 ：报文标识符低字节，固定使用0x01
	temp_buff[4]=strlen(topic_name)/256;                     //第5个字节 ：topic_name长度高字节
	temp_buff[5]=strlen(topic_name)%256;		                //第6个字节 ：topic_name长度低字节
	memcpy(&temp_buff[6],topic_name,strlen(topic_name));  //第7个字节开始 ：复制过来topic_name字串
	temp_buff[6+strlen(topic_name)]=QoS;                     //最后1个字节：订阅等级
	
	transport_sendPacketBuffer(USART3,buf,Fixed_len + Variable_len + Payload_len);
	Show_Str(40,55,200,16,"订阅主题成功",16,0);
}


//发布消息
int mqtt_publish(char *pTopic,char *pMessage,int QoS)
{
    int32_t len;
    MQTTString topicString = MQTTString_initializer;
    int msglen = strlen(pMessage);//计算发布消息的长度
    int buflen = sizeof(buf);

    memset(buf,0,buflen);
    topicString.cstring = pTopic;//"设备topic列表中的第一条";
    len = MQTTSerialize_publish(buf, buflen, 0, QoS, 0, 0, topicString, (unsigned char*)pMessage, msglen); /*构造发布消息的报文*/

    transport_sendPacketBuffer(USART3,buf,len);//发送消息
		free(buf);
		Show_Str(40,55,200,16,"发布消息成功",16,0);
    return 0;
}

/*----------------------------------------------------------*/
/*函数名：PING报文，心跳包                                  */
/*参  数：无                                               */
/*返回值：无                                                */
/*----------------------------------------------------------*/
void MQTT_PingREQ()
{
	while((USART3->SR&0x0080)==0) ;
	USART3->DR=0xC0;
	while((USART3->SR&0x0080)==0) ;
	USART3->DR=0x00;
}

void cjson_creat()
{
	char* lpJsonStr;
	cJSON * pJsonChild;
	cJSON * pJsonRoot;
	
	pJsonRoot = cJSON_CreateObject();
	pJsonChild = cJSON_CreateObject();
	
	cJSON_AddStringToObject(pJsonRoot, "method", "thing.event.property.post");
	cJSON_AddStringToObject(pJsonRoot, "id", "temper");
	cJSON_AddItemToObject(pJsonRoot, "params", pJsonChild);
	cJSON_AddNumberToObject(pJsonRoot, "version",1.4);
	
	cJSON_AddNumberToObject(pJsonChild, "temp",temperature/10);
	cJSON_AddNumberToObject(pJsonChild, "led",1);
	
	lpJsonStr = cJSON_Print(pJsonRoot);
	
	mqtt_publish(topic,lpJsonStr,1);
	
	cJSON_Delete (pJsonRoot);
	
	free (lpJsonStr);
	a++;
	
	
}

//void cjson_crt()
//{
//	cJSON *root;
//	cJSON *params;
//	char * str;
//	
//	root =cJSON_Parse (cjson);
//	if(root)
//	{
//		str=cJSON_GetObjectItem (root,"method")->receive_data;
//		str=cJcJSON_GetObjectItem(root,"id")->receive_data;
//	}
//}


void mqtt_set()
{
	while(atk_8266_send_cmd("ATE0","OK",20));//关闭回显   u3_printf("%s\r\n",cmd);	//发送命令
	
	while(atk_8266_send_cmd("AT+CWMODE_CUR=1","OK",20));     //设为客户端模式
	
	while(atk_8266_send_cmd("AT+CWJAP_CUR=\"CMCC-biR5\",\"ywrg3nbu\"","OK",20));  //连接WIFI
	Show_Str(40,55,200,16,"WIFI连接成功",16,0);
	while(atk_8266_send_cmd("AT+CIPSTART=\"TCP\",\"a18qhFfWs3H.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883","OK",20));  //TCP连接
	
	delay_ms (1000);
	
	while(atk_8266_send_cmd("AT+CIPMODE=1","OK",20));  //打开透传模式
	
	delay_ms (1000);

	while(atk_8266_send_cmd("AT+CIPSEND",">",20));  //开始传输数据
	Show_Str(40,55,200,16,"开始传输数据",16,0);
	delay_ms (1000);
	mqtt_connect();
	delay_ms (1000);
	
	MQTT_Subscribe(buf,topic,1);  //订阅主题


}


void mqtt_sendmassage()
{
	cjson_creat();
//	while(1)
//	{
//		MQTT_PingREQ();   //发送心跳包
//		LCD_ShowString(40,90,240,320,16,receive_data);		//显示云端发送的内容
//		if(strstr((const char*)receive_data ,(const char*)"\"led\":0"))  //判断接收到的数据有没有目标数据    
//		{
//			LED1=1;
//		}
//	if(strstr((const char*)receive_data ,(const char*)"\"led\":1"))  //判断接收到的数据有没有目标数据 
//		{
//			LED1=0;
//		}
//		
//		
//		   
//		if(time>=25)
//		{
//			cjson_creat();
//		}
//		
//		LED0=0;
//		delay_ms (1000);
//		LED0=1;
//		delay_ms (1000);
//	}
}

