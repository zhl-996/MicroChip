/******************************************************************************
*Copyright(C)2017, Xiaohua Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Xiaohua Semiconductor Co.,Ltd("XHSC").
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

/** \file crc.c
 **
 ** Common API of crc.
 ** @link crcGroup Some description @endlink
 **
 **   - 2017-05-16
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "crc.h"
/**
 *******************************************************************************
 ** \addtogroup CrcGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *****************************************************************************
 ** \brief CRC16 ??????(??????????????????)
 **
 ** ???????????????????????????CRC16??????.
 **
 ** \param [in]  pu8Data          ?????????????????????????????????????????????
 ** \param [in]  u32Len           ????????????????????????????????????
 ** 
 ** \retval CRC16                 CRC16?????????.                                
 *****************************************************************************/
uint16_t CRC16_Get8(uint8_t* pu8Data, uint32_t u32Len)
{
    uint32_t u32Index;
    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(M0P_CRC->DATA_f))) = pu8Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 ??????(??????????????????)
 **
 ** ???????????????????????????CRC16??????.
 **
 ** \param [in]  pu16Data          ?????????????????????????????????????????????
 ** \param [in]  u32Len           ????????????????????????????????????
 ** 
 ** \retval CRC16                 CRC16?????????.                                
 *****************************************************************************/
uint16_t CRC16_Get16(uint16_t* pu16Data, uint32_t u32Len)
{
    uint32_t u32Index;
    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA_f))) = pu16Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 ??????(???????????????)
 **
 ** ???????????????????????????CRC16??????.
 **
 ** \param [in]  pu32Data          ??????????????????????????????????????????
 ** \param [in]  u32Len            ?????????????????????????????????
 ** 
 ** \retval CRC16                  CRC16?????????.                                
 *****************************************************************************/
uint16_t CRC16_Get32(uint32_t* pu32Data, uint32_t u32Len)
{
    uint32_t u32Index;
    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 ??????(??????????????????)
 **
 ** ?????????????????????????????????CRC16???????????????.
 **
 ** \param [in]  pu8Data          ?????????????????????????????????????????????
 ** \param [in]  u32Len           ????????????????????????????????????
 ** \param [in]  u16CRC           ?????????CRC16???
 ** 
 ** \retval Ok                    CRC????????????
 ** \retval Error                 CRC????????????                                
 *****************************************************************************/
en_result_t CRC16_Check8(uint8_t* pu8Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index;
    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(M0P_CRC->DATA_f))) = pu8Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA_f))) = u16CRC;
    
    enResult = M0P_CRC->RESULT_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 ??????(??????????????????)
 **
 ** ?????????????????????????????????CRC16???????????????.
 **
 ** \param [in]  pu16Data         ?????????????????????????????????????????????
 ** \param [in]  u32Len           ????????????????????????????????????
 ** \param [in]  u16CRC           ?????????CRC16???
 ** 
 ** \retval Ok                    CRC????????????
 ** \retval Error                 CRC????????????                                
 *****************************************************************************/
en_result_t CRC16_Check16(uint16_t* pu16Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index;
    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA_f))) = pu16Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA_f))) = u16CRC;
    
    enResult = M0P_CRC->RESULT_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 ??????(???????????????)
 **
 ** ?????????????????????????????????CRC16???????????????.
 **
 ** \param [in]  pu32Data         ??????????????????????????????????????????
 ** \param [in]  u32Len           ?????????????????????????????????
 ** \param [in]  u16CRC           ?????????CRC16???
 ** 
 ** \retval Ok                    CRC????????????
 ** \retval Error                 CRC????????????                                
 *****************************************************************************/
en_result_t CRC16_Check32(uint32_t* pu32Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index;
    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(M0P_CRC->DATA_f))) = pu32Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA_f))) = u16CRC;
    
    enResult = M0P_CRC->RESULT_f.FLAG ? Ok : Error;
    
    return (enResult);
}


//@} // CrcGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
