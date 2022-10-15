
#include "AppCfg.h"
#if CFG_IS_CURRENT_APP(CFG_APP_MAIN)
#include "Terminal.h"
#include "Uart.h"
#include "GPIO.h"
#include "ADC.h"
#include "I2C.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Timer0.h"
/* main function */
bool flag = true ;

void CallBack(void * Buff ,uint16 u16Length)
{
    (((uint8*)Buff)[0] ^=1); 
}
int main()
{
  Gpio_vPinMode(GPIO_B,1,GPIO_OUTPUT);
  sei();
  uint8 buff[1] = {'1'};
  TIMER0_enmInterMode t = TIMER0_INTERRUPT_ON;
  TIMER0_enmMODE m = TIMER_CTC;
  Timer0_vSetCallBack((void*)buff,1,CallBack);
  Timer0_vInit(m,t);
  Timer0_vSetPeriod(1000);
  while (1)
  {
    Gpio_vDigitalWrite(GPIO_B,1,buff[0]-'0');
    /* code */

  }
  
    /*

      */
      /*Terminal Initialization */
      //Terminal_vInit();
    

      /* Program loop*/
      // while(1)
      // {
      //       /*Termainal Main Function*/
      //       Terminal_vMain();
      // }
      
    return 0;
}




#endif