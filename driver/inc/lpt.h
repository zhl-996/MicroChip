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
/** \file lpt.h
 **
 ** ?????????????????????????????????API??????
 **  
 **
 ** History:
 **   - 2017-05-10   Lux     V1.0
 **
 *****************************************************************************/

#ifndef __LPT_H__
#define __LPT_H__

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
 *******************************************************************************
 ** \defgroup LptGroup Low Power Timer (LPT)
 **
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief GATE ????????????????????????????????? (GATE_P)
 *****************************************************************************/
typedef enum en_lpt_gatep
{
    LptPositive = 0u,            ///< ???????????????
    LptOpposite = 1u,            ///< ???????????????
}en_lpt_gatep_t;

/**
 ******************************************************************************
 ** \brief ???????????????????????????????????? (GATE)
 *****************************************************************************/
typedef enum en_lpt_gate
{
    LptGateDisable = 0u,            ///< ?????????
    LptGateEnable  = 1u,            ///< ????????????
}en_lpt_gate_t;

/**
 ******************************************************************************
 ** \brief Lptimer ????????????????????????????????? (TCK_SEL)
 *****************************************************************************/
typedef enum en_lpt_clksel
{
    LptPCLK   = 0u,           ///< PCLK
    LptXIL32K = 2u,           ///< XIL32K
    LptIRC32K = 3u,           ///< IRC32K
}en_lpt_clksel_t;

/**
 ******************************************************************************
 ** \brief ??????????????????????????????????????? (TOG_EN)
 *****************************************************************************/
typedef enum en_lpt_toggle
{
    LptTogDisable = 0u,            ///< ??????????????????
    LptTogEnable  = 1u,            ///< ??????????????????
}en_lpt_toggle_t;

/**
 ******************************************************************************
 ** \brief ??????/?????????????????????????????????????????? (CT)
 *****************************************************************************/
typedef enum en_lpt_function
{
    LptTimer   = 0u,            ///< ???????????????
    LptCounter = 1u,            ///< ???????????????
}en_lpt_function_t;


/**
 ******************************************************************************
 ** \brief ?????????????????????????????????????????? (MD)
 *****************************************************************************/
typedef enum en_lpt_mode
{
    LptMode1  = 0u,         ///< 16????????????/?????????
    LptMode2  = 1u,         ///< ???????????????16????????????/?????????
}en_lpt_mode_t;

/**
 ******************************************************************************
 ** \brief ?????????????????????????????????????????? (TR)
 *****************************************************************************/
typedef enum en_lpt_start
{
    LptTRDisable = 0u,            ///< ??????
    LptTREnable  = 1u,            ///< ??????
}en_lpt_start_t;

/**
 ******************************************************************************
 ** \brief Lptimer ????????????????????? 
 *****************************************************************************/
typedef struct stc_lpt_config
{
    en_lpt_gatep_t    enGateP;      ///< ??????????????????
    en_lpt_gate_t     enGate;       ///< ????????????
    en_lpt_clksel_t   enTckSel;     ///< ????????????
    en_lpt_toggle_t   enTog;        ///< ??????????????????
    en_lpt_function_t enCT;         ///< ??????/??????????????????
    en_lpt_mode_t     enMD;         ///< ??????????????????
    
    func_ptr_t pfnLpTimCb;          ///< LpTimer????????????????????????[void function(void)]
}stc_lpt_config_t;


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//?????????????????? 
//??????????????????
boolean_t Lpt_GetIntFlag(void);
//??????????????????
en_result_t Lpt_ClearIntFlag(void);
//????????????/??????
en_result_t Lpt_EnableIrq (void);
en_result_t Lpt_DisableIrq(void);

//??????????????????????????????
//Lptimer??????????????????
en_result_t Lpt_Init(stc_lpt_config_t* pstcConfig);
//Lptimer ??????/??????
en_result_t Lpt_Run(void);
en_result_t Lpt_Stop(void);
//???????????????
en_result_t Lpt_ARRSet(uint16_t u16Data);
//???????????????
uint16_t Lpt_Cnt16Get(void);

//@} // LptGroup

#ifdef __cplusplus
#endif


#endif /* __LPT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


