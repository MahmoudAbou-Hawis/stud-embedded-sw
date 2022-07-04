#include "GPIO.h"
#include <stdint.h>
#include <util/delay.h>


#define BUTTON_PIN     2
#define LED_PIN        5

int main()
{
    /* This program should blink pin 13 of Arduino Uno  when pressing button */

    /* Initialization */
    PinMode(GPIO_B, LED_PIN, Output);
    PinMode(GPIO_C, BUTTON_PIN, Input);

    /* Program Loop */
    while (1)
    {
        if(PinStaus(GPIO_C, BUTTON_PIN))
        {
            DigitalWrite(GPIO_B, LED_PIN, High);
        }
        else
        {
            DigitalWrite(GPIO_B, LED_PIN, Low);
        }
    }

    return 0;
}
