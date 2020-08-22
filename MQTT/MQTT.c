#include "mqtt.h"
#include "common.h"
#include "text.h"
#include "MQTTPacket.h"
#include "transport.h"
#include "cjson.h"
#include "timer.h"

char receive_data[100];

char *topic="/sys/a1ywqH8kuPn/temper/thing/event/property/post";//��������

char *cjson="{\"method\":\"thing.service.property.set\",\"id\":\"1338379119\",\"params\":{\"led\":0},\"version\":\"1.0.0\"}";
u16 a=0;
u8 time;
u8 i;
unsigned char buf[200];

short temperature=39; 


//����Ŀ��MQTT������
void mqtt_connect()
{
    int32_t len;
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;//���ò��ֿɱ�ͷ����ֵ
    
    int buflen = sizeof(buf);
		memset(buf,0,buflen);
    data.clientID.cstring = "temper|securemode=3,signmethod=hmacsha1|";//�ͻ��˱�ʶ����������ÿ���ͻ���xxxΪ�Զ��壬����Ϊ�̶���ʽ
    data.keepAliveInterval = 120;//�����ʱ���������˷������յ��ͻ�����Ϣ�����ʱ����
    data.cleansession = 1;//�ñ�־��1���������붪��֮ǰ���ֵĿͻ��˵���Ϣ������������Ϊ�������ڡ�
    data.username.cstring = "temper&a1ywqH8kuPn";//�û��� DeviceName&ProductKey
    data.password.cstring = "52e31a47f6321c7dec0804144853c6813f4c0678";//���룬��������
    len = MQTTSerialize_connect(buf, buflen, &data); /*1 �������ӱ���*/

    transport_sendPacketBuffer(USART3,buf,len);
		Show_Str(40,55,200,16,"MQTT���ӳɹ�",16,0);
}


/*----------------------------------------------------------*/
/*��������SUBSCRIBE����topic����                            */
/*��  ����temp_buff�����汨�����ݵĻ�����                                                */
/*��  ����QoS�����ĵȼ�                                     */
/*��  ����topic_name������topic��������                     */
/*����ֵ�����ĳ���                                                                                                                */
/*----------------------------------------------------------*/
void MQTT_Subscribe(unsigned char *temp_buff, char *topic_name, int QoS)
{
	u8 Fixed_len = 2;                                 //SUBSCRIBE�����У��̶���ͷ����=2
	u8 Variable_len = 2;                              //SUBSCRIBE�����У��ɱ䱨ͷ����=2
	u8 Payload_len = 2 + strlen(topic_name) + 1;   //������Ч���ɳ��� = 2�ֽ�(topic_name����)+ topic_name�ַ����ĳ��� + 1�ֽڷ���ȼ�

	temp_buff[0]=0x82;                                          //��1���ֽ� ���̶�0x82
	temp_buff[1]=Variable_len + Payload_len;                    //��2���ֽ� ���ɱ䱨ͷ+��Ч���ɵĳ���
	temp_buff[2]=0x00;                                          //��3���ֽ� �����ı�ʶ�����ֽڣ��̶�ʹ��0x00
	temp_buff[3]=0x01;		                                    //��4���ֽ� �����ı�ʶ�����ֽڣ��̶�ʹ��0x01
	temp_buff[4]=strlen(topic_name)/256;                     //��5���ֽ� ��topic_name���ȸ��ֽ�
	temp_buff[5]=strlen(topic_name)%256;		                //��6���ֽ� ��topic_name���ȵ��ֽ�
	memcpy(&temp_buff[6],topic_name,strlen(topic_name));  //��7���ֽڿ�ʼ �����ƹ���topic_name�ִ�
	temp_buff[6+strlen(topic_name)]=QoS;                     //���1���ֽڣ����ĵȼ�
	
	transport_sendPacketBuffer(USART3,buf,Fixed_len + Variable_len + Payload_len);
	Show_Str(40,55,200,16,"��������ɹ�",16,0);
}


//������Ϣ
int mqtt_publish(char *pTopic,char *pMessage,int QoS)
{
    int32_t len;
    MQTTString topicString = MQTTString_initializer;
    int msglen = strlen(pMessage);//���㷢����Ϣ�ĳ���
    int buflen = sizeof(buf);

    memset(buf,0,buflen);
    topicString.cstring = pTopic;//"�豸topic�б��еĵ�һ��";
    len = MQTTSerialize_publish(buf, buflen, 0, QoS, 0, 0, topicString, (unsigned char*)pMessage, msglen); /*���췢����Ϣ�ı���*/

    transport_sendPacketBuffer(USART3,buf,len);//������Ϣ
		free(buf);
		Show_Str(40,55,200,16,"������Ϣ�ɹ�",16,0);
    return 0;
}

/*----------------------------------------------------------*/
/*��������PING���ģ�������                                  */
/*��  ������                                               */
/*����ֵ����                                                */
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
	while(atk_8266_send_cmd("ATE0","OK",20));//�رջ���   u3_printf("%s\r\n",cmd);	//��������
	
	while(atk_8266_send_cmd("AT+CWMODE_CUR=1","OK",20));     //��Ϊ�ͻ���ģʽ
	
	while(atk_8266_send_cmd("AT+CWJAP_CUR=\"CMCC-biR5\",\"ywrg3nbu\"","OK",20));  //����WIFI
	Show_Str(40,55,200,16,"WIFI���ӳɹ�",16,0);
	while(atk_8266_send_cmd("AT+CIPSTART=\"TCP\",\"a18qhFfWs3H.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883","OK",20));  //TCP����
	
	delay_ms (1000);
	
	while(atk_8266_send_cmd("AT+CIPMODE=1","OK",20));  //��͸��ģʽ
	
	delay_ms (1000);

	while(atk_8266_send_cmd("AT+CIPSEND",">",20));  //��ʼ��������
	Show_Str(40,55,200,16,"��ʼ��������",16,0);
	delay_ms (1000);
	mqtt_connect();
	delay_ms (1000);
	
	MQTT_Subscribe(buf,topic,1);  //��������


}


void mqtt_sendmassage()
{
	cjson_creat();
//	while(1)
//	{
//		MQTT_PingREQ();   //����������
//		LCD_ShowString(40,90,240,320,16,receive_data);		//��ʾ�ƶ˷��͵�����
//		if(strstr((const char*)receive_data ,(const char*)"\"led\":0"))  //�жϽ��յ���������û��Ŀ������    
//		{
//			LED1=1;
//		}
//	if(strstr((const char*)receive_data ,(const char*)"\"led\":1"))  //�жϽ��յ���������û��Ŀ������ 
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

