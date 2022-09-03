/******************************************************************************/
/**
 * @file ADC.h
 * @brief Atmega32P ADC implemention in C language
 *
 * @par Project Name
 * ADC Driver
 *
 * @par Code Language
 * C
 *
 * @par Description
 * You Can get the digital value of analog signal by using this driver
 * 
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef ADC_H
#define ADC_H
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

/*----------------------------------------------------------------------------*/
/** @brief Represents possible Voltage reference choices
 */
/*----------------------------------------------------------------------------*/

typedef enum 
{
    /** @brief AREF, internal V REF turned off
     */
    ARED = 0,

    /** @brief AV CC with external capacitor at AREF pin
     */
    Avcc = 1,

    /** @brief Internal 1.1V voltage reference with external capacitor at AREF pin
     */
    INTERNAL_1V = 3


} ADC_tenmVoltageReference;
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief Represents possible Channels choices from ADC0 to ADC7
 */
/*----------------------------------------------------------------------------*/

typedef enum
{
    /** @brief Selected Channel is ADC0
     */
    ADC0 = 0,

     /** @brief Selected Channel is ADC1
     */
    ADC1 = 1,

     /** @brief Selected Channel is ADC2
     */
    ADC2 = 2,

     /** @brief Selected Channel is ADC3
     */
    ADC3 = 3,

    /** @brief Selected Channel is ADC4
     */
    ADC4 = 4,

    /** @brief Selected Channel is ADC5
     */
    ADC5 = 5,

    /** @brief Selected Channel is ADC6
     */
    ADC6 = 6,
    
    /** @brief Selected Channel is ADC7
     */
    ADC7 = 7

} ADC_tenmAnolagChannals;
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief Represents Interrupt choices
 */
/*----------------------------------------------------------------------------*/

typedef enum
{
    /** @brief Disable ADC interrupt
     */
    INTERRUPT_NONE = 0,

    /** @brief Enable ADC interrupt
     */
	INTERRUPT_EN

} ADC_tenmInterruptType;
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief Represents ADC Prescaler Selections
 */
/*----------------------------------------------------------------------------*/

typedef enum
{
    /** @brief Frequancy of rhe resultant conversion equal  8000 KHz
     */
    Division_Factor_2   = 1,

    /** @brief Frequancy of rhe resultant conversion equal  4000 KHz
     */
    Division_Factor_4   = 2, 

    /** @brief Frequancy of rhe resultant conversion equal  2000 KHz
     */
    Division_Factor_8   = 3,

    /** @brief Frequancy of rhe resultant conversion equal  1000 KHz
     */
    Division_Factor_16  = 4,

    /** @brief Frequancy of rhe resultant conversion equal  500 KHz
     */
    Division_Factor_32  = 5,

    /** @brief Frequancy of rhe resultant conversion equal  250 KHz
     */
    Division_Factor_64  = 6,

    /** @brief Frequancy of rhe resultant conversion equal  125 KHz
     */
    Division_Factor_128 = 7

} ADC_PrescalerSelections;


/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/** @brief Represents the initial configuration for the ADC 
 */
/*----------------------------------------------------------------------------*/

typedef struct
{
    /** @brief The identifier of the Voltage Reference 
     * 
     * It could be one of:
     *    - ARED
     *    - Avcc
     *    - internal_1V
     */
    ADC_tenmVoltageReference enmVoltageReference;

    /** @brief The identifier of the InterruptType
     * 
     * It could be one of:
     *    - INTERRUPT_NONE
     *    - INTERRUPT_EN
     */
	ADC_tenmInterruptType enmInterruptType;

    /** @brief The identifier of the PrescalerSelections
     * 
     * It could be one of:
     *    - Division_Factor_2
     *    - Division_Factor_4
     *    - .
     *    - .
     *    - .
     *    - Division_Factor_128
     */

	ADC_PrescalerSelections enmPrescalerSelections;

} ADC_tstInitConfig;

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

/*----------------------------------------------------------------------------*/
/** @brief Initialize ADC 
 * 
 * @param[in] pstADCInit  A pointer to the configuration structure of the ADC
 *                        peripheral
 * @return None
 */
/*----------------------------------------------------------------------------*/
void ADC_vInit(ADC_tstInitConfig* pstADCInit);

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief Using this function to create new channal 
 * 
 * @param[in] enmChannal  refer to the channal for example ADC0
 * 
 * @return pointer to Channal handle
 */
/*----------------------------------------------------------------------------*/
void* ADC_pvCreateChannel(ADC_tenmAnolagChannals enmChannal);

/*----------------------------------------------------------------------------*/
/** @brief 
 * 
 * @param[in] pvChannalHandle   Pointer to channal Handle
 * 
 * @param[in] pfnCallback       Pointer to CallBack function to be called after
 *                              conversion
 * 
 * @return The value of analog signal after conversion it must be from 0 to 1023
 * 
 * @note This function runs in the polling mode only
 */
/*----------------------------------------------------------------------------*/
uint16 ADC_u16Read(void* pvChannalHandle, void (*pfnCallback)(uint16));

/*----------------------------------------------------------------------------*/
/** @brief 
 * 
 * @param[in] pvChannalHandle   Pointer to channal Handle.
 * 
 * @param[in] pfnCallback       Pointer to CallBack function to be called after
 *                              conversion.
 * 
 * @param[in] TimeOut           it refer to the time you want to perform reading
 *                              if time finished and we can't read the value the 
 *                              program still working.
 *                              
 * @return The value of analog signal after conversion it must be from 0 to 1023
 * 
 * @note This function runs in the TimeOut mode only
 */
/*----------------------------------------------------------------------------*/
uint16 ADC_u16ReadTimeOut(void* pvChannalHandle, uint16 TimeOut, void (*pfnCallback)(uint16));

/*----------------------------------------------------------------------------*/
/** @brief 
 * 
 * @param[in] pvChannalHandle   Pointer to channal Handle
 * @param[in] pfnCallback       Pointer to CallBack function to be called after
 *                              conversion
 * 
 * @return The value of analog signal after conversion it must be from 0 to 1023
 * 
 * @note This function runs in the Interrupt mode Enabled
 */
/*----------------------------------------------------------------------------*/
uint16 ADC_u16ReadInterrupt(void* pvChannalHandle, void (*pfnCallback)(uint16));
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
#endif  
/******************************************************************************/