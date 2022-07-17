#include "StdTypes.h"
#include <stdint.h>
#include "Uart.h"
#include <util/delay.h>


int main()
{
    /* UART Configrations   */
    Uart_tstInitConfig Configrations;
    Configrations.enmCharSize     = UART_SIZE_8;
    Configrations.enmParityType   = UART_PARITY_NONE;
    Configrations.u32BaudRate     = 9600;
    Configrations.u32SystemClock  = 16000000.0;
    Configrations.u8Direction     = UART_DIR_TX | UART_DIR_RX ;
    Configrations.u8InterruptType = UART_INTERRUPT_NONE;
    Configrations.enmStopBits     = UART_STOP_1;
    /* main function */
    Uart_vInit(&Configrations);
    /* Program loop*/
    while(1)
    {
    /*Transmit it Buffer */
     uint8 arr[3] = {'A' , 'B' , 'C'};
     Uart_vTransmitBuff(arr,3,NULL);
     _delay_ms(1000);   
    }

    return 0;
}
