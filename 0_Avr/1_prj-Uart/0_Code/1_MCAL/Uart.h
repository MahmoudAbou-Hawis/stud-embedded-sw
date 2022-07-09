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

#include <stdio.h>
#include "StdTypes.h"

/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

#define F_CLK      (16000000.0)

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

void UART_vInit(void);
void UART_vTransmitByte(uint8 Byte);
uint8 UART_u8ReceiveByte(void);

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