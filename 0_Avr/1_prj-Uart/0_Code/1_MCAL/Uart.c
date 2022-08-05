/******************************************************************************/
/**
 * @file Uart.c
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
/* INCLUDES */
/******************************************************************************/

#include "Uart.h"
#include "StdTypes.h"
//#include "Terminal.h"
#include <stdlib.h>
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/
#define UART0_BASE (0xC0)
#define TR_UART0 ((tstUartMemRegs *)UART0_BASE)
#define UART_HND ((tstUartHandle *)(pvUartHnd))
#define BIT_UDRE0 (5)
#define BIT_RXC0 (7)
#define UCSZn2 (2)
#define USBSn (3)
#define UPMn0 (4)
#define UCSZn0 (1)

#define NUM_OF_HANDLES 1
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

typedef struct
{
    volatile uint8 u8UcsrA;
    volatile uint8 u8UcsrB;
    volatile uint8 u8UcsrC;
    volatile uint8 u8Dummy1;
    volatile uint16 u16Ubrr;
    volatile uint8 u8Udr;

} tstUartMemRegs;


typedef struct
{
    tstUartMemRegs* pstUartMemRegs;

    void * pvSendBuffer;
    uint16 u16SendBufferLength;
    void (*pfnSendBufferCallback)(void *, uint16);
    int SendBufferindex;
    void * pvReciveBuffer;
    uint16 u16ReciveBufferLength;
    void (*pfnReciveBufferCallback)(void *, uint16);
    int ReciveBufferindex;
    bool RecivedFlag;

} tstUartHandle;


/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

