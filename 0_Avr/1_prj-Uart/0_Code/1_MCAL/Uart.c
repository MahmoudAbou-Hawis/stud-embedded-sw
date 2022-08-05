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
#define TR_UART0 ((tstUartHandle *)UART0_BASE)
#define UART_HND ((tstUartHandle *)(pvUartHnd))
#define BIT_UDRE0 (5)
#define BIT_RXC0 (7)
#define UCSZn2 (2)
#define USBSn (3)
#define UPMn0 (4)
#define UCSZn0 (1)
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

} tstUartHandle;


typedef struct
{
    void * pvSendBuffer  ;
    uint16 u16SendBufferLength;
    void (*pfnSendBufferCallback)(void *, uint16) ;
    int SendBufferindex ;
    void * pvReciveBuffer  ;
    uint16 u16ReciveBufferLength ;
    void (*pfnReciveBufferCallback)(void *, uint16)  ;
    int ReciveBufferindex ;
    bool RecivedFlag ;
} ConfUart;

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/
tstUartHandle *UartAddresse[30] = {TR_UART0};
ConfUart *Conf[30];
static void *pvUartHndInt = NULL;

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
sint16 GetAddressIndex(void * Address)
{
    for(int i = 0 ; i < 1 ; i++)
        if(UartAddresse[i] == (tstUartHandle *)Address)
        {
             return i;
        }
}

void *Uart_pvInit(Uart_tstInitConfig *UartInit)
{
    UartAddresse[UartInit->u8UartIdx]->u8UcsrB = ((UartInit->u8InterruptType | UartInit->u8Direction) | (UartInit->enmCharSize & 1 << UCSZn2));
    UartAddresse[UartInit->u8UartIdx]->u16Ubrr = ((UartInit->u32SystemClock / (16 * (uint32)UartInit->u32BaudRate)) - 1);
    UartAddresse[UartInit->u8UartIdx]->u8UcsrC = (UartInit->enmCharSize != UART_SIZE_9) ? (UartInit->enmCharSize << UCSZn0) : (UartInit->enmCharSize - 1 << UCSZn0);
    UartAddresse[UartInit->u8UartIdx]->u8UcsrC |= ((UartInit->enmStopBits << USBSn) | (UartInit->enmParityType << UPMn0));
    Conf[UartInit->u8UartIdx] = (ConfUart*)malloc(1 *sizeof(ConfUart));
    Conf[UartInit->u8UartIdx]->RecivedFlag = 0;
    return (void *)UartAddresse[UartInit->u8UartIdx];
}

void Uart_vTransmitByte(void *pvUartHnd, uint8 u8Byte, uint16 u16TimeOut)
{
    uint16 counter = 0;
    while ((!(UART_HND->u8UcsrA & (1 << BIT_UDRE0))) && (counter < u16TimeOut))
        counter++;
    if (!u16TimeOut)
    {
        return;
    }
    UART_HND->u8Udr = u8Byte;
}

uint8 Uart_u8ReceiveByte(void *pvUartHnd, uint16 u16TimeOut)
{
    uint16 counter = 0;
    while ((!(UART_HND->u8UcsrA & (1 << BIT_RXC0))) && counter < u16TimeOut)
        counter++;
    if (counter == u16TimeOut)
    {
        Conf[GetAddressIndex(pvUartHnd)]->RecivedFlag = false;
    }
    else
    {
         Conf[GetAddressIndex(pvUartHnd)]->RecivedFlag = true;
    }
    return UART_HND->u8Udr;
}

void Uart_vTransmitBuff(void *pvUartHnd, void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16))
{
    for (int idx = 0; idx < u16Length; idx++)
    {
        while (!(UART_HND->u8UcsrA & (1 << BIT_UDRE0)));
        UART_HND->u8Udr = ((uint8 *)pvBuff)[idx];
    }
    if (pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
}

void Uart_vReceiveBuff(void *pvUartHnd, void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16))
{
    for (int idx = 0; idx < u16Length; idx++)
    {
        while (!(UART_HND->u8UcsrA & (1 << BIT_RXC0)));
        ((uint8 *)pvBuff)[idx] = TR_UART0->u8Udr;
    }
    if (pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
}

void Uart_vTransmitBuffTimeout(void *pvUartHnd, void *pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void *, uint16))
{
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
    for (int idx = 0; idx < u16Length; idx++)
    {
        uint8 Data = Uart_u8ReceiveByte(pvUartHnd, u16Timeout);
        if ( Conf[GetAddressIndex(pvUartHnd)]->RecivedFlag)
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
    Conf[GetAddressIndex(pvUartHnd)]->pvSendBuffer = pvBuff;
    Conf[GetAddressIndex(pvUartHnd)]->SendBufferindex = 1;
    Conf[GetAddressIndex(pvUartHnd)]->pfnSendBufferCallback = pfnCallback;
    Conf[GetAddressIndex(pvUartHnd)]->u16SendBufferLength = u16Length;
    UART_HND->u8Udr = ((uint8 *)pvBuff)[0];
}

void Uart_vReceiveBuffInterrupt(void *pvUartHnd, void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16))
{
    Conf[GetAddressIndex(pvUartHnd)]->pvReciveBuffer = pvBuff;
    Conf[GetAddressIndex(pvUartHnd)]->ReciveBufferindex = 0;
    Conf[GetAddressIndex(pvUartHnd)]->pfnReciveBufferCallback = pfnCallback;
    Conf[GetAddressIndex(pvUartHnd)]->u16ReciveBufferLength = u16Length;
}

ISR(USART_TX_vect)
{
    if (Conf[0]->SendBufferindex == Conf[0]->u16SendBufferLength)
    {
        if (Conf[0]->pfnSendBufferCallback != NULL)
        {

            (Conf[0]->pfnSendBufferCallback)(Conf[0]->pvSendBuffer, Conf[0]->u16SendBufferLength);
        }
    }
    else
    {
        TR_UART0->u8Udr = ((uint8 *)Conf[0]->pvSendBuffer)[Conf[0]->SendBufferindex++];
    }
}

ISR(USART_RX_vect)
{
    ((uint8 *)Conf[0]->pvReciveBuffer)[Conf[0]->ReciveBufferindex++] = TR_UART0->u8Udr;
    if (Conf[0]->ReciveBufferindex == Conf[0]->u16ReciveBufferLength)
    {
        Conf[0]->ReciveBufferindex = 0;
        if (Conf[0]->pfnReciveBufferCallback != NULL)
        {
            (Conf[0]->pfnReciveBufferCallback)(Conf[0]->pvReciveBuffer, Conf[0]->u16ReciveBufferLength);
        }
    }
}

/******************************************************************************/