#include <MyApplication.h>

#define     T1_PORT                 (3)
#define     T1_PIN                  (3)

uint8_t u8RxFlg=0;
uint8_t CheckFlg=0;

uint8_t u8RxData[2]={0x55,0x00};

unsigned int Usart2_RxCounter = 0;      //����һ����������¼����2�ܹ������˶����ֽڵ�����
char Usart2_RxBuff[USART2_RXBUFF_SIZE]; //����һ�����飬���ڱ��洮��2���յ�������   	
void Usart1RxCallback(void)
{

}
void ErrIntCallback(void)
{
  
}

void Usart0RxCallback(void)  //��8266ͨ��
{

  Usart2_RxBuff[Usart2_RxCounter]=M0P_UART0->SBUF;
	Usart2_RxCounter++;
	
}
void Uart1Init()
{
	
	  uint16_t timer=0;
    uint32_t pclk=0;
	
    stc_uart_config_t  stcConfig;
    stc_uart_irq_cb_t stcUartIrqCb;
    stc_uart_multimode_t stcMulti;
    stc_uart_baud_config_t stcBaud;
    stc_bt_config_t stcBtConfig;
	
	  DDL_ZERO_STRUCT(stcUartIrqCb);
    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
    DDL_ZERO_STRUCT(stcBtConfig);
	  
    Gpio_InitIOExt(2,3,GpioDirOut,TRUE,FALSE,FALSE,FALSE);   
    Gpio_InitIOExt(2,4,GpioDirOut,TRUE,FALSE,FALSE,FALSE); 
    
		
		 //ͨ���˿�����
    Gpio_SetFunc_UART1TX_P23();
    Gpio_SetFunc_UART1RX_P24();

    //����ʱ��ʹ��
    Clk_SetPeripheralGate(ClkPeripheralBt,TRUE);//ģʽ0/2���Բ�ʹ��
    Clk_SetPeripheralGate(ClkPeripheralUart1,TRUE);
		
		stcUartIrqCb.pfnRxIrqCb = Usart1RxCallback;
    stcUartIrqCb.pfnTxIrqCb = NULL;
    stcUartIrqCb.pfnRxErrIrqCb = ErrIntCallback;
    stcConfig.pstcIrqCb = &stcUartIrqCb;
    stcConfig.bTouchNvic = TRUE;
		
		stcConfig.enRunMode = UartMode1;//��������Ĵ˴���ת��4��ģʽ����
   

    stcMulti.enMulti_mode = UartNormal;//��������Ĵ˴���ת��������ģʽ��mode2/3���ж�����ģʽ

    stcConfig.pstcMultiMode = &stcMulti;

    stcBaud.bDbaud = 0u;//˫�������ʹ���
    stcBaud.u32Baud = 9600u;//���²�����λ��
    stcBaud.u8Mode = UartMode1; //���㲨������Ҫģʽ����
    pclk = Clk_GetPClkFreq();
    timer=Uart_SetBaudRate(UARTCH1,pclk,&stcBaud);

    stcBtConfig.enMD = BtMode2;
    stcBtConfig.enCT = BtTimer;
    Bt_Init(TIM1, &stcBtConfig);//����basetimer1���ú�������������
    Bt_ARRSet(TIM1,timer);
    Bt_Cnt16Set(TIM1,timer);
    Bt_Run(TIM1);

    Uart_Init(UARTCH1, &stcConfig);
    Uart_EnableIrq(UARTCH1,UartRxIrq);
    Uart_ClrStatus(UARTCH1,UartRxFull);
    Uart_EnableFunc(UARTCH1,UartRx);
}

void Uart0Init()
{
	
	  uint16_t timer=0;
    uint32_t pclk=0;
	
    stc_uart_config_t  stcConfig;
    stc_uart_irq_cb_t stcUartIrqCb;
    stc_uart_multimode_t stcMulti;
    stc_uart_baud_config_t stcBaud;
    stc_bt_config_t stcBtConfig;
	
	  DDL_ZERO_STRUCT(stcUartIrqCb);
    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
    DDL_ZERO_STRUCT(stcBtConfig);
	

    
    Gpio_InitIOExt(3,5,GpioDirOut,TRUE,FALSE,FALSE,FALSE);   
    Gpio_InitIOExt(3,6,GpioDirOut,TRUE,FALSE,FALSE,FALSE); 
    
		
		 //ͨ���˿�����
    Gpio_SetFunc_UART0TX_P35();
    Gpio_SetFunc_UART0RX_P36();

    //����ʱ��ʹ��
    Clk_SetPeripheralGate(ClkPeripheralBt,TRUE);//ģʽ0/2���Բ�ʹ��
    Clk_SetPeripheralGate(ClkPeripheralUart0,TRUE);
		
		stcUartIrqCb.pfnRxIrqCb = Usart0RxCallback;
    stcUartIrqCb.pfnTxIrqCb = NULL;
    stcUartIrqCb.pfnRxErrIrqCb = ErrIntCallback;
    stcConfig.pstcIrqCb = &stcUartIrqCb;
    stcConfig.bTouchNvic = TRUE;
		
		stcConfig.enRunMode = UartMode1;//��������Ĵ˴���ת��4��ģʽ����
   

    stcMulti.enMulti_mode = UartNormal;//��������Ĵ˴���ת��������ģʽ��mode2/3���ж�����ģʽ

    stcConfig.pstcMultiMode = &stcMulti;

    stcBaud.bDbaud = 0u;//˫�������ʹ���
    stcBaud.u32Baud = 9600u;//���²�����λ��
    stcBaud.u8Mode = UartMode1; //���㲨������Ҫģʽ����
    pclk = Clk_GetPClkFreq();
    timer=Uart_SetBaudRate(UARTCH0,pclk,&stcBaud);

    stcBtConfig.enMD = BtMode2;
    stcBtConfig.enCT = BtTimer;
    Bt_Init(TIM0, &stcBtConfig);//����basetimer1���ú�������������
    Bt_ARRSet(TIM0,timer);
    Bt_Cnt16Set(TIM0,timer);
    Bt_Run(TIM0);

    Uart_Init(UARTCH0, &stcConfig);
    Uart_EnableIrq(UARTCH0,UartRxIrq);
    Uart_ClrStatus(UARTCH0,UartRxFull);
    Uart_EnableFunc(UARTCH0,UartRx);
}

/*
	* @name   fputc
	* @brief  fputcӳ��������
	* @param  ch -> �������ַ�
	* @retval ch -> �ѷ����ַ�      
*/
int fputc(int ch,FILE* f)
{

	Uart_SendData(UARTCH1,ch);			

	return ch;
}



