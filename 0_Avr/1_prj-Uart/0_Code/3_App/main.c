#include "StdTypes.h"
#include <stdint.h>
#include "Uart.h"
#include <util/delay.h>


int main()
{
    /* main function */
    UART_vInit();
    /* Program loop*/
    while(1)
    {
    /*Recieveing data And Transmit it Again */
     UART_vTransmitByte(UART_u8ReceiveByte());
     _delay_ms(1000);   
    }

    return 0;
}
