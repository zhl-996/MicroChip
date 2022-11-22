#ifndef __MYAPPLICATION_H_
#define __MYAPPLICATION_H_

#include "MyUART.h"

#include "ddl.h"
#include "uart.h"
#include "bt.h"
#include "lpm.h"
#include "rtc.h"
#include "gpio.h"
#include "Timer0.h"
#include "8266.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "MyGPIO.h"
#include "time.h"

 typedef struct{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}bj_time;
extern bj_time BjTime;

#define WIFI_RST_GPIO_Port (2)
#define WIFI_RST_Pin			 (5)
#define WIFI_EN_GPIO_Port (2)
#define WIFI_EN_Pin			 (6)

#define  WIFI_SSID  			  (uint8_t*)"ZHAN"
#define  WIFI_PASSWORD      (uint8_t*)"ZHAN.499.85.net"
#define  GetSecret_PASSWORD (uint8_t*)"de07e77ae38fd5ddfe5faed1f9ce15ae"

/*ศýิชื้*/
#define  ProductKey     (uint8_t*) "he5o1HgIcEg"
#define  DeviceName     (uint8_t*) "48:3f:da:67:ba:32"
#define  DeviceSecret   (uint8_t*) "bf6e1165393a08666774bb3267e53145"
#define  PASSWORD 			(uint8_t*) "839AD02F6F148C36C91EE69859A6B343"



void SendAT(uint8_t * AT_Command,uint8_t * Respond_Str);
#endif

