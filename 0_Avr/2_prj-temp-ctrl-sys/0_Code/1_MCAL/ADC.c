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
 * @brief it is the 6th bit in ADMUX Register
 * 
 */
#define REFS0 6
/**
 * @brief it is the 6th bit in ADCSRA Register 
 * 
 */
#define ADSC  6
/**
 * @brief it is the 7th bit in ADCSRA Register 
 * 
 */
#define ADEN  7
/**
 * @brief it is the 3th bit in ADCSRA Register 
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
    volatile uint8 ADCL;

    /** @brief The identifier of the ADCH register in ADC
     *
     */
    volatile uint8 ADCH;

    /** @brief The identifier of the ADCSRA register in ADC
     *
     */
    volatile uint8 ADCSRA;

    /** @brief The identifier of the ADCSRB register in ADC
     *
     */
    volatile uint8 ADCSRB;

    /** @brief The identifier of the ADMUX register in ADC
     *
     */
    volatile uint8 ADMUX;

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


void ADC_vInit(ADC_tstInitConfig* pstADCInit)
{
    ADC_HND->ADMUX  = (pstADCInit->enmVoltageReference << REFS0);
    ADC_HND->ADCSRA = (pstADCInit->enmPrescalerSelections)| 
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
    ADC_HND->ADMUX  &= 0xF0;
    ADC_HND->ADMUX  |= Channal_HND->id;
    ADC_HND->ADCSRA |= (1<<ADEN);
    ADC_HND->ADCSRA |=(1<<ADSC);
    
    while(!(ADC_HND->ADCSRA & (1<<ADIF)));
    uint16 u16Data = (ADC_HND->ADCL | (uint16)(ADC_HND->ADCH<<8));
    if (pfnCallback != NULL)
    {
        (*pfnCallback)(u16Data);
    
    }
    ADC_HND->ADCSRA &= ~(1<<ADEN);
    return u16Data;
}

uint16 ADC_u16ReadTimeOut(void* pvChannalHandle, uint16 TimeOut, void (*pfnCallback)(uint16))
{
    if (pvChannalHandle == NULL)
    {
        return 0;
    }
    ADC_HND->ADMUX  &= 0xF0;
    ADC_HND->ADMUX  |= Channal_HND->id;
    ADC_HND->ADCSRA |= (1<<ADEN);
    ADC_HND->ADCSRA |= (1<<ADSC);
    uint16 u16Counter = 0;
    while(!(ADC_HND->ADCSRA & (1<<ADIF)) && u16Counter++ < TimeOut);
    uint16 u16Data = (ADC_HND->ADCL | (ADC_HND->ADCH<<8));
    if (pfnCallback != NULL)
    {
        (*pfnCallback)(u16Data);
    }
    ADC_HND->ADCSRA &= ~(1<<ADEN);
    return u16Data;
}

uint16 ADC_u16ReadInterrupt(void* pvChannalHandle, void (*pfnCallback)(uint16))
{

}
/******************************************************************************/