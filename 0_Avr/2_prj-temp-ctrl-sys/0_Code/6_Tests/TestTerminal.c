
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_TEST_TERMINAL)

#include "StdTypes.h"
#include <stdint.h>
#include "Uart.h"
#include "Terminal.h"
#include "GPIO.h"
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

    uint8 au8MyBuff[30] = {0};

    void vCheckSlash(void* pvBuff, uint16 u8Len)
    {
        if (((uint8*)pvBuff)[0] != ';')
        {
            if (((uint8*)pvBuff) - ((uint8*)pvBuff) != 30)
            {
                Uart_vReceiveBuffInterrupt((void*)(pvBuff+1), 1, vCheckSlash);
                
            }
            else
            {
                Uart_vReceiveBuffInterrupt((void*)au8MyBuff, 1, vCheckSlash);
            }
        }
        else
        {
           ((uint8*)pvBuff+1)[0] = '\0';
            Uart_vReceiveBuffInterrupt((void*)au8MyBuff, 1, vCheckSlash);
        }
    }
/* main function */
int main()
{  
    /* Initialization */



    /* UART stConfigrations   */
    Uart_tstInitConfig stConfigrations;
    stConfigrations.enmCharSize     = UART_SIZE_8;
    stConfigrations.enmParityType   = UART_PARITY_NONE;
    stConfigrations.u32BaudRate     = 9600;
    stConfigrations.u32SystemClock  = 16000000.0;
    stConfigrations.u8Direction     = UART_DIR_TX | UART_DIR_RX ;
    stConfigrations.u8InterruptType = UART_INTERRUPT_RX | UART_INTERRUPT_TX;
    stConfigrations.enmStopBits     = UART_STOP_1;

    Uart_vReceiveBuffInterrupt((void*)au8MyBuff, 1, vCheckSlash);
  _delay_ms(4000);
  Uart_vTransmitBuff(au8MyBuff , u16length(au8MyBuff),NULL);
    /* Program loop*/
    while(1)
    {
      

    }

    return 0;
}

#endif
