#include "MyApplication.h"

void GPIOInit()
{	
		    //GPIO���
    //��ʼ���ⲿGPIO P03Ϊ�������������©��P03�˿����LED3
    Gpio_InitIOExt(0, 3, GpioDirOut, TRUE, FALSE, TRUE, FALSE);   //LED
    Gpio_InitIOExt(2, 5, GpioDirOut, TRUE, FALSE, TRUE, FALSE);   //8266_RST
    Gpio_InitIOExt(2, 6, GpioDirOut, TRUE, FALSE, TRUE, FALSE);   //8266_EN
		Gpio_InitIO(3, 4,GpioDirIn);
	
}
