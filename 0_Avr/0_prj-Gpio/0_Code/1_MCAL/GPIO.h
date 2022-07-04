
/*  Multiple Inclusion Guard */
#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdint.h>
#include "/home/sofar/stud-embedded-sw/0_Avr/0_prj-Gpio/0_Code/4_Libraries/StdTypes.h"

#define PORTB_BASE ((uint8)0x23)
#define PORTC_BASE ((uint8)0x26)
#define PORTD_BASE ((uint8)0x29)

#define GPIO_B ((GPIO *)PORTB_BASE)
#define GPIO_C ((GPIO *)PORTC_BASE)
#define GPIO_D ((GPIO *)PORTD_BASE)

typedef enum
{
    Input = 0,
    Output = 1,
    InputPullup

} GPIOTenmGPIOPinDir;

typedef enum
{
    Low = 0,
    High = 1

} GPIOAction;

typedef enum
{

    GPIOLevelLow = 0,
    GPIOLevelHigh = 1

} GPIOPinLevel;

typedef struct
{
    volatile uint8 u8pinRegister;
    volatile uint8 u8dDirRegister;
    volatile uint8 u8portRegister;

} GPIO;

void PinMode(GPIO *pBort, uint8 u8Bit, GPIOTenmGPIOPinDir EnmPinDir);
void DigitalWrite(GPIO *pBort, uint8 u8Bit, GPIOAction EnmAct);
GPIOPinLevel PinStaus(GPIO *pBort, uint8 u8Bit);
void pinModePort(GPIO *pBort, uint8 u8PortMask);
void configurePullUps(GPIO *pBort, uint8 u8InputPullupMask);
void DigitalWritePort(GPIO *pBort, uint8 u8Mask);

#endif
