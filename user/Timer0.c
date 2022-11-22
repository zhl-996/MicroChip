#include <MyApplication.h>
uint16_t Timer2_CNT;

void Bt2Int(void)
{
    if (TRUE == Bt_GetIntFlag(TIM2))
    {
        Bt_ClearIntFlag(TIM2);
				Timer2_CNT++;
    }
}


en_result_t Timer2Init(void)  //定时器0初始化
{
    stc_bt_config_t   stcConfig;
    en_result_t       enResult = Error;
    uint16_t          u16ArrData = 0x10000 - 10000;
    uint16_t          u16InitCntData = 0x10000 - 10000;
    
    stcConfig.pfnTim2Cb = Bt2Int;

      
    stcConfig.enGate  = BtGateDisable;  //关闭定时器门控
    stcConfig.enPRS   = BtPCLKDiv8;    //预分配   500khz
    stcConfig.enTog   = BtTogDisable;		//关闭反转输出
    stcConfig.enCT    = BtTimer;				//定时器功能
    stcConfig.enMD    = BtMode2;				//自动重装载16位定时器
    //Bt初始化
    if (Ok != Bt_Init(TIM2, &stcConfig))
    {
        enResult = Error;
    }
    
    //TIM2中断使能
    Bt_ClearIntFlag(TIM2);
    Bt_EnableIrq(TIM2);
    EnableNvic(TIM2_IRQn, 2, TRUE);
    
    //设置重载值和计数值，启动计数
    Bt_ARRSet(TIM2, u16ArrData);
    Bt_Cnt16Set(TIM2, u16InitCntData);
    Bt_Run(TIM2);
    
  
    
    return enResult;
}
