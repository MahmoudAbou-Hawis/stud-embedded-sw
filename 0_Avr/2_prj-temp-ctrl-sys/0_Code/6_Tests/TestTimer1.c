
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_TIMER1)

//#include "Terminal.h"
#include "GPIO.h"
#include "Timer0.h"
#include "ADC.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void CallBack(void* args)
{
    // *((boolean*)args) ^= 1;
    *((boolean*)args) = !(*((boolean*)args));
}

/* main function */
int main()
{
    Gpio_vPinMode(GPIO_B,1,GPIO_OUTPUT);
    boolean flag = TRUE;
    Timer0_tstConfig config =
    {
        .enmInterrupt = TIMER0_INTERRUPT_ON,
        .enmMode      = TIMER0_CTC,
        .u16prescaler = TIMER0_PRESCALER_1024
    };
    sei();
    Timer0_vInit(&config);
    Timer0_vSetPayload(15625);
    Timer0_vSetCallbackFunc(CallBack,&flag);
    Timer0_vEnable();

    while (TRUE)
    {
        Gpio_vDigitalWrite(GPIO_B,1,flag);
    }
    
   
    return 0;
}

#endif