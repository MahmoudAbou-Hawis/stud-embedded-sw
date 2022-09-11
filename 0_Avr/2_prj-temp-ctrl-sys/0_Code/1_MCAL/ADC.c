/******************************************************************************/
/**
 * @file ADC.c
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
/* INCLUDES */
/******************************************************************************/

// #include <avr/interrupt.h>
#include <avr/interrupt.h>
#include "ADC.h"

/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

/******************************************************************************/
/** @brief define the address of ADC base
 *
 */
/*----------------------------------------------------------------------------*/
#define ADC_BASE   (0x78)

/*----------------------------------------------------------------------------*/
/** @brief define the ADC handler
 *
 *  You can access all ADC registers from this handler
 */
/*----------------------------------------------------------------------------*/
#define ADC_HND      ((tstADCRegistrs *)ADC_BASE)
/**
 * @brief refer to Channal Handle
 * 
 */
#define Channal_HND  ((tstChannalHandle *)pvChannalHandle)
/**
 * @brief it is the 6th bit in u8Admux Register
 * 
 */
#define REFS0 6
/**
 * @brief it is the 6th bit in u8Adcsra Register 
 * 
 */
#define ADSC  6
/**
 * @brief it is the 7th bit in u8Adcsra Register 
 * 
 */
#define ADEN  7
/**
 * @brief it is the 3th bit in u8Adcsra Register 
 * 
 */
#define ADIE  3


#define ADLAR 5

#define ADIF  4 
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

/*----------------------------------------------------------------------------*/
/** @brief Represnt ADC Regisers
 */
/*----------------------------------------------------------------------------*/

typedef struct
{
    /** @brief The identifier of the ADCL register in ADC
     * 
     */
    volatile uint8 u8Adcl;

    /** @brief The identifier of the u8Adch register in ADC
     *
     */
    volatile uint8 u8Adch;

    /** @brief The identifier of the Adcsra register in ADC
     *
     */
    volatile uint8 u8Adcsra;

    /** @brief The identifier of the Adcsrb register in ADC
     *
     */
    volatile uint8 u8Adcsrb;

    /** @brief The identifier of the u8Admux register in ADC
     *
     */
    volatile uint8 u8Admux;

} tstADCRegistrs;

/*----------------------------------------------------------------------------*/
/** @brief Represnt channal's ID
 */
/*----------------------------------------------------------------------------*/
typedef struct 
{
    /** @brief The identifier of the channal id
     *
     */
    uint8 id;

} tstChannalHandle;

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

/**
 * @brief refer to all Channal handle's id
 * 
 */
static tstChannalHandle astChannelHandles[8] = 
{
    {
        .id = 0
    } ,

    {
        .id = 1
    } ,

    {
        .id = 2
    } ,
    {
        .id = 3
    } ,

    {
        .id = 4
    } ,

    {
        .id = 5
    } ,

    {
        .id = 6
    } ,

    {
        .id = 7
    }
};

void (*pfnCallbackInterrupt)(uint16) = NULL;

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

ISR(ADC_vect)
{
    uint16 u16Data = (ADC_HND->u8Adcl | (ADC_HND->u8Adch<<8));

    if (pfnCallbackInterrupt != NULL)
    {
        (*pfnCallbackInterrupt)(u16Data);
    }
    ADC_HND->u8Adcsra &= ~(1<<ADEN);
}

/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/


void ADC_vInit(ADC_tstInitConfig* pstADCInit)
{
    ADC_HND->u8Admux  = (pstADCInit->enmVoltageReference << REFS0);
    ADC_HND->u8Adcsra = (pstADCInit->enmPrescalerSelections)| 
                      (pstADCInit->enmInterruptType<<ADIE);
}

void* ADC_pvCreateChannel(ADC_tenmAnolagChannals enmChannal)
{
    return (void *)&astChannelHandles[enmChannal];
}

uint16 ADC_u16Read(void * pvChannalHandle, void (*pfnCallback)(uint16))
{
    if (pvChannalHandle == NULL)
    {
        return 0;
    }
    ADC_HND->u8Admux  &= 0xF0;
    ADC_HND->u8Admux  |= Channal_HND->id;
    ADC_HND->u8Adcsra |= (1<<ADEN);
    ADC_HND->u8Adcsra |= (1<<ADSC);
    while(!(ADC_HND->u8Adcsra & (1<<ADIF)));
    uint16 u16Data = (ADC_HND->u8Adcl | (ADC_HND->u8Adch<<8));
    if (pfnCallback != NULL)
    {
        (*pfnCallback)(u16Data);
    }
    ADC_HND->u8Adcsra &= ~(1<<ADEN);
    return u16Data;
}

uint16 ADC_u16ReadTimeOut(void* pvChannalHandle, uint16 TimeOut, void (*pfnCallback)(uint16))
{
    if (pvChannalHandle == NULL)
    {
        return 0;
    }
    ADC_HND->u8Admux  &= 0xF0;
    ADC_HND->u8Admux  |= Channal_HND->id;
    ADC_HND->u8Adcsra |= (1<<ADEN);
    ADC_HND->u8Adcsra |= (1<<ADSC);
    uint16 u16Counter = 0;
    while(!(ADC_HND->u8Adcsra & (1<<ADIF)) && u16Counter++ < TimeOut);
    uint16 u16Data = (ADC_HND->u8Adcl | (ADC_HND->u8Adch<<8));
    if (pfnCallback != NULL)
    {
        (*pfnCallback)(u16Data);
    }
    ADC_HND->u8Adcsra &= ~(1<<ADEN);
    return u16Data;
}

uint16 ADC_u16ReadInterrupt(void* pvChannalHandle, void (*pfnCallback)(uint16))
{
    if (pvChannalHandle == NULL)
    {
        return 0;
    }
    pfnCallbackInterrupt = pfnCallback;
    ADC_HND->u8Admux  &= 0xF0;
    ADC_HND->u8Admux  |= Channal_HND->id;
    ADC_HND->u8Adcsra |= (1<<ADEN);
    ADC_HND->u8Adcsra |= (1<<ADSC);
}

/******************************************************************************/