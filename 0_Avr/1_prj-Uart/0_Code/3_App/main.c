
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_MAIN)
#include "Terminal.h"
#include "Uart.h"
#include "GPIO.h"
#include <util/delay.h>
#include <avr/interrupt.h>

/* main function */
int main()
{
      /*Terminal Initialization */
      Terminal_vInit();
    

      /* Program loop*/
      while(1)
      {
            /*Termainal Main Function*/
            Terminal_vMain();
      }

    return 0;
}




#endif
