#include "GPIO.h"
#include <util/delay.h>


#define BUTTON_PIN     2
#define LED_PIN        5

int main()
{
    /* This program should blink pin 13 of Arduino Uno  when pressing button */

    /* Initialization */
    Pin_mode(GPIO_B, LED_PIN, Output);
    Pin_mode(GPIO_C, BUTTON_PIN, Input);

    /* Program Loop */
    while (1)
    {
        if(pinStaus(GPIO_C, BUTTON_PIN))
        {
            digital_write(GPIO_B, LED_PIN, High);
        }
        else
        {
            digital_write(GPIO_B, LED_PIN, Low);
        }
    }

    return 0;
}
