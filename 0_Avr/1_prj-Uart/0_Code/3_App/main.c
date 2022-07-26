#include "StdTypes.h"
#include <stdint.h>
#include "Uart.h"
#include "Terminal.h"
#include "GPIO.h"
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#define RED_LED_PIN 0
#define Blue_LED_PIN 1
#define Green_LED_PIN 2 
 /*Global variable*/
bool LedStatus = false;
volatile uint8 result;

/* main function */
int main()
{
    /* UART stConfigrations   */
    Uart_tstInitConfig stConfigrations;
    stConfigrations.enmCharSize     = UART_SIZE_8;
    stConfigrations.enmParityType   = UART_PARITY_NONE;
    stConfigrations.u32BaudRate     = 9600;
    stConfigrations.u32SystemClock  = 16000000.0;
    stConfigrations.u8Direction     = UART_DIR_TX | UART_DIR_RX ;
    stConfigrations.u8InterruptType = UART_INTERRUPT_TX | UART_INTERRUPT_RX;
    stConfigrations.enmStopBits     = UART_STOP_1;

    Uart_vInit(&stConfigrations);

     /*Global Interrupt Enable*/
    sei();
   
    /* Initialization */
    uint8 Buffer[100]={'0'};
    uint8 command[30];
    uint8 procss[30];
    uint16 Numbers[30];
    uint8 signs[30];
    terminal_tstCalculator calculator;
    uint8 result[30];
    uint8 Serial[30];
    Gpio_vPinMode(GPIO_B,RED_LED_PIN,GPIO_LEVEL_HIGH);
    Gpio_vPinMode(GPIO_B,Green_LED_PIN,GPIO_LEVEL_HIGH);
    Gpio_vPinMode(GPIO_B,Blue_LED_PIN,GPIO_LEVEL_HIGH);
    Uart_vReceiveBuffInterrupt(Buffer,100,NULL);
    /* Program loop*/
    while(1)
    {

        if(Uart_readRecivedFlag()){
            terminal_vAnalsysOperand(Buffer,command,procss,(u16length(Buffer)-1));
            if(IsEqual("Cal" , command))
            {
                calculator.u16Size =  terminal_u16ProcessCalculatorSentData(procss,Numbers,signs,u16length(procss));
                calculator.u8ptrSigns=signs;
                calculator.u16ptrNumbers=Numbers;
                uint16 n =terminal_vCalculate(0,0,0,&calculator);
                Convert(n,result);
                Uart_vTransmitBuff(result,u16length(result),NULL);
                Uart_vTransmitBuff((void*)"\n",1,NULL);
            }
            else if(IsEqual("LED" , command))
            {
               if(IsEqual("RED",procss))
               {
                    Gpio_vDigitalWrite(GPIO_B,Green_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,Blue_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,RED_LED_PIN,GPIO_LEVEL_HIGH);
               }
               else if(IsEqual("GREEN",procss))
               {
                    Gpio_vDigitalWrite(GPIO_B,RED_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,Blue_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,Green_LED_PIN,GPIO_LEVEL_HIGH);
               }
               else if(IsEqual("BLUE",procss))
               {
                    Gpio_vDigitalWrite(GPIO_B,RED_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,Green_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,Blue_LED_PIN,GPIO_LEVEL_HIGH);
               }
               else if(IsEqual("TURQUOSE",procss))
               {
                    Gpio_vDigitalWrite(GPIO_B,RED_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,Green_LED_PIN,GPIO_LEVEL_HIGH);
                    Gpio_vDigitalWrite(GPIO_B,Blue_LED_PIN,GPIO_LEVEL_HIGH);
               }
               else if(IsEqual("ORANGE",procss))
               {
                    Gpio_vDigitalWrite(GPIO_B,RED_LED_PIN,GPIO_LEVEL_HIGH);
                    Gpio_vDigitalWrite(GPIO_B,Green_LED_PIN,GPIO_LEVEL_HIGH);
                    Gpio_vDigitalWrite(GPIO_B,Blue_LED_PIN,GPIO_LEVEL_LOW);
               }
               else if(IsEqual("PURPLE",procss))
               {
                    Gpio_vDigitalWrite(GPIO_B,RED_LED_PIN,GPIO_LEVEL_HIGH);
                    Gpio_vDigitalWrite(GPIO_B,Green_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,Blue_LED_PIN,GPIO_LEVEL_HIGH);
               }
               else if(IsEqual("WHITE",procss))
               {
                    Gpio_vDigitalWrite(GPIO_B,RED_LED_PIN,GPIO_LEVEL_HIGH);
                    Gpio_vDigitalWrite(GPIO_B,Green_LED_PIN,GPIO_LEVEL_HIGH);
                    Gpio_vDigitalWrite(GPIO_B,Blue_LED_PIN,GPIO_LEVEL_HIGH);
               }
               else if(IsEqual("OFF",procss))
               {
                    Gpio_vDigitalWrite(GPIO_B,RED_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,Green_LED_PIN,GPIO_LEVEL_LOW);
                    Gpio_vDigitalWrite(GPIO_B,Blue_LED_PIN,GPIO_LEVEL_LOW);
               }
                Uart_vTransmitBuff((void*)"ACK\n", 4, NULL);
            }
            else
            {
                if(IsEqual("SET",command))
                {
                    int i = 0;
                    for(;i<u16length(procss);i++)
                    {
                        Serial[i] = procss[i];
                    }
                    Serial[i]='\0';
                }
                else
                {
                  Uart_vTransmitBuff(Serial,u16length(Serial),NULL);
                }
            }
        }
    }

    return 0;
}


