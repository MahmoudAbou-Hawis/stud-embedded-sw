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

#define F_CLK (16000000.0)
#define SERG  *(((volatile uint8*)0x5F))

    /******************************************************************************/

    /******************************************************************************/
    /* PUBLIC MACROS */
    /******************************************************************************/

    /******************************************************************************/

    /******************************************************************************/
    /* PUBLIC ENUMS */
    /******************************************************************************/

    typedef enum
    {
        UART_SIZE_5 = 0,
        UART_SIZE_6 = 1,
        UART_SIZE_7 = 2,
        UART_SIZE_8 = 3,
        UART_SIZE_9

    } Uart_tenmCharSize;

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
        UART_INTERRUPT_NONE = 0,
        UART_INTERRUPT_TX = (1 << 6),
        UART_INTERRUPT_RX = (1 << 7),
        UART_INTERRUPT_EMPTY_REG = (1 << 5)

    } Uart_tenmInterruptType;
    /******************************************************************************/

    /******************************************************************************/
    /* PUBLIC TYPES */
    /******************************************************************************/
    /******************************************************************************/

    typedef struct
    {
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

    void Uart_vInit(Uart_tstInitConfig *stUartInit);
    void Uart_vTransmitBuff(void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16));
    void Uart_vReceiveBuff(void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16));
    void Uart_vTransmitBuffTimeout(void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16));
    void Uart_vReceiveBuffTimeout(void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16));
    void Uart_vTransmitBuffInterrupt(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16));
    void Uart_vReceiveBuffInterrupt(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16));
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
