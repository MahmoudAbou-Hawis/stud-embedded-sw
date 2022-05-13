#include "GPIO.h"
#include <util/delay.h>


int main()
{
    /* This program should blink pin 13 of Arduino Uno  when pressing button */

    /* Initialization */
    Pin_mode(GPIO_B, 5, Output);
    Pin_mode(GPIO_C,2,Input);

    /* Program Loop */
    while (1)
    {
        if(pinStaus(GPIO_C,2)){
        digital_write(GPIO_B,5,High);
        }else{
            digital_write(GPIO_B,5,Low);
        }
    }

    return 0;
}
