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
/******************************************************************************/
/** \file adc.c
 **
 ** ADC driver API.
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "adc.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
 ******************************************************************************/
//@{

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
static void AdcEnableNvic(IRQn_Type enIrqn);
static void AdcDisableNvic(IRQn_Type enIrqn);

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static stc_adc_irq_calbakfn_pt_t stcAdcIrqCalbaks = {NULL, NULL, NULL, NULL};

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/


/**
 * \brief   
 *          ??????NVIC???ADC??????
 *
 * \param   [in]  enIrqn  ?????????
 *
 * \retval  ???
 */
static void AdcEnableNvic(IRQn_Type enIrqn)
{
    NVIC_ClearPendingIRQ(enIrqn);
    NVIC_EnableIRQ(enIrqn);
    NVIC_SetPriority(enIrqn, DDL_IRQ_LEVEL_DEFAULT);
}

/**
 * \brief   
 *          ??????NVIC???ADC??????
 *
 * \param   [in]  enIrqn  ?????????
 *
 * \retval  ???
 */
static void AdcDisableNvic(IRQn_Type enIrqn)
{
    NVIC_ClearPendingIRQ(enIrqn);
    NVIC_DisableIRQ(enIrqn);
    NVIC_SetPriority(enIrqn, DDL_IRQ_LEVEL_DEFAULT);
}

/**
 * \brief   
 *          ADC??????????????????
 *
 * \param   [in]  u8Param  ?????????
 *
 * \retval  ???
 */
void Adc_IRQHandler(uint8_t u8Param)
{
    if (TRUE == M0P_ADC->IFR_f.REG_INTF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcRegIrq)
        {
            stcAdcIrqCalbaks.pfnAdcRegIrq();
        }
        M0P_ADC->ICLR_f.REG_INTC = 0u;
    }

    if (TRUE == M0P_ADC->IFR_f.HHT_INTF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcHhtIrq)
        {
            stcAdcIrqCalbaks.pfnAdcHhtIrq();
        }
        M0P_ADC->ICLR_f.HHT_INTC = 0u;
    }

    if (TRUE == M0P_ADC->IFR_f.LLT_INTF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcLltIrq)
        {
            stcAdcIrqCalbaks.pfnAdcLltIrq();
        }
        M0P_ADC->ICLR_f.LLT_INTC = 0u;
    }

    if (TRUE == M0P_ADC->IFR_f.CONT_INTF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcContIrq)
        {
            stcAdcIrqCalbaks.pfnAdcContIrq();
        }
        M0P_ADC->ICLR_f.CONT_INTC = 0u;
    }
}

/**
 * \brief   
 *          ??????ADC??????
 *
 * \param   [in]  pstcAdcIrqCfg  ADC??????????????????
 * \param   [in]  pstcAdcIrqCalbaks  ADC????????????????????????
 *
 * \retval  ???
 */
void Adc_ConfigIrq(stc_adc_irq_t* pstcAdcIrqCfg,
                   stc_adc_irq_calbakfn_pt_t* pstcAdcIrqCalbaks)
{
    if (TRUE == pstcAdcIrqCfg->bAdcIrq)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcContIrq)
        {
            stcAdcIrqCalbaks.pfnAdcContIrq = pstcAdcIrqCalbaks->pfnAdcContIrq;
        }
    }

    if (TRUE == pstcAdcIrqCfg->bAdcRegCmp)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcRegIrq)
        {
            stcAdcIrqCalbaks.pfnAdcRegIrq = pstcAdcIrqCalbaks->pfnAdcRegIrq;
        }
    }

    if (TRUE == pstcAdcIrqCfg->bAdcHhtCmp)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcHhtIrq)
        {
            stcAdcIrqCalbaks.pfnAdcHhtIrq = pstcAdcIrqCalbaks->pfnAdcHhtIrq;
        }
    }

    if (TRUE == pstcAdcIrqCfg->bAdcLltCmp)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcLltIrq)
        {
            stcAdcIrqCalbaks.pfnAdcLltIrq = pstcAdcIrqCalbaks->pfnAdcLltIrq;
        }
    }
}

/**
 * \brief   
 *          ??????ADC????????????
 *
 * \param   [in]  pstcAdcIrqState  ADC??????????????????
 *
 * \retval  ???
 */
void Adc_GetIrqState(stc_adc_irq_t* pstcAdcIrqState)
{
    pstcAdcIrqState->bAdcIrq = M0P_ADC->IFR_f.CONT_INTF;
    pstcAdcIrqState->bAdcRegCmp = M0P_ADC->IFR_f.REG_INTF;
    pstcAdcIrqState->bAdcHhtCmp = M0P_ADC->IFR_f.HHT_INTF;
    pstcAdcIrqState->bAdcLltCmp = M0P_ADC->IFR_f.LLT_INTF;
}

