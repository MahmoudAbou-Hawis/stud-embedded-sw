#include "GPIO.h"
#include "StdTypes.h"

void Gpio_vPinMode(Gpio_tstPort *pPort, uint8 u8Bit, GPIO_tenmGPIOPinDir EnmPinDir)
{
    if (EnmPinDir != GPIO_OUTPUT)
    {
        pPort->u8DirRegister &= ~(1 << u8Bit);
        if (EnmPinDir == GPIO_INPUT_PULLUP)
        {
            pPort->u8PortRegister |= (1 << u8Bit);
        }
        else
        {
            pPort->u8PortRegister &= ~(1 << u8Bit);
        }
    }
    else
    {
        pPort->u8DirRegister |= (1 << u8Bit);
    }
}

void Gpio_vPinModePort(Gpio_tstPort *pPort, uint8 u8PortMask)
{
    pPort->u8DirRegister = u8PortMask;
}

void Gpio_vConfigurePullUps(Gpio_tstPort *pPort, uint8 u8InputPullupMask)
{
    pPort->u8PortRegister = u8InputPullupMask;
}

void Gpio_vDigitalWrite(Gpio_tstPort *pPort, uint8 u8Bit, Gpio_tenmLevel EnmAct)
{
    if (EnmAct == GPIO_LEVEL_HIGH)
    {
        pPort->u8PortRegister |= (1 << u8Bit);
    }
    else
    {
        pPort->u8PortRegister &= ~(1 << u8Bit);
    }
}

void Gpio_vDigitalWritePort(Gpio_tstPort *pPort, uint8 u8Mask)
{
    pPort->u8PortRegister = u8Mask;
}

Gpio_tenmLevel Gpio_enmPinStaus(Gpio_tstPort *pPort, uint8 u8Bit)
{
    return pPort->u8PinRegister & (1 << u8Bit) ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW;
}
