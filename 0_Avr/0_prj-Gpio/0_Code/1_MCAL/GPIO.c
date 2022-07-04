#include "GPIO.h"
#include "/home/sofar/stud-embedded-sw/0_Avr/0_prj-Gpio/0_Code/4_Libraries/StdTypes.h"

void PinMode(GPIO *pBort, uint8 u8Bit, GPIOTenmGPIOPinDir EnmPinDir)
{
    if (EnmPinDir != Output)
    {
        pBort->u8dDirRegister &= ~(1 << u8Bit);
        if (EnmPinDir == InputPullup)
        {
            pBort->u8portRegister |= (1 << u8Bit);
        }
        else
        {
            pBort->u8portRegister &= ~(1 << u8Bit);
        }
    }
    else
    {
        pBort->u8dDirRegister |= (1 << u8Bit);
    }
}

void pinModePort(GPIO *pBort, uint8 u8PortMask)
{
    pBort->u8dDirRegister = u8PortMask;
}

void configurePullUps(GPIO *pBort, uint8 u8InputPullupMask)
{
    pBort->u8portRegister = u8InputPullupMask;
}

void DigitalWrite(GPIO *pBort, uint8 u8Bit, GPIOAction EnmAct)
{
    if (EnmAct == High)
    {
        pBort->u8portRegister |= (1 << u8Bit);
    }
    else
    {
        pBort->u8portRegister &= ~(1 << u8Bit);
    }
}

void DigitalWritePort(GPIO *pBort, uint8 u8Mask)
{
    pBort->u8portRegister = u8Mask;
}

GPIOPinLevel PinStaus(GPIO *pBort, uint8 u8Bit)
{
    return pBort->u8pinRegister & (1 << u8Bit) ? GPIOLevelHigh : GPIOLevelLow;
}
