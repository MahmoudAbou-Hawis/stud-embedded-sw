#include "GPIO.h"

void Pin_mode(GPIO* port , uint8_t _bit ,GPIO_tenmGpioPinDir enmPinDir)
{
    if(enmPinDir==Input)
        port->dDirRegister&=~(1<<_bit);
    else
        port->dDirRegister|=(1<<_bit);
}

void digital_write(GPIO* port , uint8_t _bit ,GPIO_action enmAct)
{
    if(enmAct==High)
        port->portRegister|=(1<<_bit);
    else
        port->portRegister&=~(1<<_bit);
}