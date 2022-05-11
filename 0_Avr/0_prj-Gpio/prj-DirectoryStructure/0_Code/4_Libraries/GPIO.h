#include <stdio.h>
#include <stdint.h>

#define PORTB_BASE ((uint8_t)0x23)
#define PORTC_BASE ((uint8_t)0x26)
#define PORTD_BASE ((uint8_t)0x29)
typedef struct
{
   volatile uint8_t pinRegister;
   volatile uint8_t dDirRegister;
   volatile uint8_t portRegister;
} GPIO;

#define GPIO_B ((GPIO*)PORTB_BASE)
#define GPIO_C ((GPIO*)PORTC_BASE)
#define GPIO_D ((GPIO*)PORTD_BASE)

typedef enum
{
    Input  = 0,
    Output = 1
} GPIO_tenmGpioPinDir;

typedef enum
{
    Low  = 0,
    High = 1
} GPIO_action;

void Pin_mode(GPIO* port , uint8_t _bit , GPIO_tenmGpioPinDir enmPinDir);
void digital_write(GPIO* port , uint8_t _bit ,GPIO_action enmAct);