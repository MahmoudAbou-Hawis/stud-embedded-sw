/******************************************************************************/
/**
 * @file I2C.h
 * @brief Atmega32P I2C implemention in C language
 *
 * @par Project Name
 * I2C Driver
 *
 * @par Code Language
 * C
 *
 * @par Description
 * You Can use I2C in Atmega32P
 * 
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef I2C_H
#define I2C_H
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

/*----------------------------------------------------------------------------*/
/**
 * @brief represent I2C Interrupt choicess in Configration  
 * 
 */
/*----------------------------------------------------------------------------*/
typedef enum
{
    /**
     * @brief Disable TWI Interrupt
     * 
     */
    I2C_INTERRUPT_NONE = 0,

    /**
     * @brief Enable TWI Interrupt
     * 
     */
    I2C_INTERRUPT_EN
} I2C_tenumInterruptEn;
/*----------------------------------------------------------------------------*/

/**
 * @brief Represents I2C Prescaler Selections used in configration
 * 
 */
/*----------------------------------------------------------------------------*/
typedef enum 
{
    /**
     * @brief Means you make the parser value equal 1
     * 
     */
    I2C_PARSER_VALUE_1 = 0,

    /**
     * @brief Means you make the parser value equal 4
     * 
     */
    I2C_PARSER_VALUE_4    ,

    /**
     * @brief Means you make the parser value equal 8
     * 
     */
    I2C_PARSER_VALUE_16   ,

    /**
     * @brief Means you make the parser value equal 16
     * 
     */
    I2C_PARSER_VALUE_64 


} I2C_tenumPrescalerSelections;
/*----------------------------------------------------------------------------*/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @brief reffer to the configration of I2C Master device
 * 
 */

typedef struct 
{
    /**
     * @brief The identifier of the PrescalerSelections
     * It could be one of:
     *    - I2C_PARSER_VALUE_1 
     *    - I2C_PARSER_VALUE_4
     *    - I2C_PARSER_VALUE_16 
     *    - I2C_PARSER_VALUE_64
     */
    I2C_tenumPrescalerSelections enmParserValue;

    /**
     * @brief it include 8 bit it can carry values from 0 to 255
     * 
     */

    uint8 u8BitRate;

} I2C_tstInitConfigMaster;
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
/**
 * @brief This function used to Initialize I2C Master
 * 
 * @param[in] MasterInitConfig A pointer to Master Configration structure of I2C 
 *                             Peripheral
 */
/*----------------------------------------------------------------------------*/
void I2C_vMasterInit(I2C_tstInitConfigMaster* MasterInitConfig);
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * @brief This Function used to Transffer data using I2C
 * 
 * @param[in] pvBuff      A pointer to the Buffer which you prepared to transmit 
 * @param[in] u16Length   refer to the length of the buffer
 * @param[in] pfnCallback refer to the CallBack function it could be equal to NULL 
 * 
 * @return Nothing
 * 
 * @note This function used only in polling mode
 */
/*----------------------------------------------------------------------------*/
void I2C_vTransmitBuffMaster(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress);
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * @brief this function used to receive data using I2C.
 * 
 * @param[in] pvBuff      A pointer to the Buffer which you prepared to receive .
 * @param[in] u16Length   refer to the length of the buffer.
 * @param[in] pfnCallback refer to the CallBack function it could be equal to NULL .
 * 
 * @return Nothing
 * 
 * @note This function used only in polling mode.
*/
/*----------------------------------------------------------------------------*/
void I2C_vReceiveBuffMaster(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress);
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * @brief this function used to transmit data using I2C
 * 
 * @param[in] pvBuff      A pointer to the Buffer which you prepared to transmit 
 * @param[in] u16Length   refer to the length of the buffer.
 * @param[in] u16Timeout  refer to Maxmuim time you want . if process need more time 
 *                        it will terminate the process.
 * @param[in] pfnCallback refer to the CallBack function it could be equal to NULL.
 * 
 * @return Nothing
 * 
 * @note This fuction used only in timeout mode.
/*----------------------------------------------------------------------------*/
void I2C_vTransmitBuffTimeoutMaster(void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress);
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * @brief this function used to receive data using I2C
 * 
 * @param[in] pvBuff      A pointer to the Buffer which you prepared to recieve 
 * @param[in] u16Length   refer to the length of the buffer
 * @param[in] u16Timeout  refer to Maxmuim time you want . if process need more time 
 *                        it will terminate the process
 * @param[in] pfnCallback refer to the CallBack function it could be equal to NULL
 *
 * @return Nothing
 * 
 * @note This fuction used only in timeout mode
/*----------------------------------------------------------------------------*/
void I2C_vReceiveBuffTimeoutMaster(void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress);
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * @brief This Function used to Transffer data using I2C
 * 
 * @param[in] pvBuff      A pointer to the Buffer which you prepared to transmit 
 * @param[in] u16Length   refer to the length of the buffer
 * @param[in] pfnCallback refer to the CallBack function it could be equal to NULL 
 * 
 * @return Nothing
 * 
 * @note This function used only in Interrupt mode
 */
/*----------------------------------------------------------------------------*/
void I2C_vTransmitBuffInterruptMaster(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress);
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * @brief This Function used to recieve data using I2C
 * 
 * @param[in] pvBuff      A pointer to the Buffer which you prepared to recieve 
 * @param[in] u16Length   refer to the length of the buffer
 * @param[in] pfnCallback refer to the CallBack function it could be equal to NULL 
 * 
 * @return Nothing
 * 
 * @note This function used only in Interrupt mode
 */
/*----------------------------------------------------------------------------*/

void I2C_vReceiveBuffInterruptMaster(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress);
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