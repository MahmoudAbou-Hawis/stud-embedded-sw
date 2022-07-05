#include "GPIO.h"
#include "StdTypes.h"

void PinMode(Gpio_tstPort *pBort, uint8 u8Bit, GPIO_tenmGPIOPinDir EnmPinDir)
{
    if (EnmPinDir != GPIO_OUTPUT)
    {
        pBort->u8DirRegister &= ~(1 << u8Bit);
        if (EnmPinDir == GPIO_INPUT_PULLUP)
        {
            pBort->u8PortRegister |= (1 << u8Bit);
        }
        else
        {
            pBort->u8PortRegister &= ~(1 << u8Bit);
        }
    }
    else
    {
        pBort->u8DirRegister |= (1 << u8Bit);
    }
}

void pinModePort(Gpio_tstPort *pBort, uint8 u8PortMask)
{
    pBort->u8DirRegister = u8PortMask;
}

void configurePullUps(Gpio_tstPort *pBort, uint8 u8InputPullupMask)
{
    pBort->u8PortRegister = u8InputPullupMask;
}

void DigitalWrite(Gpio_tstPort *pBort, uint8 u8Bit, GPIO_tenmAction EnmAct)
{
    if (EnmAct == HIGH)
    {
        pBort->u8PortRegister |= (1 << u8Bit);
    }
    else
    {
        pBort->u8PortRegister &= ~(1 << u8Bit);
    }
}

void DigitalWritePort(Gpio_tstPort *pBort, uint8 u8Mask)
{
    pBort->u8PortRegister = u8Mask;
}

Gpio_tenmLevel PinStaus(Gpio_tstPort *pBort, uint8 u8Bit)
{
    return pBort->u8PinRegister & (1 << u8Bit) ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW;
}