/**
 * \brief   
 *          ??????ADC CONT????????????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_ClrContIrqState(void)
{
    M0P_ADC->ICLR = ~(1<<3);
}

/**
 * \brief   
 *          ??????ADC REG????????????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_ClrRegIrqState(void)
{
    M0P_ADC->ICLR = ~(1<<2);
}

/**
 * \brief   
 *          ??????ADC HHT????????????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_ClrHhtIrqState(void)
{
    M0P_ADC->ICLR = ~(1<<1);
}

/**
 * \brief   
 *          ??????ADC LLT????????????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_ClrIrqLltState(void)
{
    M0P_ADC->ICLR = ~1;
}


/**
 * \brief   
 *          ADC????????????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_EnableIrq(void)
{
    M0P_ADC->CR0_f.IE = 1u;
}

/**
 * \brief   
 *          ADC????????????
 *
 * \param   [in]  pstcAdcIrqCfg  ADC????????????
 *
 * \retval  ???
 */
void Adc_CmpCfg(stc_adc_irq_t* pstcAdcIrqCfg)
{
    if (TRUE == pstcAdcIrqCfg->bAdcRegCmp)
    {
        M0P_ADC->CR1_f.REGCMP = 1u;
    }
    else
    {
        M0P_ADC->CR1_f.REGCMP = 0u;
    }

    if (TRUE == pstcAdcIrqCfg->bAdcHhtCmp)
    {
        M0P_ADC->CR1_f.HTCMP = 1u;
    }
    else
    {
        M0P_ADC->CR1_f.HTCMP = 0u;
    }

    if (TRUE == pstcAdcIrqCfg->bAdcLltCmp)
    {
        M0P_ADC->CR1_f.LTCMP = 1u;
    }
    else
    {
        M0P_ADC->CR1_f.LTCMP = 0u;
    }

    AdcEnableNvic(ADC_IRQn);
}

/**
 * \brief   
 *          ADC????????????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_DisableIrq(void)
{
    uint32_t u32Cr1;
    
    M0P_ADC->CR0_f.IE = 0u;
    
    u32Cr1 = M0P_ADC->CR1 | (1<<15);    // must write 1 to bit 15 to avoid clear ADC_result_acc
    u32Cr1 &= ~((1u<<12)|(1u<<13)|(1u<<14));
    M0P_ADC->CR1 = u32Cr1;
    AdcDisableNvic(ADC_IRQn);
}

/**
 * \brief   
 *          ADC?????????
 *
 * \param   [in]  pstcAdcConfig  ADC????????????
 *
 * \retval  en_result_t  Ok:  ????????????
 * \retval  en_result_t  ErrorInvalidParameter: ????????????
 */
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcConfig)
{
    if (NULL == pstcAdcConfig)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR0_f.CLKSEL = pstcAdcConfig->enAdcClkSel;
    M0P_ADC->CR0_f.SAM = pstcAdcConfig->enAdcSampTimeSel;
    M0P_ADC->CR0_f.SREF = pstcAdcConfig->enAdcRefVolSel;
    M0P_ADC->CR0_f.BUFEN = pstcAdcConfig->bAdcInBufEn;
    M0P_ADC->HT_f.HT = pstcAdcConfig->u32AdcRegHighThd;
    M0P_ADC->LT_f.LT = pstcAdcConfig->u32AdcRegLowThd;
    M0P_ADC->CR1_f.TRIGS0 = pstcAdcConfig->enAdcTrig0Sel;
    M0P_ADC->CR1_f.TRIGS1 = pstcAdcConfig->enAdcTrig1Sel;
    M0P_ADC->CR0_f.IE = 0u;
    M0P_ADC->CR1_f.REGCMP = 0u;
    M0P_ADC->CR1_f.HTCMP = 0u;
    M0P_ADC->CR1_f.LTCMP = 0u;

    return Ok;
}

