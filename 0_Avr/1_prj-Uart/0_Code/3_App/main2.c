#include "StdTypes.h"
#include <stdint.h>
#include <util/delay.h>

#define F_CLK      16000000.0

#define UART0_BASE (0xC0)
#define TR_UART0 ((tstUartHandle*)UART0_BASE)
typedef struct
{

    volatile uint8 u8UcsrA;

    volatile uint8 u8UcsrB;

    volatile uint8 u8UcsrC;

    volatile uint8 u8Dummy1;

    volatile uint16 u16Ubrr;

    volatile uint8 u8Udr;

} tstUartHandle;


void UART_Init(void)
{
    TR_UART0->u16Ubrr = ((F_CLK/(16*(uint32)9600)) -1);
    TR_UART0->u8UcsrB |= (1<<3) | (1<<4);
    TR_UART0->u8UcsrC |= (3<<1);
}

void UART_TransmitByte(uint8 Byte){
    while(!(TR_UART0->u8UcsrA&(1<<5)));
    TR_UART0->u8Udr = Byte;
}

uint8 UART_ReceiveByte(void){
    while(!(TR_UART0->u8UcsrA&(1<<7)));
    return TR_UART0->u8Udr;
}

int main()
{
    /* main function */
    UART_Init();
    /* Program loop*/
    while(1)
    {
    /*Recieveing data And Transmit it Again */
     UART_TransmitByte(UART_ReceiveByte());
     _delay_ms(1000);   
    }

    return 0;
}
