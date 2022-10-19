
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_SW_TIMER_2)
//#include "Terminal.h"
#include "Uart.h"
#include "GPIO.h"
#include <stdio.h>
#include "SwTimer.h"
#include <util/delay.h>
#include <avr/interrupt.h>

void *pvTaskToggle = NULL;
void *pvTaskToggle2 = NULL;
boolean bFlag2 = 0;
void * pvTaskPrint = NULL;
void *pvUart =NULL;
boolean bFlag = 0;

void vTaskToggle(void *pvArgs)
{
    bFlag ^= 1;

    Gpio_vDigitalWrite(GPIO_B, 1, bFlag);
}

void vTaskToggle2(void *pvArgs)
{
    bFlag2 ^= 1;

    Gpio_vDigitalWrite(GPIO_B, 5, bFlag2);
}
void vTaskSendHelloWolrld(void * pvArgs)
{
    Uart_vTransmitBuffInterrupt(pvUart ,(void*)"Hello World",11,NULL);
}
int main()
{
    Gpio_vPinMode(GPIO_B, 1, GPIO_OUTPUT);
    Gpio_vPinMode(GPIO_B, 7, GPIO_OUTPUT);

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

    SwTimer_vInit(15625, SW_TIMER_PRESCALER_1024);

    sei();

    SwTimer_tenmRetStatus enmRet = SwTimer_enmMakeTimer(&pvTaskToggle,1, vTaskToggle, NULL);
    
    if (enmRet == SW_TIMER_RET_STAT_ERR_FULL)
    {
        SwTimer_enmDeleteTimer(jgiktu);

        SwTimer_enmMakeTimer(&pvTaskToggle,1, vTaskToggle, NULL);
    }

    SwTimer_enmStart(pvTaskToggle);
    _delay_ms(5000);
    SwTimer_enmEnd(pvTaskToggle);
    _delay_ms(5000);
    SwTimer_enmStart(pvTaskToggle);
    SwTimer_enmMakeTimer(pvTaskToggle2,2, vTaskToggle2, NULL);
    SwTimer_enmMakeTimer(NULL,17, NULL, NULL);
    SwTimer_enmMakeTimer(NULL,12, NULL, NULL);
    SwTimer_enmMakeTimer( pvTaskPrint ,2, vTaskSendHelloWolrld, NULL);


    while (1);

    return 0;
}

#endif