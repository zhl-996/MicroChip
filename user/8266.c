#include "MyApplication.h"

char MyMacAddress[17]=  "48:3f:da:67:ba:32";
bj_time BjTime;
stc_rtc_time_t  stcReadTime;
struct tm *timeinfo;
static void RtcCycCb(void)
{

	Rtc_ReadDateTime(&stcReadTime);
	printf("日期:%d%d-%d%d-%d%d   时间:%d%d:%d%d:%d%d\r\n",(stcReadTime.u8Year&0xF0)>>4,(stcReadTime.u8Year&0x0F),(stcReadTime.u8Month&0xF0)>>4,(stcReadTime.u8Month&0x0F),(stcReadTime.u8Day&0xF0)>>4,(stcReadTime.u8Day&0x0F),(stcReadTime.u8Hour&0xF0)>>4,(stcReadTime.u8Hour&0x0F),(stcReadTime.u8Minute&0xF0)>>4,(stcReadTime.u8Minute&0x0F),(stcReadTime.u8Second&0xF0)>>4,(stcReadTime.u8Second&0x0F));
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
	
	Usart2_RxCounter=0;                           //WiFi接收数据量变量清零                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //清空WiFi接收缓冲区
	//发送AT指令
	WiFi_printf(Ptr_AT_Command);	
	//打印信息
	printf("%s",Ptr_AT_Command);
	
	//等待模块回应数据，超时错误处理
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
	//延时10ms，接收完全部字节
	delay1ms(10);
	
	//模块回应数据处理处理
	if(strstr((const char*)Usart2_RxBuff,(const char*)Ptr_Respond_Str) == NULL)
	{
	//	ESP8266.Error();
	}
	
	//打印信息
	printf("%s",Usart2_RxBuff);

}

