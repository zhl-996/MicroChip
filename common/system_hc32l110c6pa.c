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
** @file system_hc32l110c6pa.c
**
** @brief Headerfile for SYSTEM functions
**
** @author MADS Team
**
** - 2022-01-26.
**
******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"
#include "hc32l110.h"
#include "system_hc32l110.h"
#include "ddl.h"
/**
 ******************************************************************************
 ** System Clock Frequency (Core Clock) Variable according CMSIS
 ******************************************************************************/
uint32_t SystemCoreClock;

static void _HidePinInit(void)
{
#if !defined(HC32L110Cxxx)       //20PIN MCU	
    uint32_t tmpReg = M0P_CLOCK->PERI_CLKEN;
	
	M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;
    
  #if defined(HC32L110Bxxx)	     //16PIN MCU
    M0P_GPIO->P0ADS &= 0x07;     ///< P03配置为数字端口
	M0P_GPIO->P3ADS &= 0xE3;     ///< P32/P33/P34配置为数字端口
	
    M0P_GPIO->P0DIR	|= 0xF8;     ///< P03配置为端口输入
    M0P_GPIO->P3DIR	|= 0x1C;     ///< P32/P33/P34配置为端口输入
	
	M0P_GPIO->P0PU  |= 0xF8;     ///< P03配置为上拉
	M0P_GPIO->P3PU  |= 0x1C;     ///< P32/P33/P34配置为上拉
    
  #endif
	  M0P_CLOCK->PERI_CLKEN = tmpReg;
#endif
}
//add clock source.
void SystemCoreClockUpdate (void) // Update SystemCoreClock variable
{
    SystemCoreClock = Clk_GetHClkFreq();
}

/**
 ******************************************************************************
 ** \brief  Setup the microcontroller system. Initialize the System and update
 ** the SystemCoreClock variable.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
void SystemInit(void)
{    

    stc_clk_systickcfg_t stcCfg;
		Clk_Enable(ClkXTH, TRUE);                  
    SystemCoreClockUpdate();
	  _HidePinInit();
    DDL_ZERO_STRUCT(stcCfg);
    stcCfg.bNoRef = TRUE;
    stcCfg.u32LoadVal = 0xFFFFFF;
    Clk_SysTickConfig(&stcCfg);
}


