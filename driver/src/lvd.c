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
/** \file lvd.c
 **
 ** Low Voltage Detect driver API.
 ** @link Lvd Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "lvd.h"

/**
 ******************************************************************************
 ** \addtogroup LvdGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define IS_VALID_INPUT(x)       ( (x) <= LvdInputP25 )

#define IS_VALID_THRESHOLD(x)   ( (x) <= LvdTH3p3V )

#define IS_VALID_FILTER(x)      ( (x) <= LvdFilter29ms )

#define IS_VALID_IRQTYPE(x)     ( (x) <= LvdIrqFall )


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
// static void LvdEnableNvic(void);
// static void LvdDisableNvic(void);
// static en_result_t LvdEnable(en_lvd_type_t enType, boolean_t bFlag);

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static func_ptr_t    pfnLvdIrqCbk;

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

 /**
 * \brief   
 *          LVD??????????????????
 *
 * \param   [in]  u8Param  ?????????
 *
 * \retval  ???
 */
void Lvd_IRQHandler(uint8_t u8Param)
{
    M0P_LVD->IFR_f.INTF = 0u;
    if (NULL != pfnLvdIrqCbk)
    {
        pfnLvdIrqCbk();
    }
}

/**
 * \brief   
 *          ??????NVIC???LVD??????
 *
 * \param   ???
 *
 * \retval  ???
 */
static void LvdEnableNvic(void)
{
    NVIC_ClearPendingIRQ(LVD_IRQn);
    NVIC_SetPriority(LVD_IRQn, DDL_IRQ_LEVEL_DEFAULT);
    NVIC_EnableIRQ(LVD_IRQn);
}

/**
 * \brief   
 *          ??????NVIC???LVD??????
 *
 * \param   ???
 *
 * \retval  ???
 */
static void LvdDisableNvic(void)
{
    NVIC_ClearPendingIRQ(LVD_IRQn);
    NVIC_DisableIRQ(LVD_IRQn);
    NVIC_SetPriority(LVD_IRQn, DDL_IRQ_LEVEL_DEFAULT);
}

/**
 * \brief   
 *          ??????LVD??????
 *
 * \param   [in]  enType  LVD????????????
 *
 * \retval  en_result_t  Ok:  ????????????
 * \retval  en_result_t  ErrorInvalidParameter:  ????????????
 */
en_result_t Lvd_EnableIrq(en_lvd_irq_type_t enType)
{
    en_result_t enRet = Ok;

    if (enType > LvdIrqFall)
    {
        return ErrorInvalidParameter;
    }
    else
    {   switch (enType)
        {
            case LvdIrqHigh:
                M0P_LVD->CR_f.HTEN = 1u;
                M0P_LVD->CR_f.RTEN = 0u;
                M0P_LVD->CR_f.FTEN = 0u;
                break;
            case LvdIrqRise:
                M0P_LVD->CR_f.HTEN = 0u;
                M0P_LVD->CR_f.RTEN = 1u;
                M0P_LVD->CR_f.FTEN = 0u;
                break;
            case LvdIrqFall:
                M0P_LVD->CR_f.HTEN = 0u;
                M0P_LVD->CR_f.RTEN = 0u;
                M0P_LVD->CR_f.FTEN = 1u;
                break;
            default:
                break;
        }

        M0P_LVD->CR_f.IE = 1u;
        LvdEnableNvic();
    }
    return enRet;
}

/**
 * \brief   
 *          ??????LVD??????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Lvd_DisableIrq(void)
{
    LvdDisableNvic();
    M0P_LVD->CR_f.IE = 0u;
    M0P_LVD->CR_f.HTEN = 0u;
    M0P_LVD->CR_f.RTEN = 0u;
    M0P_LVD->CR_f.FTEN = 0u;
}

/**
 * \brief   
 *          LVD?????????
 *
 * \param   [in]  pstcConfig  LVD????????????
 *
 * \retval  ???
 */
void Lvd_Init(stc_lvd_config_t *pstcConfig)
{
    ASSERT(pstcConfig);
    ASSERT(IS_VALID_INPUT(pstcConfig->enInput));
    ASSERT(IS_VALID_THRESHOLD(pstcConfig->enThreshold));
    ASSERT(IS_VALID_FILTER(pstcConfig->enFilterTime));
    ASSERT(IS_VALID_IRQTYPE(pstcConfig->enIrqType));

    //NEED to DISABLE first.
    Lvd_Disable();
    Lvd_DisableIrq();
    LvdDisableNvic();

    M0P_LVD->CR_f.DEBOUNCE_TIME = pstcConfig->enFilterTime;
    M0P_LVD->CR_f.FLTEN = pstcConfig->bFilter;
    M0P_LVD->CR_f.VTDS = pstcConfig->enThreshold;
    M0P_LVD->CR_f.SOURCE_SEL = pstcConfig->enInput;
    M0P_LVD->CR_f.ACT = pstcConfig->bLvdReset;

    pfnLvdIrqCbk = pstcConfig->pfnIrqCbk;
}

/**
 * \brief   
 *          LVD deinit
 *
 * \param   ???
 *
 * \retval  ???
 */
void Lvd_DeInit(void)
{
    Lvd_DisableIrq();
    LvdDisableNvic();

    pfnLvdIrqCbk = NULL;
    Lvd_Disable();
}

/**
 * \brief   
 *          ??????LVD
 *
 * \param   ???
 *
 * \retval  ???
 *
 */
void Lvd_Enable(void)
{
    M0P_LVD->CR_f.LVDEN = 1u;
}

/**
 * \brief   
 *          ??????LVD
 *
 * \param   ???
 *
 * \retval  ???
 */
void Lvd_Disable(void)
{
    M0P_LVD->CR_f.LVDEN = 0u;
}

/**
 * \brief   
 *          ??????LVD????????????
 *
 * \param   ???
 *
 * \retval  boolean_t  ????????????
 */
boolean_t Lvd_GetIntrStat(void)
{
    return M0P_LVD->IFR_f.INTF;

}

/**
 * \brief   
 *          ??????LVD????????????
 *
 * \param   ???
 *
 * \retval  ???
 */
void Lvd_ClearIrq(void)
{
    M0P_LVD->IFR_f.INTF = 0u;
}


//@} // LvdGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

