#ifndef __TIMER0_H
#define __TIMER0_H

#include "ddl.h"
typedef enum
{
	TIMER2_10mS  	= (uint16_t)1,
	TIMER2_50mS  	= (uint16_t)5,
	TIMER2_100mS	= (uint16_t)10,
	TIMER2_200mS	= (uint16_t)20,
	TIMER2_500mS	= (uint16_t)50,
	TIMER2_1S     = (uint16_t)100,
	TIMER2_2S     = (uint16_t)200,
	TIMER2_3S     = (uint16_t)300,
	TIMER2_5S     = (uint16_t)500,
	TIMER2_10S    = (uint16_t)1000,
	TIMER2_3min   = (uint16_t)18000,
}TIMER2_Value_t;

extern uint16_t Timer2_CNT;
en_result_t Timer2Init(void) ; //定时器0初始化;
#endif
