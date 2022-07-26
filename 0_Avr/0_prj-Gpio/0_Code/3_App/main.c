#include "GPIO.h"
#include <stdint.h>
#include <util/delay.h>


#define BUTTON_PIN     2
#define LED_PIN        5

int main()
{
    /* This program should blink pin 13 of Arduino Uno  when pressing button */

    /* Initialization */
    Gpio_vPinMode(GPIO_B, LED_PIN, GPIO_OUTPUT);
    Gpio_vPinMode(GPIO_C, BUTTON_PIN, GPIO_INPUT);

    /* Program Loop */
    while (1)
    {
        if(Gpio_enmPinStaus(GPIO_C, BUTTON_PIN))
        {
            Gpio_vDigitalWrite(GPIO_B, LED_PIN, GPIO_LEVEL_HIGH);         
        }
        else
        {
            Gpio_vDigitalWrite(GPIO_B, LED_PIN, GPIO_LEVEL_LOW);
        }
    }

    return 0;
}
