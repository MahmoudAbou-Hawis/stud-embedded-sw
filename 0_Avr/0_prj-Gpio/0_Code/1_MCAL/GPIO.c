#include "GPIO.h"

void Pin_mode(GPIO* port, uint8_t _bit, GPIO_tenmGpioPinDir enmPinDir)
{
    if(enmPinDir != Output)
    {
        port->dDirRegister &= ~(1 << _bit);
        if(enmPinDir == Input_Pullup)
        {
            port->portRegister |= (1 << _bit);
        }
        else
        {
            port->portRegister &= ~(1 << _bit);
        }
    }
    else
    {
       port->dDirRegister |= (1 << _bit);
    }
}

void pinModePort(GPIO* port, uint8_t PortMask)
{
   port->dDirRegister = PortMask;
}

void configurePullUps(GPIO* port, uint8_t Input_Pullup_Mask)
{
    port->portRegister = Input_Pullup_Mask;
}

void digital_write(GPIO* port, uint8_t _bit, GPIO_action enmAct)
{
    if(enmAct == High)
    {
        port->portRegister |= (1 <<_bit);
    }
    else
    {
        port->portRegister &= ~(1 << _bit);
    }
}

void digital_writePort(GPIO* port, uint8_t Mask)
{
    port->portRegister = Mask;
}

GPIO_PinLevel pinStaus(GPIO* port, uint8_t _bit)
{
    return port->pinRegister &(1 << _bit) ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW ;
}
