#include "GPIO.h"
#include <util/delay.h>


int main()
{
    /* This program should blink pin 13 of Arduino Uno */

    /* Initialization */
    Pin_mode(GPIO_B, 5, Output);

    /* Program Loop */
    while (1)
    {
        digital_write(GPIO_B,5,High);
        _delay_ms(1000);
        digital_write(GPIO_B,5,Low);
        _delay_ms(1000);
    }

    return 0;
}
