#include "MyApplication.h"

void GPIOInit()
{	
		    //GPIO输出
    //初始化外部GPIO P03为输出、上拉、开漏，P03端口外接LED3
    Gpio_InitIOExt(0, 3, GpioDirOut, TRUE, FALSE, TRUE, FALSE);   //LED
    Gpio_InitIOExt(2, 5, GpioDirOut, TRUE, FALSE, TRUE, FALSE);   //8266_RST
    Gpio_InitIOExt(2, 6, GpioDirOut, TRUE, FALSE, TRUE, FALSE);   //8266_EN
		Gpio_InitIO(3, 4,GpioDirIn);
	
}
