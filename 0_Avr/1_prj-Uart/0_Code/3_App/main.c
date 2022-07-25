#include "StdTypes.h"
#include <stdint.h>
#include "Uart.h"
#include "GPIO.h"
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#define LED_PIN 5

#define UDR (*(volatile uint8*)0xC6)
 /*Global variable*/
bool LedStatus = false;
volatile uint8 result;

void func(void * buff , uint16 size)
{
    for(int i = 0 ; i < size ; i++)
    {
        ((uint8*)buff)[i] = (i+25+'0');
    }
}
int main()
{
    /* UART stConfigrations   */
    Uart_tstInitConfig stConfigrations;
    stConfigrations.enmCharSize     = UART_SIZE_8;
    stConfigrations.enmParityType   = UART_PARITY_NONE;
    stConfigrations.u32BaudRate     = 9600;
    stConfigrations.u32SystemClock  = 16000000.0;
    stConfigrations.u8Direction     = UART_DIR_TX | UART_DIR_RX ;
    stConfigrations.u8InterruptType = UART_INTERRUPT_TX ;
    stConfigrations.enmStopBits     = UART_STOP_1;
    /* main function */
    Uart_vInit(&stConfigrations);
    /* Program loop*/

     /*Global Interrupt Enable*/
    sei();
   
    /* Initialization */
    Gpio_vPinMode(GPIO_B, LED_PIN, GPIO_OUTPUT);
     uint8 arr[5]={'0','1','2','3','4'};
     
    while(1)
    {
    /*Transmit it Buffer With Interrupt*/
       Uart_vTransmitBuffInterrupt(arr,5,NULL);
     _delay_ms(100);
   
    }

    return 0;
}


