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
#include "Terminal.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/
#define UART0_BASE     (0xC0)
#define TR_UART0       ((tstUartHandle *)UART0_BASE)
#define BIT_UDRE0          (5)
#define BIT_RXC0       (7)
#define UCSZn2         (2)
#define USBSn          (3)
#define UPMn0          (4)
#define UCSZn0         (1)
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

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/
void * pvSendBuffer = NULL ;
uint16 u16SendBufferLength = 0;
void (*pfnSendBufferCallback)(void *, uint16) = NULL ;
int SendBufferindex = 0;

void * pvReciveBuffer = NULL ;
uint16 u16ReciveBufferLength = 0;
void (*pfnReciveBufferCallback)(void *, uint16) = NULL ;
int ReciveBufferindex = 0;

bool RecivedFlag = 0;

bool CorrectData = false;
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
void Uart_vTransmitByte(uint8 u8Byte,uint16 u16TimeOut);
uint8 Uart_u8ReceiveByte(uint16 u16TimeOut);
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/

void Uart_vInit(Uart_tstInitConfig* UartInit)
{
    TR_UART0->u8UcsrB  = ((UartInit->u8InterruptType | UartInit->u8Direction) | (UartInit->enmCharSize & 1 << UCSZn2));
    TR_UART0->u16Ubrr  = ((UartInit->u32SystemClock / (16 * (uint32)UartInit->u32BaudRate)) - 1);
    TR_UART0->u8UcsrC  = (UartInit->enmCharSize != UART_SIZE_9) ? (UartInit->enmCharSize << UCSZn0): (UartInit->enmCharSize-1 << UCSZn0 );
    TR_UART0->u8UcsrC |= ((UartInit->enmStopBits << USBSn) | (UartInit->enmParityType << UPMn0)) ;
   
}

void Uart_vTransmitByte(uint8 u8Byte , uint16 u16TimeOut)
{
     uint16 counter = 0;
    while ((!(TR_UART0->u8UcsrA & (1 << BIT_UDRE0)))&&  (counter < u16TimeOut))counter++;
    if(!u16TimeOut)
    {
        return;
    }
    TR_UART0->u8Udr = u8Byte;
}

uint8 Uart_u8ReceiveByte(uint16 u16TimeOut)
{
    uint16 counter = 0;
    while ((!(TR_UART0->u8UcsrA & (1 << BIT_RXC0))) &&  counter < u16TimeOut )counter++;
    if(counter == u16TimeOut)
    {
        RecivedFlag = false;
    }
    else
    {
        RecivedFlag = true;
    }
    return TR_UART0->u8Udr;
}

void  Uart_vTransmitBuff(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16))
{
    for(int idx = 0 ; idx < u16Length ; idx++)
    {
        while (!(TR_UART0->u8UcsrA & (1 << BIT_UDRE0)));
         TR_UART0->u8Udr = ((uint8*)pvBuff)[idx];
        
    }
    if(pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
}

void Uart_vReceiveBuff(void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16))
{
    for(int idx = 0 ; idx < u16Length ; idx++)
    {
        while(!(TR_UART0->u8UcsrA & (1 << BIT_RXC0)));
       ((uint8*)pvBuff)[idx] =   TR_UART0->u8Udr;
    }
    if(pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
}

void Uart_vTransmitBuffTimeout(void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16))
{
    for(int idx = 0 ; idx < u16Length ; idx++)
    {
        Uart_vTransmitByte(((uint8*)pvBuff)[idx] , u16Timeout);
    }
    if(pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
}

 void Uart_vReceiveBuffTimeout(void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16))
 {
    for(int idx = 0 ; idx < u16Length ; idx++)
    {
        uint8 Data =  Uart_u8ReceiveByte(u16Timeout);
        if(RecivedFlag)
        {
             ((uint8*)pvBuff)[idx] = Data;
        }
    }
    if(pfnCallback != NULL)
    {
        (*pfnCallback)(pvBuff, u16Length);
    }
 }

void Uart_vTransmitBuffInterrupt(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16))
{
    pvSendBuffer = pvBuff;
    SendBufferindex = 1;
    pfnSendBufferCallback = pfnCallback;
    u16SendBufferLength = u16Length;
    TR_UART0->u8Udr = ((uint8*)pvBuff)[0];

}

void Uart_vReceiveBuffInterrupt(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16))
{
    pvReciveBuffer = pvBuff;
    ReciveBufferindex = 0;
    pfnReciveBufferCallback = pfnCallback;
    u16ReciveBufferLength = u16Length;
}
bool Uart_readRecivedFlag(void)
{
    if(CorrectData)
    {
        CorrectData = false;
        return true;
    }
    return false;
}
ISR(USART_TX_vect)
{
      if(SendBufferindex == u16SendBufferLength)
      { 
        if(pfnSendBufferCallback != NULL)
        {
           (*pfnSendBufferCallback)(pvSendBuffer,u16SendBufferLength);
        }
      }
      else
      {
       TR_UART0->u8Udr = ((uint8*)pvSendBuffer)[SendBufferindex++];
      }
}

ISR(USART_RX_vect)
{
        ((uint8*) pvReciveBuffer)[ReciveBufferindex++] = TR_UART0->u8Udr; 
        if(((uint8*) pvReciveBuffer)[ReciveBufferindex-1]  == '/')
        { 
            ((uint8*) pvReciveBuffer)[ReciveBufferindex]='\0';   
            CorrectData =true;
            ReciveBufferindex = 0;
            if(pfnReciveBufferCallback != NULL)
                {
                 (*pfnReciveBufferCallback)(pvReciveBuffer,u16ReciveBufferLength);
                }
        }
      
}



/******************************************************************************/