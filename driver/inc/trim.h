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
* XHSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
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
/** \file trim.h
 **
 ** TRIM ???????????????API??????
 **  
 **
 ** History:
 **   - 2017-05-10   Lux     V1.0
 **
 *****************************************************************************/

#ifndef __TRIM_H__
#define __TRIM_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup TrimGroup Clock Trimming (TRIM)
 **
 ******************************************************************************/
//@{

/******************************************************************************
 ** Global pre-processor symbols/macros ('#define')                            
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

 /**
 ******************************************************************************
 ** \brief ?????????????????????????????????    (MON_EN)
 *****************************************************************************/
typedef enum en_trim_monitor
{
    MonDisable = 0u,            ///< ??????
    MonEnable  = 1u,            ///< ??????
}en_trim_monitor_t; 
 
 /**
 ******************************************************************************
 ** \brief ?????????/????????????????????????????????? (CALCLK_SEL)
 *****************************************************************************/
typedef enum en_trim_calclksel
{
    CALIRC16M  = 0u,            ///< ??????16M
    CALXTAL32M = 1u,            ///< ??????32M
    CALIRC32K  = 2u,            ///< ??????32K
    CALXTAL32K = 3u,            ///< ??????32K
}en_trim_calclksel_t;

/**
 ******************************************************************************
 ** \brief ????????????????????????????????? (REFCLK_SEL)
 *****************************************************************************/
typedef enum en_trim_refclksel
{
    RefIRC16M  = 0u,            ///< ??????16M
    RefXTAL32M = 1u,            ///< ??????32M
    RefIRC32K  = 2u,            ///< ??????32K
    RefXTAL32K = 3u,            ///< ??????32K
    RefIRC10K  = 4u,            ///< ??????10K
    ExtClkIn   = 5u,            ///< ??????????????????
}en_trim_refclksel_t;

/**
 ******************************************************************************
 ** \brief ?????????????????????????????????
 *****************************************************************************/
typedef enum en_trim_inttype
{
    RefStop      = 0u,            ///< ???????????????????????????
    CalCntOf     = 1u,            ///< ???????????????????????????
    XTAL32KFault = 2u,            ///< XTAL32K ????????????
    XTAL32MFault = 3u,            ///< XTAL32M ????????????
}en_trim_inttype_t;

/**
 ******************************************************************************
 ** \brief TRIM ????????????????????? 
 *****************************************************************************/
typedef struct stc_trim_config
{
    en_trim_monitor_t    enMON;         ///< ????????????
    en_trim_calclksel_t  enCALCLK;      ///< ??????????????????
    en_trim_refclksel_t  enREFCLK;      ///< ??????????????????
    
    func_ptr_t           pfnTrimCb;     ///< TRIM ????????????????????????[void function(void)]
}stc_trim_config_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//????????????????????????
//??????????????????
boolean_t Trim_GetIntFlag(en_trim_inttype_t enIntType);
//??????????????????
en_result_t Trim_ClearIntFlag(en_trim_inttype_t enIntType);
//????????????/??????
en_result_t Trim_EnableIrq (void);
en_result_t Trim_DisableIrq(void);

//???????????????????????????
//Trim ??????????????????
en_result_t Trim_Init(stc_trim_config_t* pstcConfig);
//??????/????????????/??????
en_result_t Trim_Run(void);
en_result_t Trim_Stop(void);
//???????????????????????????
en_result_t Trim_RefConSet(uint32_t u32Data);
//???????????????????????????
en_result_t Trim_CalConSet(uint32_t u32Data);
//??????????????????????????????
uint32_t Trim_RefCntGet(void);
//??????????????????????????????
uint32_t Trim_CalCntGet(void);

//@} // TrimGroup

#ifdef __cplusplus
#endif


#endif /* __TRIM_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


