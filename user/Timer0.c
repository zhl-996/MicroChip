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


en_result_t Timer2Init(void)  //��ʱ��0��ʼ��
{
    stc_bt_config_t   stcConfig;
    en_result_t       enResult = Error;
    uint16_t          u16ArrData = 0x10000 - 10000;
    uint16_t          u16InitCntData = 0x10000 - 10000;
    
    stcConfig.pfnTim2Cb = Bt2Int;

      
    stcConfig.enGate  = BtGateDisable;  //�رն�ʱ���ſ�
    stcConfig.enPRS   = BtPCLKDiv8;    //Ԥ����   500khz
    stcConfig.enTog   = BtTogDisable;		//�رշ�ת���
    stcConfig.enCT    = BtTimer;				//��ʱ������
    stcConfig.enMD    = BtMode2;				//�Զ���װ��16λ��ʱ��
    //Bt��ʼ��
    if (Ok != Bt_Init(TIM2, &stcConfig))
    {
        enResult = Error;
    }
    
    //TIM2�ж�ʹ��
    Bt_ClearIntFlag(TIM2);
    Bt_EnableIrq(TIM2);
    EnableNvic(TIM2_IRQn, 2, TRUE);
    
    //��������ֵ�ͼ���ֵ����������
    Bt_ARRSet(TIM2, u16ArrData);
    Bt_Cnt16Set(TIM2, u16InitCntData);
    Bt_Run(TIM2);
    
  
    
    return enResult;
}
