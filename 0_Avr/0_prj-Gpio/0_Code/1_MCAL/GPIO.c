#include "GPIO.h"
#include "/home/sofar/stud-embedded-sw/0_Avr/0_prj-Gpio/0_Code/4_Libraries/StdTypes.h"

void PinMode(GPIO* port, uint8 _bit, GPIO_tenmGpioPinDir enmPinDir)
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

void pinModePort(GPIO* port, uint8 PortMask)
{
   port->dDirRegister = PortMask;
}

void configurePullUps(GPIO* port, uint8 Input_Pullup_Mask)
{
    port->portRegister = Input_Pullup_Mask;
}

void digitalWrite(GPIO* port, uint8 _bit, GPIO_action enmAct)
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

void digital_writePort(GPIO* port, uint8 Mask)
{
    port->portRegister = Mask;
}

GPIO_PinLevel pinStaus(GPIO* port, uint8 _bit)
{
    return port->pinRegister &(1 << _bit) ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW ;
}
