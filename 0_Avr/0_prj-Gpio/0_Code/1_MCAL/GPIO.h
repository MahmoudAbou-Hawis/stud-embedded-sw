
/*  Multiple Inclusion Guard */
#ifndef GPIO_H
#define GPIO_H



#include <stdio.h>
#include <stdint.h>
#include "/home/sofar/stud-embedded-sw/0_Avr/0_prj-Gpio/0_Code/4_Libraries/StdTypes.h"


#define PORTB_BASE ((uint8_t)0x23)
#define PORTC_BASE ((uint8_t)0x26)
#define PORTD_BASE ((uint8_t)0x29)

#define GPIO_B ((GPIO*)PORTB_BASE)
#define GPIO_C ((GPIO*)PORTC_BASE)
#define GPIO_D ((GPIO*)PORTD_BASE)

typedef enum
{
    Input  = 0,
    Output = 1,
    Input_Pullup

} GPIO_tenmGpioPinDir;

typedef enum
{
    Low  = 0,
    High = 1

} GPIO_action;


typedef enum
{

    GPIO_LEVEL_LOW  = 0,
    GPIO_LEVEL_HIGH = 1

} GPIO_PinLevel;

typedef struct
{
   volatile uint8 pinRegister;
   volatile uint8 dDirRegister;
   volatile uint8 portRegister;

} GPIO;

void Pin_mode(GPIO* port , uint8 _bit , GPIO_tenmGpioPinDir enmPinDir);
void digital_write(GPIO* port , uint8 _bit ,GPIO_action enmAct);
GPIO_PinLevel pinStaus(GPIO* port , uint8 _bit);
void pinModePort(GPIO* port, uint8 PortMask);
void configurePullUps(GPIO* port, uint8 Input_Pullup_Mask);
void digital_writePort(GPIO* port , uint8 Mask);




#endif