/*
	* @name   Init
	* @brief  ESP8266初始化
	* @param  None
	* @retval None      
*/
void ESP8266_Init() 
{
	
	//复位模组
	Gpio_SetIO(WIFI_RST_GPIO_Port,WIFI_RST_Pin,FALSE);
	delay1ms(10);
	Gpio_SetIO(WIFI_RST_GPIO_Port,WIFI_RST_Pin,TRUE);
	
	//使能模组
	Gpio_SetIO(WIFI_EN_GPIO_Port,WIFI_EN_Pin,TRUE);
	//延时500ms，等待WIFI模块稳定，准备好接收AT指令
	delay1ms(500);
	
	//同步波特率
	Timer2_CNT = 0;
	Usart2_RxCounter=0;                           //WiFi接收数据量变量清零                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
	do
	{	
		//发送AT指令
		WiFi_printf((uint8_t*)"AT\r\n");
		//延时100ms，等待接收完成
		delay1ms(100);
		
		//打印信息
		printf("%s",Usart2_RxBuff);
		
		//超时处理
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
	SendAT((uint8_t*)"ATE0\r\n",(uint8_t*)"OK");            //关闭回显
  SendAT((uint8_t*)"AT+CWMODE=1\r\n",(uint8_t*)"OK"); //WIFI模块设置为STA模式
	sprintf(buff, "AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI_SSID,WIFI_PASSWORD);
	Timer2_CNT = 0;
	Usart2_RxCounter=0;                           //WiFi接收数据量变量清零                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //清空WiFi接收缓冲区
	do
	{	
		//发送指令
		WiFi_printf((uint8_t*)buff);
		//延时100ms，等待接收完成
		delay1ms(1000);
		
		//打印信息
		printf("%s",Usart2_RxBuff);
		
		//超时处理
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
	SendAT((uint8_t*)"AT+MQTTCONNCFG=0,60,0,\"123\",\"123\",0,0\r\n",(uint8_t*)"OK");  //设置保活时间
	Timer2_CNT = 0;
	Usart2_RxCounter=0;                           //WiFi接收数据量变量清零                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //清空WiFi接收缓冲区
	do
	{

		//发送指令
		WiFi_printf((uint8_t*)MQTTCONNBuff);
		//延时100ms，等待接收完成
		delay1ms(2000);
		
		//打印信息
		printf("%s",Usart2_RxBuff);
		
		//超时处理
		if(Timer2_CNT> TIMER2_10S)
		{
			//ESP8266.Error();
			break;
		}
	}
	while(strstr((const char*)Usart2_RxBuff,"OK") == NULL);
	
	SendAT((uint8_t*)"AT+MQTTSUB=0,\"/sys/he5o1HgIcEg/48:3f:da:67:ba:32/thing/event/property/set\",1\r\n",(uint8_t*)"OK");  //订阅主题
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
	Usart2_RxCounter=0;                           //WiFi接收数据量变量清零                        
	memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //清空WiFi接收缓冲区
	printf("%s",MQTTPOSTBuff);
	do
	{
		
		//发送指令
		WiFi_printf((uint8_t*)MQTTPOSTBuff);
		//延时100ms，等待接收完成
		delay1ms(1000);
		
		//打印信息
		printf("%s",Usart2_RxBuff);
		
		//超时处理
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
    char SubTopic[100]; //订阅Topic用的
		int TimeChuo_int;
	

	  sprintf(SubTopic, "AT+MQTTSUB=0,\"/ext/ntp/%s/%s/response\",1\r\n",ProductKey,DeviceName);
		sprintf(GetTimeBuff,"AT+MQTTPUB=0,\"/ext/ntp/%s/%s/request\",\"{\\\"deviceSendTime\\\":\\\"1592361428000\\\"}\",0,0\r\n",ProductKey,DeviceName);
		SendAT((uint8_t*)SubTopic,(uint8_t*)"OK");
		Timer2_CNT = 0;
		Usart2_RxCounter=0;                           //WiFi接收数据量变量清零                        
		memset(Usart2_RxBuff,0,USART2_RXBUFF_SIZE);     //清空WiFi接收缓冲区
		printf("%s",GetTimeBuff);
	do
	{
		
		//发送指令
		WiFi_printf((uint8_t*)GetTimeBuff);
		//延时100ms，等待接收完成
		delay1ms(1000);
		
		//打印信息
		printf("%s",Usart2_RxBuff);
		
		//超时处理
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
    /* 调用系统函数 */
   timeinfo = localtime(&timestamp);

		BjTime.year = timeinfo->tm_year;  /* 自1900年算起 */
		BjTime.month = timeinfo->tm_mon;  /* 从1月算起，范围0-11 */

		BjTime.day = timeinfo->tm_mday;   /* 日: 1-31 */
		BjTime.hour = timeinfo->tm_hour;  /* 小时:0-23点,UTC+0时间 */
		BjTime.minute = timeinfo->tm_min; /* 分钟:0-59 */
		BjTime.second = timeinfo->tm_sec; /* 0-60，偶尔出现的闰秒 */

			/* 时间校正 */
		BjTime.year += 1900;
		BjTime.month += 1;
	  printf("日期:%d-%d-%d   时间:%d:%d:%d\r\n",  BjTime.year, BjTime.month, BjTime.day,BjTime.hour, BjTime.minute, BjTime.second);

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
	
		Clk_Enable(ClkXTL, TRUE);//开启外部晶振32.768   
    Clk_SetPeripheralGate(ClkPeripheralRtc,TRUE);//使能rtc时钟
		    
		stcRtcConfig.enClkSel = RtcClk32768;//RtcClkHxt1024;//RtcClk32;//
    stcRtcConfig.enAmpmSel = Rtc24h;//Rtc12h;//
    stcCycSel.enCyc_sel = RtcPrads;  //rtc周期中断配置
    stcCycSel.enPrds_sel = Rtc_1S;
		stcRtcConfig.pstcCycSel = &stcCycSel;//周期配置
		
		
		Rtc_DisableFunc(RtcCount);
//    stcAlarm.u8Minute = BjTime.minute;  //闹钟
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
    stcTime.u8DayOfWeek = Rtc_CalWeek(&stcTime.u8Day);  //根据日期算周数
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