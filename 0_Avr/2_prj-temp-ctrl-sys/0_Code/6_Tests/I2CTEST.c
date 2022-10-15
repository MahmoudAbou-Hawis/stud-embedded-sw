
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_I2C)
//#include "Terminal.h"
#include "GPIO.h"
#include "I2C.h"
#include "ADC.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/* main function */
int main()
{
    I2C_tstInitConfigMaster config = 
    {
        .enmParserValue   = I2C_PARSER_VALUE_1,
        .u8BitRate        = ((16000000.0 / 100000UL) -16)/2
    };
    sei();
    I2C_vMasterInit(&config);
    uint8 arr[] = {0,200};
    I2C_vReceiveBuffInterruptMaster(arr,2,NULL,0x50);
    
    return 0;
    }

#endif