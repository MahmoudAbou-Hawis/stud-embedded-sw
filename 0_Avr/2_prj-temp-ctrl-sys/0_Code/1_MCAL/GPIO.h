
/*  Multiple Inclusion Guard */
#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdint.h>
#include "StdTypes.h"

#define PORTB_BASE ((uint8)0x23)
#define PORTC_BASE ((uint8)0x26)
#define PORTD_BASE ((uint8)0x29)

#define GPIO_B ((Gpio_tstPort *)PORTB_BASE)
#define GPIO_C ((Gpio_tstPort *)PORTC_BASE)
#define GPIO_D ((Gpio_tstPort *)PORTD_BASE)

typedef enum
{
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
    GPIO_INPUT_PULLUP

} GPIO_tenmGPIOPinDir;

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

void Gpio_vPinMode(Gpio_tstPort *pPort, uint8 u8Bit, GPIO_tenmGPIOPinDir EnmPinDir);
void Gpio_vDigitalWrite(Gpio_tstPort *pPort, uint8 u8Bit, Gpio_tenmLevel EnmAct);
Gpio_tenmLevel Gpio_enmPinStaus(Gpio_tstPort *pPort, uint8 u8Bit);
void Gpio_vPinModePort(Gpio_tstPort *pPort, uint8 u8PortMask);
void Gpio_vConfigurePullUps(Gpio_tstPort *pPort, uint8 u8InputPullupMask);
void Gpio_vDigitalWritePort(Gpio_tstPort *pPort, uint8 u8Mask);

#endif