static tstUartHandle astHandles[NUM_OF_HANDLES] =
{
    {
        .pstUartMemRegs = TR_UART0
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
void Uart_vTransmitByte(void *pvUartHnd, uint8 u8Byte, uint16 u16TimeOut);
uint8 Uart_u8ReceiveByte(void *pvUartHnd, uint16 u16TimeOut);
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/

void *Uart_pvInit(Uart_tstInitConfig *UartInit)
{
    if (UartInit->u8UartIdx > NUM_OF_HANDLES)
    {
        return NULL;
    }

    astHandles[UartInit->u8UartIdx].pstUartMemRegs->u8UcsrB = ((UartInit->u8InterruptType | UartInit->u8Direction) | (UartInit->enmCharSize & 1 << UCSZn2));
    astHandles[UartInit->u8UartIdx].pstUartMemRegs->u16Ubrr = ((UartInit->u32SystemClock / (16 * (uint32)UartInit->u32BaudRate)) - 1);
    astHandles[UartInit->u8UartIdx].pstUartMemRegs->u8UcsrC = (UartInit->enmCharSize != UART_SIZE_9) ? (UartInit->enmCharSize << UCSZn0) : (UartInit->enmCharSize - 1 << UCSZn0);
    astHandles[UartInit->u8UartIdx].pstUartMemRegs->u8UcsrC |= ((UartInit->enmStopBits << USBSn) | (UartInit->enmParityType << UPMn0));
    astHandles[UartInit->u8UartIdx].RecivedFlag = 0;
    return (void *)&astHandles[UartInit->u8UartIdx];
}

void Uart_vTransmitByte(void *pvUartHnd, uint8 u8Byte, uint16 u16TimeOut)
{
    if (pvUartHnd == NULL)
    {
        return;
    }

    uint16 counter = 0;
    while ((!(UART_HND->pstUartMemRegs->u8UcsrA & (1 << BIT_UDRE0))) && (counter < u16TimeOut))
    {
        counter++;
    }

    if (!u16TimeOut)
    {
        return;
    }

    UART_HND->pstUartMemRegs->u8Udr = u8Byte;
}

uint8 Uart_u8ReceiveByte(void *pvUartHnd, uint16 u16TimeOut)
{
    if (pvUartHnd == NULL)
    {
        return 0;
    }

    uint16 counter = 0;
    while ((!(UART_HND->pstUartMemRegs->u8UcsrA & (1 << BIT_RXC0))) && counter < u16TimeOut)
    {
        counter++;
    }

    if (counter == u16TimeOut)
    {
        UART_HND->RecivedFlag = false;
    }
    else
    {
        UART_HND->RecivedFlag = true;
    }
    return UART_HND->pstUartMemRegs->u8Udr;
}

void Uart_vTransmitBuff(void *pvUartHnd, void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16))
{
    if (pvUartHnd == NULL)
    {
        return;
    }

    for (int idx = 0; idx < u16Length; idx++)
    {
        while (!(UART_HND->pstUartMemRegs->u8UcsrA & (1 << BIT_UDRE0)));
        UART_HND->pstUartMemRegs->u8Udr = ((uint8 *)pvBuff)[idx];
    }

    if (pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
}

void Uart_vReceiveBuff(void *pvUartHnd, void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16))
{
    if (pvUartHnd == NULL)
    {
        return;
    }

    for (int idx = 0; idx < u16Length; idx++)
    {
        while (!(UART_HND->pstUartMemRegs->u8UcsrA & (1 << BIT_RXC0)));
        ((uint8 *)pvBuff)[idx] = UART_HND->pstUartMemRegs->u8Udr;
    }

    if (pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
}

void Uart_vTransmitBuffTimeout(void *pvUartHnd, void *pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void *, uint16))
{
    if (pvUartHnd == NULL)
    {
        return;
    }

    for (int idx = 0; idx < u16Length; idx++)
    {
        Uart_vTransmitByte(pvUartHnd, ((uint8 *)pvBuff)[idx], u16Timeout);
    }
    if (pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
}

void Uart_vReceiveBuffTimeout(void *pvUartHnd, void *pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void *, uint16))
{
    if (pvUartHnd == NULL)
    {
        return;
    }

    for (int idx = 0; idx < u16Length; idx++)
    {
        uint8 Data = Uart_u8ReceiveByte(pvUartHnd, u16Timeout);
        if (UART_HND->RecivedFlag)
        {
            ((uint8 *)pvBuff)[idx] = Data;
        }
    }
    if (pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
}

void Uart_vTransmitBuffInterrupt(void *pvUartHnd, void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16))
{
    if (pvUartHnd == NULL)
    {
        return;
    }

    UART_HND->pvSendBuffer = pvBuff;
    UART_HND->SendBufferindex = 1;
    UART_HND->pfnSendBufferCallback = pfnCallback;
    UART_HND->u16SendBufferLength = u16Length;
    UART_HND->pstUartMemRegs->u8Udr = ((uint8 *)pvBuff)[0];
}

void Uart_vReceiveBuffInterrupt(void *pvUartHnd, void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16))
{
    if (pvUartHnd == NULL)
    {
        return;
    }

    UART_HND->pvReciveBuffer = pvBuff;
    UART_HND->ReciveBufferindex = 0;
    UART_HND->pfnReciveBufferCallback = pfnCallback;
    UART_HND->u16ReciveBufferLength = u16Length;
}

ISR(USART_TX_vect)
{
    if (astHandles[0].SendBufferindex == astHandles[0].u16SendBufferLength)
    {
        if (astHandles[0].pfnSendBufferCallback != NULL)
        {

            (astHandles[0].pfnSendBufferCallback)(astHandles[0].pvSendBuffer, astHandles[0].u16SendBufferLength);
        }
    }
    else
    {
        astHandles[0].pstUartMemRegs->u8Udr = ((uint8 *)astHandles[0].pvSendBuffer)[astHandles[0].SendBufferindex++];
    }
}

ISR(USART_RX_vect)
{
    ((uint8 *)astHandles[0].pvReciveBuffer)[astHandles[0].ReciveBufferindex++] = astHandles[0].pstUartMemRegs->u8Udr;
    if (astHandles[0].ReciveBufferindex == astHandles[0].u16ReciveBufferLength)
    {
        astHandles[0].ReciveBufferindex = 0;
        if (astHandles[0].pfnReciveBufferCallback != NULL)
        {
            (astHandles[0].pfnReciveBufferCallback)(astHandles[0].pvReciveBuffer, astHandles[0].u16ReciveBufferLength);
        }
    }
}

/******************************************************************************/