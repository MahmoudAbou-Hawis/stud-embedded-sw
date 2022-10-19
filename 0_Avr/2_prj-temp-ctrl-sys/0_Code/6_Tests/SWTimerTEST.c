
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_SWTIMER)
//#include "Terminal.h"
#include "Uart.h"
#include "GPIO.h"
#include <stdio.h>
#include "swTimer.h"
#include <util/delay.h>
#include <avr/interrupt.h>

/* main function */
bool flag = TRUE;
void Mode(void * ptr)
{
    Gpio_vDigitalWrite(GPIO_B,1,flag);
}
void CallBack(void* args)
{
    *((boolean*)args) = !(*((boolean*)args));
}
int main()
{
    Gpio_vPinMode(GPIO_B,1,GPIO_OUTPUT);
    SW_Timer_vInit(6250,SW_TIMER_PRESCALER_256);
    SW_Timer_pvMakeTimwr(1,Mode,NULL);
    SW_Timer_pvMakeTimwr(10,CallBack,&flag);
    return 0;
}

#endif