/**
 * \brief   
 *          ADC Deinit
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_DeInit(void)
{
    AdcDisableNvic(ADC_IRQn);

    M0P_ADC->CR0_f.ADCEN = 0u;

    M0P_ADC->CR0_f.IE = 0u;
    M0P_ADC->CR1_f.REGCMP = 0u;
    M0P_ADC->CR1_f.HTCMP = 0u;
    M0P_ADC->CR1_f.LTCMP = 0u;
    M0P_ADC->ICLR_f.CONT_INTC = 0u;
    M0P_ADC->ICLR_f.REG_INTC = 0u;
    M0P_ADC->ICLR_f.HHT_INTC = 0u;
    M0P_ADC->ICLR_f.LLT_INTC = 0u;

    M0P_ADC->CR0_f.CLKSEL = 0u;
    M0P_ADC->CR0_f.SAM = 0x2u;
    M0P_ADC->CR0_f.SREF = 0x3u;
    M0P_ADC->CR0_f.SEL = 0xFu;
    M0P_ADC->CR0_f.BUFEN = 0u;
    M0P_ADC->HT_f.HT = 0xFFFu;
    M0P_ADC->LT_f.LT = 0u;
    M0P_ADC->CR1_f.TRIGS0 = 0u;
    M0P_ADC->CR1_f.TRIGS1 = 0u;
}

/**
 * \brief   
 *          ADC????????????
 *
 * \param   ???
 *
 * \retval  ???
 */

void Adc_Start(void)
{
    M0P_ADC->ICLR_f.CONT_INTC = 0u;
    M0P_ADC->CR0_f.STATERST = 1u;
    M0P_ADC->CR0_f.START = 1u;
}

/**
 * \brief   
 *          ADC????????????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_Stop(void)
{
    M0P_ADC->CR0_f.START = 0u;
}

/**
 * \brief   
 *          ADC??????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_Enable(void)
{
    M0P_ADC->CR0_f.ADCEN = 1u;
}

/**
 * \brief   
 *          ADC??????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_Disable(void)
{
    M0P_ADC->CR0_f.ADCEN = 0u;
}

/**
 * \brief   
 *          ????????????????????????
 *
 * \param   [in]  pstcAdcConfig   ADC????????????
 * \param   [in]  pstcAdcNormCfg  ??????????????????????????????
 *
 * \retval  en_result_t  Ok:  ????????????
 * \retval  en_result_t  ErrorInvalidParameter: ????????????
 */
en_result_t Adc_ConfigNormMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_norm_cfg_t* pstcAdcNormCfg)
{
    if ((NULL == pstcAdcNormCfg) || (NULL == pstcAdcConfig))
    {
        return ErrorInvalidParameter;
    }

    pstcAdcConfig->enAdcOpMode = AdcNormalMode;
    M0P_ADC->CR1_f.CT = 0u;
    M0P_ADC->CR0_f.SEL = pstcAdcNormCfg->enAdcNormModeCh;
    M0P_ADC->CR1_f.RACC_EN = pstcAdcNormCfg->bAdcResultAccEn;

    return Ok;
}

/**
 * \brief   
 *          ????????????????????????
 *
 * \param   [in]  pstcAdcConfig   ADC????????????
 * \param   [in]  pstcAdcNormCfg  ??????????????????????????????
 *
 * \retval  en_result_t  Ok:  ????????????
 * \retval  en_result_t  ErrorInvalidParameter: ????????????
 */
en_result_t Adc_ConfigContMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_cont_cfg_t* pstcAdcContCfg)
{
    if ((NULL == pstcAdcContCfg) || (NULL == pstcAdcConfig))
    {
        return ErrorInvalidParameter;
    }

    pstcAdcConfig->enAdcOpMode = AdcContMode;
    M0P_ADC->CR1_f.CT = 1u;
    M0P_ADC->CR0_f.SEL = pstcAdcContCfg->enAdcContModeCh;
    M0P_ADC->CR1_f.RACC_EN = pstcAdcContCfg->bAdcResultAccEn;
    if (pstcAdcContCfg->bAdcResultAccEn)
    {
        M0P_ADC->CR1_f.RACC_CLR = 1u;
    }
    M0P_ADC->CR2 = 1<<pstcAdcContCfg->enAdcContModeCh;
    M0P_ADC->CR2_f.ADCCNT = pstcAdcContCfg->u8AdcSampCnt;

    return Ok;
}

/**
 * \brief   
 *          ????????????????????????
 *
 * \param   [in]  pstcAdcConfig   ADC????????????
 * \param   [in]  pstcAdcNormCfg  ??????????????????????????????
 *
 * \retval  en_result_t  Ok:  ????????????
 * \retval  en_result_t  ErrorInvalidParameter: ????????????
 */
en_result_t Adc_ConfigScanMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_scan_cfg_t* pstcAdcScanCfg)
{
    if ((NULL == pstcAdcScanCfg) || (NULL == pstcAdcConfig))
    {
        return ErrorInvalidParameter;
    }

    pstcAdcConfig->enAdcOpMode = AdcScanMode;
    M0P_ADC->CR1_f.CT = 1u;
    M0P_ADC->CR2 = pstcAdcScanCfg->u8AdcScanModeCh;
    M0P_ADC->CR2_f.ADCCNT = pstcAdcScanCfg->u8AdcSampCnt;

    return Ok;
}

