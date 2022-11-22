#ifndef __MYUART_H
#define __MYUART_H

#include "ddl.h"
#define USART2_RXBUFF_SIZE   1024              //定义串口2 接收缓冲区大小 1024字节

extern unsigned int Usart2_RxCounter;          //外部声明，其他文件可以调用该变量
extern char Usart2_RxBuff[USART2_RXBUFF_SIZE]; //外部声明，其他文件可以调用该变量
extern uint8_t u8RxData[2];

void Uart1Init(void);
void Uart0Init(void);

void RxIntCallback(void);
void ErrIntCallback(void);
#endif
