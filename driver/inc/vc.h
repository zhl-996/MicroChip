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
/** \file vc.h
 **
 ** Headerfile for Voltage Comparator functions
 ** @link VC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

#ifndef __VC_H__
#define __VC_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup VcGroup Voltage Comparator (VC)
 **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief VC??????
 *****************************************************************************/
typedef enum en_vc_channel
{
    VcChannel0,                 ///< ??????0
    VcChannel1,                 ///< ??????1
}en_vc_channel_t;


/**
 ******************************************************************************
 ** \brief VC??????
 *****************************************************************************/
typedef enum en_vc_cmp_delay
{
    VcDelayoff,             ///< ????????????
    VcDelay10mv,            ///< ??????10mv
    VcDelay20mv,            ///< ??????20mv
    VcDelay30mv,            ///< ??????30mv
}en_vc_cmp_delay_t;

/**
 ******************************************************************************
 ** \brief VC????????????
 *****************************************************************************/
typedef enum en_vc_bias_current
{
    VcBias300na,            ///< ????????????300na
    VcBias1200na,           ///< ????????????1.2ua
    VcBias10ua,             ///< ????????????10ua
    VcBias20ua,             ///< ????????????20ua
}en_vc_bias_current_t;

/**
 ******************************************************************************
 ** \brief VC??????????????????
 *****************************************************************************/
typedef enum en_vc_resp_filter
{
    VcFilter7us,            ///< ??????????????????7us
    VcFilter14us,           ///< ??????????????????14us
    VcFilter28us,           ///< ??????????????????28us
    VcFilter112us,          ///< ??????????????????112us
    VcFilter450us,          ///< ??????????????????450us
    VcFilter1800us,         ///< ??????????????????1.8ms
    VcFilter7200us,         ///< ??????????????????7.2ms
    VcFilter28800us,        ///< ??????????????????28.8ms
}en_vc_resp_filter_t;

/**
 ******************************************************************************
 ** \brief VC P?????????
 *****************************************************************************/
typedef enum en_vc_input_p_src
{
    VcInPCh0,                ///< ????????????0 P2.3
    VcInPCh1,                ///< ????????????1 P2.5
    VcInPCh2,                ///< ????????????2 P3.2
    VcInPCh3,                ///< ????????????3 P3.3
    VcInPCh4,                ///< ????????????4 P3.4
    VcInPCh5,                ///< ????????????5 P3.5
    VcInPCh6,                ///< ????????????6 P3.6
    VcInPCh7,                ///< ????????????7 P0.1
}en_vc_input_p_src_t;

/**
 ******************************************************************************
 ** \brief VC N?????????
 *****************************************************************************/
typedef enum en_vc_input_n_src
{
    VcInNCh0,         ///< ????????????0 P2.3
    VcInNCh1,         ///< ????????????1 P2.5
    VcInNCh2,         ///< ????????????2 P3.2
    VcInNCh3,         ///< ????????????3 P3.3
    VcInNCh4,         ///< ????????????4 P3.4
    VcInNCh5,         ///< ????????????5 P3.5
    VcInNCh6,         ///< ????????????6 P3.6
    VcInNCh7,         ///< ????????????7 P0.1
    ResDivOut,        ///< Vcc??????
    AiTs,             ///< ???????????????
    AiBg1p2,          ///< BGR 1.2V
    AiVcRef2p5,       ///< REF 2.5V
    AiLdo,            ///< LDO
}en_vc_input_n_src_t;

/**
 ******************************************************************************
 ** \brief VC??????????????????
 *****************************************************************************/
typedef enum en_vc_irq_sel
{
    VcIrqRise,            ///< ???????????????
    VcIrqFall,            ///< ???????????????
    VcIrqHigh,            ///< ???????????????
    VcIrqNone,            ///< ?????????
}en_vc_irq_sel_t;

/**
 ******************************************************************************
 ** \brief VC??????
 *****************************************************************************/
typedef enum en_vc_stat
{
    VcCmpResult,                ///< VC??????????????????
    VcIntrResult,               ///< VC????????????
}en_vc_stat_t;

/**
 ******************************************************************************
 ** \brief VC????????????
 *****************************************************************************/