/**
 * \brief   
 *          ??????ADC????????????
 *
 * \param   none
 *
 * \retval  boolean_t  TRUE:  ADC?????????
 * \retval  boolean_t  FALSE: ADC????????????
 */
boolean_t Adc_PollBusyState(void)
{
    return M0P_ADC->CR0_f.START;
}

/**
 * \brief   
 *          ???????????????
 *
 * \param   [out] pu16AdcResult  ???????????????
 *
 * \retval  en_result_t  Ok:  ??????
 * \retval  en_result_t  ErrorInvalidParameter: ????????????
 */
en_result_t Adc_GetResult(uint16_t* pu16AdcResult)
{
    if (NULL == pu16AdcResult)
    {
        return ErrorInvalidParameter;
    }

    *pu16AdcResult = M0P_ADC->RESULT_f.RESULT;

    return Ok;
}

/**
 * \brief   
 *          ?????????????????????
 *
 * \param   [out] pu32AdcAccResult  ?????????????????????
 *
 * \retval  en_result_t  Ok:  ??????
 * \retval  en_result_t  ErrorInvalidParameter: ????????????
 */
en_result_t Adc_GetAccResult(uint32_t* pu32AdcAccResult)
{
    if (NULL == pu32AdcAccResult)
    {
        return ErrorInvalidParameter;
    }

    *pu32AdcAccResult = M0P_ADC->RESULT_ACC_f.RESULT_ACC;

    return Ok;
}

/**
 * \brief   
 *          ?????????????????????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Adc_ClrAccResult(void)
{
    M0P_ADC->CR1_f.RACC_CLR = 0u;
}

/**
 * \brief   
 *          ???????????????????????????????????????????????????
 *
 * \param   [in]  u8Channel  ?????????
 * \param   [out] pu16AdcResult  ???????????????
 *
 * \retval  en_result_t  Ok:  ??????
 * \retval  en_result_t  ErrorInvalidParameter: ????????????
 */
en_result_t Adc_GetScanResult(uint8_t u8Channel, uint16_t* pu16AdcResult)
{
    if (NULL == pu16AdcResult)
    {
        return ErrorInvalidParameter;
    }

    switch (u8Channel)
    {
        case AdcExInputCH0:
            *pu16AdcResult = M0P_ADC->RESULT0_f.RESULT0;
            break;
        case AdcExInputCH1:
            *pu16AdcResult = M0P_ADC->RESULT1_f.RESULT1;
            break;
        case AdcExInputCH2:
            *pu16AdcResult = M0P_ADC->RESULT2_f.RESULT2;
            break;
        case AdcExInputCH3:
            *pu16AdcResult = M0P_ADC->RESULT3_f.RESULT3;
            break;
        case AdcExInputCH4:
            *pu16AdcResult = M0P_ADC->RESULT4_f.RESULT4;
            break;
        case AdcExInputCH5:
            *pu16AdcResult = M0P_ADC->RESULT5_f.RESULT5;
            break;
        case AdcExInputCH6:
            *pu16AdcResult = M0P_ADC->RESULT6_f.RESULT6;
            break;
        case AdcExInputCH7:
            *pu16AdcResult = M0P_ADC->RESULT7_f.RESULT7;
            break;
        default:
            return ErrorInvalidParameter;
    }
    return Ok;
}
/**
 * \brief   
 *          ??????ch8????????????
 * \param   [out] pu16AdcResult  ???????????????
 *
 * \retval  en_result_t  Ok:  ??????
 * \retval  en_result_t  ErrorInvalidParameter: ????????????
 */
en_result_t Adc_GetCH8Result(uint16_t* pu16AdcResult)
{  
    if (NULL == pu16AdcResult)
    {
        return ErrorInvalidParameter;
    }   
    *pu16AdcResult = M0P_ADC->RESULT8_f.RESULT8;
    return Ok;   
}

/**
 * \brief   
 *          ??????ADC????????????
 *
 * \param   [in]  enAdcRefVolSel  ADC????????????
 *
 * \retval  en_result_t  Ok:  ????????????
 * \retval  en_result_t  ErrorInvalidParameter: ????????????
 */
en_result_t Adc_SetVref(en_adc_ref_vol_sel_t enAdcRefVolSel)
{
    if (enAdcRefVolSel > RefVolSelAVDD)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR0_f.SREF = enAdcRefVolSel;
    return Ok;
}

//@} // AdcGroup


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

