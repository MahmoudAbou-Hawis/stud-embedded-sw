/******************************************************************************/
/**
 * @file Timer0.h
 * @brief Atmega32P Timer0 implemention in C language
 *
 * @par Project Name
 *  Timer0 driver
 *
 * @par Code Language
 * C
 *
 * @par Description
 * this driver makes for control Counter0 in AtMega32p
 * 
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "Timer1.h"
#include "string.h"
#include "Uart.h"
#include <util/delay.h>
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

/**
 * @brief refer to the base of Timer 1

*/
#define TIMER1_BASE ((tstTimer1Reg*)0x6F)
/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/
/**
 * @brief refer to Timer registers
*/
typedef struct 
{
    uint8 u8TIMSK1;
    uint8 u8Reseved1[16];
    uint8 u8TCCR1A;
    uint8 u8TCCR1B;
    uint8 u8TCCR1C;
    uint8 u8Reseved2;
    uint16 u16TCNT;
    uint16 u16ICR1;
    uint16 u16OCR1A;
    uint16 u16OCR1B;

} tstTimer1Reg;

/**
 * @brief refer to Timer periphral requirements inputs
*/
typedef struct 
{
    tstTimer1Reg* pstTimer1Regs;
    uint16 u16prscaler;
    void (*pfnCallback0)(void*);
    void* pvArgs0;

} tstTimer1Hnd;

static tstTimer1Hnd stTimer0Hnd =
{
    .pstTimer1Regs = TIMER1_BASE,
    .u16prscaler = 0,
    .pvArgs0 = NULL,
    .pfnCallback0 = NULL
};
/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION PROTOTYPES */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/

void Timer0_vInit(Timer1_tstConfig* pstConfig)
{
    if(pstConfig->enmMode == TIMER1_NORTMAL)
    {
        stTimer0Hnd.pstTimer1Regs->u8TCCR1A = 0;
        stTimer0Hnd.pstTimer1Regs->u8TCCR1B = 0;
    }
    else if(pstConfig->enmMode == TIMER1_FAST_PWM)
    {
        stTimer0Hnd.pstTimer1Regs->u8TCCR1A  = 3;
        stTimer0Hnd.pstTimer1Regs->u8TCCR1B  = (1<<3);
    }
    else
    {
        stTimer0Hnd.pstTimer1Regs->u8TCCR1A = 0;
        stTimer0Hnd.pstTimer1Regs->u8TCCR1B = 0x08;
    }

    if(pstConfig->enmInterrupt == TIMER1_INTERRUPT_ON)
    {
        stTimer0Hnd.pstTimer1Regs->u8TIMSK1 = 2;
    }
    stTimer0Hnd.u16prscaler = pstConfig->u16prescaler;
}


void Timer0_vSetPayload(uint16 u16Payload)
{

    stTimer0Hnd.pstTimer1Regs->u16OCR1A = u16Payload;
}

void Timer0_vSetCallbackFunc(void (*pfnCallback)(void*), void* pvArgs)
{
    stTimer0Hnd.pfnCallback0 = pfnCallback;
    stTimer0Hnd.pvArgs0 = pvArgs;
}


void Timer0_vEnable(void)
{
    stTimer0Hnd.pstTimer1Regs->u8TCCR1B |= stTimer0Hnd.u16prscaler; 
}

void Timer0_vDisable(void)
{
    stTimer0Hnd.pstTimer1Regs->u8TCCR1B |= 0xF8;
}

ISR(TIMER1_COMPA_vect)
{
    if((*(stTimer0Hnd.pfnCallback0))!= NULL)
    {
        (*(stTimer0Hnd.pfnCallback0))(stTimer0Hnd.pvArgs0);
    }
}

/******************************************************************************/