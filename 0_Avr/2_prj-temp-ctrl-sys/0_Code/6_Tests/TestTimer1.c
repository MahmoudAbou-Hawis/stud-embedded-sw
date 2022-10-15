
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_TIMER1)

//#include "Terminal.h"
#include "GPIO.h"
#include "Timer1.h"
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
    Timer1_tstConfig config =
    {
        .enmInterrupt = TIMER1_INTERRUPT_ON,
        .enmMode      = TIMER1_CTC,
        .u16prescaler = TIMER1_PRESCALER_1024
    };
    sei();
    Timer1_vInit(&config);
    Timer1_vSetPayload(15625);
    Timer1_vSetCallbackFunc(CallBack,&flag);
    Timer1_vEnable();

    while (TRUE)
    {
        Gpio_vDigitalWrite(GPIO_B,1,flag);
    }
    
   
    return 0;
}

#endif