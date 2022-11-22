#include "MyApplication.h"

char MyMacAddress[17]=  "48:3f:da:67:ba:32";
bj_time BjTime;
stc_rtc_time_t  stcReadTime;
struct tm *timeinfo;
static void RtcCycCb(void)
{

	Rtc_ReadDateTime(&stcReadTime);
	printf("����:%d%d-%d%d-%d%d   ʱ��:%d%d:%d%d:%d%d\r\n",(stcReadTime.u8Year&0xF0)>>4,(stcReadTime.u8Year&0x0F),(stcReadTime.u8Month&0xF0)>>4,(stcReadTime.u8Month&0x0F),(stcReadTime.u8Day&0xF0)>>4,(stcReadTime.u8Day&0x0F),(stcReadTime.u8Hour&0xF0)>>4,(stcReadTime.u8Hour&0x0F),(stcReadTime.u8Minute&0xF0)>>4,(stcReadTime.u8Minute&0x0F),(stcReadTime.u8Second&0xF0)>>4,(stcReadTime.u8Second&0x0F));
}
void WiFi_printf(uint8_t* p_Str) 
{	
	uint8_t i;
	uint8_t*  Buff=p_Str;
	uint16_t BuffLength = strlen((const char *)Buff);
	for(i=0;i<BuffLength;i++)
	{
	Uart_SendData(UARTCH0,*Buff);	
	Buff++;
	}
}
void SendAT(uint8_t * AT_Command,uint8_t * Respond_Str)
{
	uint8_t* const  Ptr_AT_Command   = AT_Command;
	uint8_t* const  Ptr_Respond_Str  = Respond_Str;
	
	Usart2_RxCounter=0;                           //WiFi������������������                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //���WiFi���ջ�����
	//����ATָ��
	WiFi_printf(Ptr_AT_Command);	
	//��ӡ��Ϣ
	printf("%s",Ptr_AT_Command);
	
	//�ȴ�ģ���Ӧ���ݣ���ʱ������
	Timer2_CNT = 0;

	while(strstr((const char*)Usart2_RxBuff,"\r\n") == NULL)
	{
		if(Timer2_CNT> TIMER2_10S)
		{
			//ESP8266.Error();
			printf("Error!!!\r\n");
			break;
		}
	}
	//��ʱ10ms��������ȫ���ֽ�
	delay1ms(10);
	
	//ģ���Ӧ���ݴ�����
	if(strstr((const char*)Usart2_RxBuff,(const char*)Ptr_Respond_Str) == NULL)
	{
	//	ESP8266.Error();
	}
	
	//��ӡ��Ϣ
	printf("%s",Usart2_RxBuff);

}

/*
	* @name   Init
	* @brief  ESP8266��ʼ��
	* @param  None
	* @retval None      
*/
void ESP8266_Init() 
{
	
	//��λģ��
	Gpio_SetIO(WIFI_RST_GPIO_Port,WIFI_RST_Pin,FALSE);
	delay1ms(10);
	Gpio_SetIO(WIFI_RST_GPIO_Port,WIFI_RST_Pin,TRUE);
	
	//ʹ��ģ��
	Gpio_SetIO(WIFI_EN_GPIO_Port,WIFI_EN_Pin,TRUE);
	//��ʱ500ms���ȴ�WIFIģ���ȶ���׼���ý���ATָ��
	delay1ms(500);
	
	//ͬ��������
	Timer2_CNT = 0;
	Usart2_RxCounter=0;                           //WiFi������������������                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //���WiFi���ջ����� 
	do
	{	
		//����ATָ��
		WiFi_printf((uint8_t*)"AT\r\n");
		//��ʱ100ms���ȴ��������
		delay1ms(100);
		
		//��ӡ��Ϣ
		printf("%s",Usart2_RxBuff);
		
		//��ʱ����
		if(Timer2_CNT> TIMER2_10S)
		{
			printf("Error\r\n");
			break;
		}
	}
	while(strstr((const char*)Usart2_RxBuff,"OK") == NULL);
	
		printf("OKK");
}

