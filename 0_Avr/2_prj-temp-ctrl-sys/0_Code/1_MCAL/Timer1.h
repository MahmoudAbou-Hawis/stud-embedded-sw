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
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef Timer0_H
#define Timer0_H
/******************************************************************************/

/******************************************************************************/
/* C++ Style GUARD */
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "StdTypes.h"
#include <avr/interrupt.h>
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @brief Represents all of Modes you can use
*/

typedef enum
{
    /**
     * @brief This Mode Meaning you will use overflow mode
    */
    TIMER1_NORTMAL,

    /**
     * @brief represent to PWM mode
    */

    TIMER1_FAST_PWM,
    /**
     * @brief represent to CTC mode
    */
    TIMER1_CTC

} TIMER1_enmMode;

typedef enum
{
    /**
    * @brief represt to enable timer one interrupt
    */
    TIMER1_INTERRUPT_ON,
    /**
    * @brief represt to disable timer one interrupt
    */
    TIMER1_INTERRUPT_NONE
    
} TIMER0_enmInterMode;
/**
 * @brief represnt to prescalers you can use in timer 1
*/
typedef enum 
{
    /**
     * @brief it will make the prescaler 1024
    */

    TIMER1_PRESCALER_1024 = 0x05,

    /**
     * @brief it will make the prescaler 256
    */

    TIMER1_PRESCALER_256 = 0x04,

    /**
     * @brief it will make the prescaler 64
    */

    TIMER1_PRESCALER_64 = 0x03,

    /**
    * @brief it will make the prescaler 8
    */

    TIMER1_PRESCALER_8 = 0x02,
    /**
     * @brief it will make the prescaler 1
    */
    TIMER1_PRESCALER_1 = 0x01

} TIMER1_enmPrescaler;

/**
 * @brief represent to the configration of timer 1
*/

typedef struct
{
    /**
     * @brief represent to Mode which you want
     * it can be :
     *  TIMER1_NORTMAL
     *  TIMER1_CTC
     *  TIMER1_FAST_PWM
    */
    TIMER1_enmMode enmMode;
    /**
     * @brief represent to interrupt mode which you want 
     * it can be :
     * TIMER1_INTERRUPT_ON
     * TIMER1_INTERRUPT_NONE
    */

    TIMER1_enmInterMode enmInterrupt;
    /**
     * @brief represent to prescaler which you want to use 
     * it can be :
     * TIMER1_PRESCALER_1024 
     * .
     * .
     * .
     * TIMER1_PRESCALER_1
    */
    uint16 u16prescaler;

} Timer1_tstConfig;

/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DECLARATIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DECLARATIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION PROTOTYPES */
/******************************************************************************/

/**
 * intializion the timer peripheral
 * @param[in] pstConfig pointer to configration structure of the
 *                      Timer1 peripheral
 * @return None
*/

void Timer0_vInit(Timer0_tstConfig* pstConfig);

/**
 * @param[in] u16Payload refer to the value which you want to put in compare 
 *                       regester
*/

void Timer0_vSetPayload(uint16 u16Payload);

/**
 * @param[in] pfnCallback refer to pointer to function "Callback function"
 * @param[in] pvArgs      refer to pointer to additional arguments
 * 
 * @return None
*/

void Timer0_vSetCallbackFunc(void (*pfnCallback)(void*), void* pvArgs);
/**
 * @brief this function to enable Timer
 * 
 * @return Nothing
*/
void Timer0_vEnable(void);
/**
 * @brief this function to disable Timer
 * 
 * @return Nothing
*/
void Timer0_vDisable(void);

/******************************************************************************/

/******************************************************************************/
/* C++ Style GUARD */
/******************************************************************************/
#ifdef __cplusplus
}
#endif /* __cplusplus */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#endif /* FILE_NAME_H */
/******************************************************************************/