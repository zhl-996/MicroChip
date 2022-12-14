/******************************************************************************
* Copyright (C) 2017, Xiaohua Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Xiaohua Semiconductor Co.,Ltd ("XHSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with XHSC
* components. This software is licensed by XHSC to be adapted only
* for use in systems utilizing XHSC components. XHSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. XHSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* XHSC MAKES NO WARRANTY, EXPRESS OR IMPLIED   , ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* XHSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file spi.h
 **
 ** Headerfile for SPI functions
 **  
 **
 ** History:
 **   - 2017-05-17  1.0  Devi     First Version
 **
 *****************************************************************************/
#ifndef __SPI_H__
#define __SPI_H__

/******************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

//@{

/******************************************************************************
 * Global type definitions
 *****************************************************************************/
/**
 ******************************************************************************
 ** \brief SPI ??????????????????
 ******************************************************************************/ 
typedef enum en_spi_en
{
    SpiEnable     = 1u,  ///< SPI????????????
    SpiDisable    = 0u,  ///< SPI????????????
}en_spi_en_t;
/**
 ******************************************************************************
 ** \brief SPI ????????????
 ******************************************************************************/ 
typedef enum en_spi_mode
{
    SpiMaster = 1u,  ///<??????
    SpiSlave  = 0u,  ///<??????
}en_spi_mode_t;
/**
 ******************************************************************************
 ** \brief SPI ??????????????????
 ******************************************************************************/ 
typedef enum en_spi_cpol
{
    Spicpollow   = 0u,  ///<????????????
    Spicpolhigh  = 1u,  ///<????????????
}en_spi_cpol_t;
/**
 ******************************************************************************
 ** \brief SPI ??????????????????
 ******************************************************************************/ 
typedef enum en_spi_cpha
{
    Spicphafirst   = 0u,  ///<??????????????????
    Spicphasecond  = 1u,  ///<??????????????????
}en_spi_cpha_t;
/**
 ******************************************************************************
 ** \brief SPI ??????????????????
 *****************************************************************************/
typedef enum en_spi_clk_div
{
    SpiClkDiv2   = 0u,   ///<2??????       
    SpiClkDiv4   = 1u,   ///<4??????            
    SpiClkDiv8   = 2u,   ///<8??????            
    SpiClkDiv16  = 3u,   ///<16??????            
    SpiClkDiv32  = 4u,   ///<32??????            
    SpiClkDiv64  = 5u,   ///<64??????            
    SpiClkDiv128 = 6u,   ///<128??????            
}en_spi_clk_div_t;

/**
 ******************************************************************************
 ** \brief SPI ?????????????????????
 *****************************************************************************/
typedef enum en_spi_cspin
{
    SpiCsLow  = 0u,      ///<???????????????         
    SpiCsHigh = 1u,      ///<???????????????            
}en_spi_cspin_t;

/**
 ******************************************************************************
 ** \brief SPI ??????
 *****************************************************************************/
typedef enum en_spi_status
{
    SpiIf              = 0x80,   ///<????????????????????????    
    SpiWcol            = 0x40,   ///<???????????????    
    SpiSserr           = 0x20,   ///<????????????????????????    
    SpiMdf             = 0x10,   ///<????????????????????????    
}en_spi_status_t;
/**
 ******************************************************************************
 ** \brief SPI ?????????????????????
 *****************************************************************************/
typedef struct stc_spi_config
{
    boolean_t           bMasterMode;     ///< ??????????????????
    uint8_t             u8BaudRate;      ///< ???????????????
    boolean_t           bCPOL;           ///< ??????????????????
    boolean_t           bCPHA;           ///< ??????????????????
    boolean_t           bIrqEn;          ///< ????????????
    func_ptr_t          pfnIrqCb;        ///< ??????????????????
}stc_spi_config_t;

//SPI ??????
void Spi_IRQHandler(void);

//SPI ????????????      
boolean_t Spi_GetStatus(en_spi_status_t enStatus);

//SPI???????????????
en_result_t Spi_Init(stc_spi_config_t* pstcSpiConfig);
//SPI????????????
en_result_t Spi_DeInit(void);
//SPI ????????????????????????
void Spi_SetCS(boolean_t bFlag);
//SPI ????????????
en_result_t Spi_SendData(uint8_t u8Data);
//SPI ????????????
uint8_t Spi_ReceiveData(void);

//@} // Spi Group

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