void ESP8266_ConnectWiFi()
{

	char buff[200];
	SendAT((uint8_t*)"ATE0\r\n",(uint8_t*)"OK");            //�رջ���
  SendAT((uint8_t*)"AT+CWMODE=1\r\n",(uint8_t*)"OK"); //WIFIģ������ΪSTAģʽ
	sprintf(buff, "AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI_SSID,WIFI_PASSWORD);
	Timer2_CNT = 0;
	Usart2_RxCounter=0;                           //WiFi������������������                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //���WiFi���ջ�����
	do
	{	
		//����ָ��
		WiFi_printf((uint8_t*)buff);
		//��ʱ100ms���ȴ��������
		delay1ms(1000);
		
		//��ӡ��Ϣ
		printf("%s",Usart2_RxBuff);
		
		//��ʱ����
		if(Timer2_CNT> TIMER2_10S)
		{
			//ESP8266.Error();
			break;
		}
	}
	while(strstr((const char*)Usart2_RxBuff,"WIFI GOT IP") == NULL);
	
	printf("OKK");
}


void ConnectMQTT() 
{
	char UserNameBuff[100]="0";
	char PasswordBuff[100]="0";	
	char MQTTCONNBuff[100]="0";	

	sprintf(UserNameBuff, "AT+MQTTUSERNAME=0,\"%s&%s\"\r\n",MyMacAddress,ProductKey);
	sprintf(PasswordBuff, "AT+MQTTPASSWORD=0,\"%s\"\r\n",PASSWORD);
	sprintf(MQTTCONNBuff,"AT+MQTTCONN=0,\"%s.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,1\r\n",ProductKey);
	SendAT((uint8_t*)"AT+MQTTUSERCFG=0,2,\"NULL\",\"NULL\",\"NULL\",0,0,\"\"\r\n",(uint8_t*)"OK");
	delay1ms(300);	
  SendAT((uint8_t*)UserNameBuff,(uint8_t*)"OK");            //UserName
	delay1ms(300);
  SendAT((uint8_t*)PasswordBuff,(uint8_t*)"OK");            //PasswordBuff
	delay1ms(300);
	SendAT((uint8_t*)"AT+MQTTCLIENTID=0,\"32131|securemode=3\\,signmethod=hmacmd5|\"\r\n",(uint8_t*)"OK"); 
	delay1ms(300);
	SendAT((uint8_t*)"AT+MQTTCONNCFG=0,60,0,\"123\",\"123\",0,0\r\n",(uint8_t*)"OK");  //���ñ���ʱ��
	Timer2_CNT = 0;
	Usart2_RxCounter=0;                           //WiFi������������������                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //���WiFi���ջ�����
	do
	{

		//����ָ��
		WiFi_printf((uint8_t*)MQTTCONNBuff);
		//��ʱ100ms���ȴ��������
		delay1ms(2000);
		
		//��ӡ��Ϣ
		printf("%s",Usart2_RxBuff);
		
		//��ʱ����
		if(Timer2_CNT> TIMER2_10S)
		{
			//ESP8266.Error();
			break;
		}
	}
	while(strstr((const char*)Usart2_RxBuff,"OK") == NULL);
	
	SendAT((uint8_t*)"AT+MQTTSUB=0,\"/sys/he5o1HgIcEg/48:3f:da:67:ba:32/thing/event/property/set\",1\r\n",(uint8_t*)"OK");  //��������
}
void MQTTPOST() 
{
	char PersonFlag[1];
	char MQTTPOSTBuff[500];
	if(Gpio_GetIO(3,4))
		PersonFlag[0]='1';
	else PersonFlag[0]='0';
	sprintf(MQTTPOSTBuff, "AT+MQTTPUB=0,\"/sys/%s/%s/thing/event/property/post\",\"{\\\"id\\\":\\\"123456\\\"\\,\\\"version\\\":\\\"1.0\\\"\\,\\\"method\\\":\\\"thing.event.property.post\\\"\\,\\\"params\\\":{\\\"Temperature\\\":{\\\"value\\\": 66.6}\\,\\\"HumanDetection\\\": {\\\"value\\\": %.1s}}}\",1,0\r\n",ProductKey,DeviceName,PersonFlag);
	Timer2_CNT = 0;
	Usart2_RxCounter=0;                           //WiFi������������������                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //���WiFi���ջ�����
	printf("%s",MQTTPOSTBuff);
	do
	{
		
		//����ָ��
		WiFi_printf((uint8_t*)MQTTPOSTBuff);
		//��ʱ100ms���ȴ��������
		delay1ms(1000);
		
		//��ӡ��Ϣ
		printf("%s",Usart2_RxBuff);
		
		//��ʱ����
		if(Timer2_CNT> TIMER2_10S)
		{
			//ESP8266.Error();
			break;
		}
	}
	while(strstr((const char*)Usart2_RxBuff,"OK") == NULL);
	
	
}
void GetNtpTime()
{	

	
		time_t timestamp;
		char *buff;
		char Timechuo[11];
    char GetTimeBuff[128];
    char SubTopic[100]; //����Topic�õ�
		int TimeChuo_int;
	

	  sprintf(SubTopic, "AT+MQTTSUB=0,\"/ext/ntp/%s/%s/response\",1\r\n",ProductKey,DeviceName);
		sprintf(GetTimeBuff,"AT+MQTTPUB=0,\"/ext/ntp/%s/%s/request\",\"{\\\"deviceSendTime\\\":\\\"1592361428000\\\"}\",0,0\r\n",ProductKey,DeviceName);
		SendAT((uint8_t*)SubTopic,(uint8_t*)"OK");
		Timer2_CNT = 0;
		Usart2_RxCounter=0;                           //WiFi������������������                        
		memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //���WiFi���ջ�����
		printf("%s",GetTimeBuff);
	do
	{
		
		//����ָ��
		WiFi_printf((uint8_t*)GetTimeBuff);
		//��ʱ100ms���ȴ��������
		delay1ms(1000);
		
		//��ӡ��Ϣ
		printf("%s",Usart2_RxBuff);
		
		//��ʱ����
		if(Timer2_CNT> TIMER2_10S)
		{
			//ESP8266.Error();
			break;
		}
	}
	while((buff=strstr((const char*)Usart2_RxBuff,"\"serverSendTime\":")) == NULL);
	buff+=18;
  strncpy(Timechuo,buff,10);
	printf("%s\r\n",Timechuo);
	TimeChuo_int= atoi((const char*)Timechuo);
	printf("%d\r\n",TimeChuo_int);
	timestamp=TimeChuo_int;
	timestamp += 8 * 60 * 60;
    /* ����ϵͳ���� */
   timeinfo = localtime(&timestamp);

		BjTime.year = timeinfo->tm_year;  /* ��1900������ */
		BjTime.month = timeinfo->tm_mon;  /* ��1�����𣬷�Χ0-11 */

		BjTime.day = timeinfo->tm_mday;   /* ��: 1-31 */
		BjTime.hour = timeinfo->tm_hour;  /* Сʱ:0-23��,UTC+0ʱ�� */
		BjTime.minute = timeinfo->tm_min; /* ����:0-59 */
		BjTime.second = timeinfo->tm_sec; /* 0-60��ż�����ֵ����� */

			/* ʱ��У�� */
		BjTime.year += 1900;
		BjTime.month += 1;
	  printf("����:%d-%d-%d   ʱ��:%d:%d:%d\r\n",  BjTime.year, BjTime.month, BjTime.day,BjTime.hour, BjTime.minute, BjTime.second);

}
void RTC_Init()
{
		stc_rtc_config_t stcRtcConfig; 
    stc_rtc_irq_cb_t stcIrqCb;
    stc_rtc_time_t  stcTime;
    stc_rtc_alarmset_t stcAlarm;
    stc_rtc_cyc_sel_t   stcCycSel;
    stc_lpm_config_t stcLpmCfg;
	
		DDL_ZERO_STRUCT(stcRtcConfig);
    DDL_ZERO_STRUCT(stcIrqCb);
    DDL_ZERO_STRUCT(stcAlarm);
    DDL_ZERO_STRUCT(stcTime);
    DDL_ZERO_STRUCT(stcCycSel);
    DDL_ZERO_STRUCT(stcLpmCfg);
	
		Clk_Enable(ClkXTL, TRUE);//�����ⲿ����32.768   
    Clk_SetPeripheralGate(ClkPeripheralRtc,TRUE);//ʹ��rtcʱ��
		    
		stcRtcConfig.enClkSel = RtcClk32768;//RtcClkHxt1024;//RtcClk32;//
    stcRtcConfig.enAmpmSel = Rtc24h;//Rtc12h;//
    stcCycSel.enCyc_sel = RtcPrads;  //rtc�����ж�����
    stcCycSel.enPrds_sel = Rtc_1S;
		stcRtcConfig.pstcCycSel = &stcCycSel;//��������
		
		
		Rtc_DisableFunc(RtcCount);
//    stcAlarm.u8Minute = BjTime.minute;  //����
//    stcAlarm.u8Hour = BjTime.hour;
//    stcAlarm.u8Week = 0x08;
		
//    Rtc_DisableFunc(RtcAlarmEn);
//    Rtc_EnAlarmIrq(Rtc_AlarmInt_Enable);
//    Rtc_SetAlarmTime(&stcAlarm);
//    Rtc_EnableFunc(RtcAlarmEn);
		
//		stcTime.u8Year = 21;
//    stcTime.u8Month = BjTime.month;
//    stcTime.u8Day = BjTime.day;
//    stcTime.u8Hour = BjTime.hour;
//    stcTime.u8Minute = BjTime.minute;
//    stcTime.u8Second = BjTime.second;
    stcTime.u8Year = bcd_decimal_code(BjTime.year-2000);
    stcTime.u8Month = bcd_decimal_code(BjTime.month);
    stcTime.u8Day = bcd_decimal_code(BjTime.day);
    stcTime.u8Hour = bcd_decimal_code(BjTime.hour);
    stcTime.u8Minute = bcd_decimal_code(BjTime.minute);
    stcTime.u8Second = bcd_decimal_code(BjTime.second);
    stcTime.u8DayOfWeek = Rtc_CalWeek(&stcTime.u8Day);  //��������������
    stcRtcConfig.pstcTimeDate = &stcTime;
    
    //stcIrqCb.pfnAlarmIrqCb = RtcAlarmCb;
    stcIrqCb.pfnTimerIrqCb = RtcCycCb;
    stcRtcConfig.pstcIrqCb = &stcIrqCb;
    stcRtcConfig.bTouchNvic = TRUE;
    
    Rtc_DisableFunc(RtcCount);
    Rtc_Init(&stcRtcConfig); 
    
    Rtc_EnableFunc(RtcCount);
}
int bcd_decimal_code( int bcd)
{
    return (bcd + (bcd/10) * 6);
}
int decimal_bcd_code(int decimal)
{
    return (decimal - (decimal>>4) * 6);
}