typedef enum en_vc_output_config
{
    VcOutInvTimer,              ///< ????????????????????????Timer0,1,2,3
    VcOutTm0Gate,               ///< ?????????????????????TM0 Gate
    VcOutTm1Gate,               ///< ?????????????????????TM1 Gate
    VcOutTm2Gate,               ///< ?????????????????????TM2 Gate
    VcOutTm3Gate,               ///< ?????????????????????LPTIMER3 Gate
    VcOutTm3ExtClk,             ///< ?????????????????????LPTIMER ????????????
    VcOutInvPca,                ///< ?????????????????????PCA
    VcOutPcaCap0,               ///< ?????????????????????PCA ????????????0
    VcOutPcaExtClk,             ///< ?????????????????????PCA ????????????
    VcOutInvTm4,                ///< ?????????????????????Timer4
    VcOutTm4,                   ///< ?????????????????????TM4 ????????????
    VcOutInvTm5,                ///< ?????????????????????Timer5
    VcOutTm5,                   ///< ?????????????????????TM5 ????????????
    VcOutInvTm6,                ///< ?????????????????????Timer6
    VcOutTm6,                   ///< ?????????????????????TM6 ????????????
    VcOutBrake,                 ///< ????????????
    VcOutDisable,               ///< ??????????????????
}en_vc_output_config_t;

/**
 ******************************************************************************
 ** \brief VC DIV????????????Vref??????
 *****************************************************************************/
typedef enum en_vc_div_vref
{
    VcDivVrefAvcc,              ///< AVCC
    VcDivVrefAdc,               ///< ADC_CR0 SREF??????????????????
}en_vc_div_vref_t;

/**
 ******************************************************************************
 ** \brief VC????????????
 *****************************************************************************/
typedef struct stc_vc_general_config
{
    boolean_t           bDivEn;       ///< ??????/?????? 6-bit VCC divider
    uint8_t             u8DivVal;     ///< 6-bit VCC divider?????????
    en_vc_div_vref_t    enDivVref;    ///< 6-bit VCC divider????????????????????????
}stc_vc_general_config_t;

/**
 ******************************************************************************
 ** \brief VC????????????
 *****************************************************************************/
typedef struct stc_vc_channel_config
{
    en_vc_channel_t         enVcChannel;        ///< VC????????????
    en_vc_cmp_delay_t       enVcCmpDly;         ///< VC??????
    en_vc_bias_current_t    enVcBiasCurrent;    ///< VC????????????
    en_vc_resp_filter_t     enVcFilterTime;     ///< ??????????????????
    en_vc_input_p_src_t     enVcInPin_P;        ///< P?????????
    en_vc_input_n_src_t     enVcInPin_N;        ///< N?????????
    en_vc_output_config_t   enVcOutConfig;      ///< ????????????
    en_vc_irq_sel_t         enVcIrqSel;         ///< ??????????????????
    func_ptr_t              pfnAnalogCmpCb;     ///< ??????????????????
}stc_vc_channel_config_t;

/******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//get stat
boolean_t Vc_GetStat(en_vc_channel_t enChannel, en_vc_stat_t enStat);
//clear stat
void Vc_ClearIrq(en_vc_channel_t enChannel);

//irq enable/disable
en_result_t Vc_EnableIrq(en_vc_channel_t enChannel);
en_result_t Vc_DisableIrq(en_vc_channel_t enChannel);
en_result_t Vc_ConfigIrq(en_vc_channel_t enChannel, en_vc_irq_sel_t enSel);

//VC init/deinit
en_result_t Vc_GeneralInit(stc_vc_general_config_t *pstcGeneralConfig);
void Vc_GeneralDeInit(void);
en_result_t Vc_ChannelInit(en_vc_channel_t enChannel,
                            stc_vc_channel_config_t *pstcChannelConfig);
en_result_t Vc_ChannelDeInit(en_vc_channel_t enChannel);

//VC function enable/disable
en_result_t Vc_EnableChannel(en_vc_channel_t enChannel);
en_result_t Vc_DisableChannel(en_vc_channel_t enChannel);

//VC filter enable/disable
en_result_t Vc_EnableFilter(en_vc_channel_t enChannel);
en_result_t Vc_DisableFilter(en_vc_channel_t enChannel);

//@} // VcGroup

#ifdef __cplusplus
}
#endif

#endif /* __VC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

