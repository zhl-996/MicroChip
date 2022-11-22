#ifndef __8266_H
#define __8266_H

#include "ddl.h"

void WiFi_printf(uint8_t* p_Str) ;
void ESP8266_Init(void);
void ESP8266_ConnectWiFi(void);
void ConnectMQTT(void); 
void MQTTPOST(void);
void GetNtpTime(void);
void RTC_Init(void);
int bcd_decimal_code( int bcd);
int decimal_bcd_code(int decimal);
#endif
