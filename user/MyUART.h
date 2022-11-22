#ifndef __MYUART_H
#define __MYUART_H

#include "ddl.h"
#define USART2_RXBUFF_SIZE   1024              //���崮��2 ���ջ�������С 1024�ֽ�

extern unsigned int Usart2_RxCounter;          //�ⲿ�����������ļ����Ե��øñ���
extern char Usart2_RxBuff[USART2_RXBUFF_SIZE]; //�ⲿ�����������ļ����Ե��øñ���
extern uint8_t u8RxData[2];

void Uart1Init(void);
void Uart0Init(void);

void RxIntCallback(void);
void ErrIntCallback(void);
#endif
