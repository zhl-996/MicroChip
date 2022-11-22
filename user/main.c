/******************************************************************************
 * Copyright (C) 2021, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************/
 
/******************************************************************************
 ** @file main.c
 **
 ** @brief Source file for MAIN functions
 **
 ** @author MADS Team 
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l110.h"
#include "gpio.h"
#include "MyApplication.h"
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                            
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')                                         
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void SystemClkConfig(void);
/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/
extern uint8_t u8RxFlg;


/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                             
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ******************************************************************************/
int32_t main(void)
{

	SystemClkConfig();
  Clk_SetPeripheralGate(ClkPeripheralBt, TRUE);
	Timer2Init();
	    
	Uart1Init(); //串口1用于打印log P23 24
	Uart0Init(); //串口0用于与8266通信   P35 36
	GPIOInit();
	ESP8266_Init();
	ESP8266_ConnectWiFi();
	delay1ms(500);
	ConnectMQTT();
	GetNtpTime();
	RTC_Init();
	while(1)
	{

	//MQTTPOST() ;
	delay1ms(2000);	
	
	}
			
}

void SystemClkConfig()
{
	  volatile uint32_t u32Val = 0;
		stc_clk_config_t stcCfg;
    Clk_SetPeripheralGate(ClkPeripheralGpio, TRUE);
	   Clk_SwitchTo(ClkXTH);
    //CLK初始化
    DDL_ZERO_STRUCT(stcCfg);
	    //选择外部高低速时钟
    stcCfg.enClkSrc = ClkXTH;       // 8M
    stcCfg.enHClkDiv = ClkDiv1;   // 8
    stcCfg.enPClkDiv = ClkDiv1;     // 8
 

    Clk_Init(&stcCfg);
   
    u32Val = Clk_GetHClkFreq();    

//    //P24 输出HCLK
   Gpio_SetFunc_HCLKOUT_P24();
}
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


