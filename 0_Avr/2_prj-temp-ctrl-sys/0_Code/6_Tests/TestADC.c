
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_TEST_ADC)
//#include "Terminal.h"
#include "Uart.h"
#include "GPIO.h"
#include "ADC.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

static void *pvUart = NULL;
int x = 0;

void vAdc0CallBack(uint16 u16AdcRaw)
{
    static char as16Out[6] = {0};
    sprintf(as16Out, "%05u\n", u16AdcRaw);
    Uart_vTransmitBuffInterrupt(pvUart,as16Out, 6, NULL);
}

/* main function */
int main()
{
    ADC_tstInitConfig ADCConf =
    {
      .enmInterruptType       = INTERRUPT_EN ,
      .enmVoltageReference    = Avcc ,
      .enmPrescalerSelections = Division_Factor_128  
    };
    Uart_tstInitConfig stConfigrations = {
    .u8UartIdx       = UART1,
    .enmCharSize     = UART_SIZE_8,
    .enmParityType   = UART_PARITY_NONE,
    .u32BaudRate     = 9600,
    .u32SystemClock  = 16000000.0,
    .u8Direction     = UART_DIR_TX | UART_DIR_RX ,
    .u8InterruptType = UART_INTERRUPT_TX | UART_INTERRUPT_RX,
    .enmStopBits     = UART_STOP_1

    };

    pvUart = Uart_pvInit(&stConfigrations);

    sei();
    ADC_vInit(&ADCConf);
    void* channal = ADC_pvCreateChannel(ADC7);
    while(1)
    {
    ADC_u16ReadInterrupt(channal,vAdc0CallBack);
    _delay_ms(1000);
    }

    return 0;
}




#endif