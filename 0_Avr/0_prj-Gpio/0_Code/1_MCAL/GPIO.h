
/*  Multiple Inclusion Guard */
#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdint.h>
#include "StdTypes.h"

#define PORTB_BASE ((uint8)0x23)
#define PORTC_BASE ((uint8)0x26)
#define PORTD_BASE ((uint8)0x29)

#define GPIO_B ((GPIO *)PORTB_BASE)
#define GPIO_C ((GPIO *)PORTC_BASE)
#define GPIO_D ((GPIO *)PORTD_BASE)

typedef enum
{
    INPUT = 0,
    OUTPUT = 1,
    INPUT_PULLUP

} GPIO_tenmGPIOPinDir;

typedef enum
{
    LOW = 0,
    HIGH = 1

} GPIO_tenmAction;

typedef enum
{

    GPIO_LEVEL_LOW = 0,
    GPIO_LEVEL_HIGH = 1

} Gpio_tenmLevel;

typedef struct
{
    volatile uint8 u8PinRegister;
    volatile uint8 u8DirRegister;
    volatile uint8 u8PortRegister;

} Gpio_tstPort;

void PinMode(GPIO *pBort, uint8 u8Bit, GPIOTenmGPIOPinDir EnmPinDir);
void DigitalWrite(GPIO *pBort, uint8 u8Bit, GPIOAction EnmAct);
GPIOPinLevel PinStaus(GPIO *pBort, uint8 u8Bit);
void pinModePort(GPIO *pBort, uint8 u8PortMask);
void configurePullUps(GPIO *pBort, uint8 u8InputPullupMask);
void DigitalWritePort(GPIO *pBort, uint8 u8Mask);

#endif
