#include "GPIO.h"

void Pin_mode(GPIO* port , uint8_t _bit ,GPIO_tenmGpioPinDir enmPinDir)
{
    if(enmPinDir!=Output ){
        port->dDirRegister&=~(1<<_bit);
        if(enmPinDir == Input_Pullup)
            port->pinRegister|=(1<<_bit);
    }
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

GPIO_PinLevel pinStaus(GPIO* port , uint8_t _bit){
    return port->pinRegister &(1<<_bit) ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW ;
}