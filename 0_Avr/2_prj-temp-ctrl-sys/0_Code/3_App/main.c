
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_MAIN)
//#include "Terminal.h"
#include "Uart.h"
#include "GPIO.h"
#include "ADC.h"
#include <util/delay.h>
#include <avr/interrupt.h>


/* main function */
int main()
{
    ADC_tstInitConfig ADCConf =
    {
      .enmInterruptType       = INTERRUPT_NONE ,
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
    .u8InterruptType = UART_INTERRUPT_RX | UART_INTERRUPT_TX,
    .enmStopBits     = UART_STOP_1

    };
    
    static void *pvUart;
    pvUart = Uart_pvInit(&stConfigrations);

    sei();
    ADC_vInit(&ADCConf);
    void* channal = ADC_pvCreateChannel(ADC0);
    uint8 buffer[4]={'-','-','-','-'};
    while(1)
    {
      int x =ADC_u16ReadTimeOut(channal,125,NULL);
      // int x = ADC_u16Read(channal,NULL);
      for(int i = 0 ; i < 4 ; i++)
      {
        buffer[i] = (x%10)+'0';
        x/=10;
      }
      for(int i = 0 ; i < 2 ; i++)
      {
        char temp = buffer[i];
        buffer[i] = buffer[3-i];
        buffer[3-i] = temp;
      }
      Uart_vTransmitBuffInterrupt(pvUart,buffer, 4, NULL);
      _delay_ms(200);
      Uart_vTransmitBuffInterrupt(pvUart,(void*)"\n", 1, NULL);
      _delay_ms(1000);
    }

    return 0;
}




#endif