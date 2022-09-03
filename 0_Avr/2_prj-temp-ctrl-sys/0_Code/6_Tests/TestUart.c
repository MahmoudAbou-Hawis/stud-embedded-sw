
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_TEST_UART)
#include "Terminal.h"
#include "Uart.h"
#include "GPIO.h"
#include <util/delay.h>
#include <avr/interrupt.h>

void * address = NULL;

void vUartCallback(void* pvBuff, uint16 u16Len)
{
      Uart_vTransmitBuff(address, (void*)"Ok\n", 3, NULL);
}

/* main function */
int main()
{
     /*Terminal Initialization */
    // Terminal_vInit();
    Gpio_vPinMode(GPIO_B, 5, GPIO_OUTPUT);

    
      uint8 ReciveBuffer[3];  
      uint8 SendBuffer[3]={'a','b' ,'c'};
      Uart_tstInitConfig stConfigrations;

      stConfigrations.u8UartIdx       = 0;
      stConfigrations.enmCharSize     = UART_SIZE_8;
      stConfigrations.enmParityType   = UART_PARITY_NONE;
      stConfigrations.u32BaudRate     = 9600;
      stConfigrations.u32SystemClock  = 16000000.0;
      stConfigrations.u8Direction     = UART_DIR_TX | UART_DIR_RX;
      stConfigrations.u8InterruptType =  UART_INTERRUPT_TX | UART_INTERRUPT_RX ;
      stConfigrations.enmStopBits     = UART_STOP_1;
      address = Uart_pvInit(&stConfigrations);

      sei();
    Uart_vReceiveBuffInterrupt(address, ReciveBuffer, 3, vUartCallback);
 
    /* Program loop*/
    while(1)
    {
        Uart_vTransmitBuffInterrupt(address,(void*)"SOF",3,NULL);
        _delay_ms(1000);
    }

    return 0;
}




#endif
