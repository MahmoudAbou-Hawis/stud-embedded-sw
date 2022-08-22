/******************************************************************************/
/**
 * @file Uart.h
 * @brief Uart protocol implemention in c language
 *
 * @par Project Name
 * Uart Project
 *
 * @par Code Language
 * C
 *
 * @par Description
 * You can Transmit and receive with Uart protocol
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef UART_H
#define UART_H
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
#include <stdbool.h>

/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief Microcontroller clock
 */
/*----------------------------------------------------------------------------*/
#define F_CLK (16000000.0)
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief status register
 */
/*----------------------------------------------------------------------------*/
#define SERG  *(((volatile uint8*)0x5F))
/*----------------------------------------------------------------------------*/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief Represents possible character size choices
 */
/*----------------------------------------------------------------------------*/
typedef enum
{
    /** @brief Character size = 5 bits
     */
    UART_SIZE_5 = 0,

    /** @brief Character size = 6 bits
     */
    UART_SIZE_6 = 1,

    /** @brief Character size = 7 bits
     */
    UART_SIZE_7 = 2,

    /** @brief Character size = 8 bits
     */
    UART_SIZE_8 = 3,

    /** @brief Character size = 9 bits
     */
    UART_SIZE_9

} Uart_tenmCharSize;
/*----------------------------------------------------------------------------*/

typedef enum
{
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN = 2,
    UART_PARITY_ODD

} Uart_tenmParityType;

typedef enum
{
    UART_STOP_1 = 0,
    UART_STOP_2

} Uart_tenmStopBits;

typedef enum
{
    UART_DIR_TX = (1 << 3),
    UART_DIR_RX = (1 << 4)

} Uart_tenmDirection;

typedef enum
{
    UART_INTERRUPT_NONE      = 0,
    UART_INTERRUPT_TX        = (1 << 6),
    UART_INTERRUPT_RX        = (1 << 7),
    UART_INTERRUPT_EMPTY_REG = (1 << 5)

} Uart_tenmInterruptType;

typedef enum
{
    UART1 = 0,
    UART2 = 1

} Uart_tenmUartID;
/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief Represents the initial configuration for the UART peripheral
 */
/*----------------------------------------------------------------------------*/
typedef struct
{
    /** @brief The identifier of the UART peripheral
     * 
     * It could be one of:
     *    - UART1
     *    - UART2
     */
    uint8 u8UartIdx;

    /** @brief The current microcontroller clock frequency value 
     */
    uint32 u32SystemClock;
    uint32 u32BaudRate;
    Uart_tenmCharSize enmCharSize;
    Uart_tenmParityType enmParityType;
    Uart_tenmStopBits enmStopBits;
    uint8 u8Direction;
    uint8 u8InterruptType;
    
} Uart_tstInitConfig;


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
/** @brief Initialize the UART peripheral
 *
 * @param[in] UartInit A pointer to the configuration structure of the UART
 *                     peripheral
 * @return Pointer to the UART handle
 */
/*----------------------------------------------------------------------------*/
void* Uart_pvInit(Uart_tstInitConfig* UartInit);
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief Transmit a buffer of data using the UART peripheral in the polling
 *         mode
 * 
 * @param[in] pvUartHnd   Pointer to UART Handle
 * @param[in] pvBuff      Pointer to data Buffer to be transmitted
 * @param[in] u16Length   The length of buffer
 * @param[in] pfnCallback Pointer to CallBack function to be called after
 *                        transmission
 * @return None
 */
/*----------------------------------------------------------------------------*/
void Uart_vTransmitBuff(void* pvUartHnd,
                       void *pvBuff,
                       uint16 u16Length,
                       void (*pfnCallback)(void *, uint16));
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief Receive a buffer of data using the UART peripheral in the polling
 *         mode
 * 
 * @param[in] pvUartHnd   Pointer to UART Handle
 * @param[in] pvBuff      Pointer to data Buffer to be received in
 * @param[in] u16Length   The length of buffer
 * @param[in] pfnCallback Pointer to CallBack function to be called after
 *                        receiving
 * @return None
 * 
 * @note This function runs in the polling mode only
 */
/*----------------------------------------------------------------------------*/
void Uart_vReceiveBuff(void* pvUartHnd,void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16));
/*----------------------------------------------------------------------------*/

void Uart_vTransmitBuffTimeout(void* pvUartHnd,void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16));
void Uart_vReceiveBuffTimeout(void* pvUartHnd,void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16));
void Uart_vTransmitBuffInterrupt(void* pvUartHnd,void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16));
void Uart_vReceiveBuffInterrupt(void* pvUartHnd,void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16));

/******************************************************************************/

/******************************************************************************/
/* C++ Style GUARD */
/******************************************************************************/
#ifdef __cplusplus

#endif /* __cplusplus */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#endif /* FILE_NAME_H */
/******************************************************************************/