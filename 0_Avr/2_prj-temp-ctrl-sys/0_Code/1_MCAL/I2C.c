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
/* INCLUDES */
/******************************************************************************/
#include "I2C.h"
#include <stdbool.h>
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

/**
 * @brief this is the base address of I2C
 *
 */

#define I2C_BASE (0xBD)
/**
 *@brief I2C_HND can control all the I2C registers
 */
#define I2C_HND ((tstI2CMemRegs *)I2C_BASE)

#define TWINT0 (7)
#define TWEA0 (6)
#define TWSTA0 (5)
#define TWSTO0 (4)
#define TWWC0 (3)
#define TWEN0 (2)
#define TWIE0 (0)

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

/**
 * @brief Represent to I2C Registers structure
 *
 */
typedef struct
{
    /**
     * @brief refer to TWAMR register in I2C
     *
     */
    volatile uint8 u8TWAMR;

    /**
     * @brief refer to TWCR register in I2C
     *
     */
    volatile uint8 u8TWCR;

    /**
     * @brief refer to TWDR register in I2C
     *
     */
    volatile uint8 u8TWDR;

    /**
     * @brief refer to TWAR register in I2C
     *
     */
    volatile uint8 u8TWAR;

    /**
     * @brief refer to TWSR register in I2C
     *
     */
    volatile uint8 u8TWSR;

    /**
     * @brief refer to TWBR register in I2C
     *
     */
    volatile uint8 u8TWBR;

} tstI2CMemRegs;

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

void *pvaBuff = NULL;
uint16 u16aLength;
uint16 u16aidx = 0;
void (*pfnaCallback)(void *, uint16) = NULL;
uint8 u8aSlaveAddress;
bool SendFlag;
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
void vStart()
{
    I2C_HND->u8TWCR = (1 << TWINT0)  | (1 << TWEN0)| (1<<TWIE0) | (1 << TWSTA0);
}
void vStop()
{
    I2C_HND->u8TWCR = (1 << TWINT0)  | (1 << TWEN0) | (1 << TWSTO0);
}
void vACK()
{
    I2C_HND->u8TWCR = (1<<TWINT0) |  (1<<TWEN0) | (1<<TWIE0) | (1<<TWEA0);
}
void vNACK()
{
    I2C_HND->u8TWCR = (1<<TWINT0) |  (1<<TWEN0) | (1<<TWIE0);
}
void write(uint8 data)
{
    I2C_HND->u8TWDR = data;
}
void vRead(bool bIsLast)
{
    if (bIsLast)
    {
        vNACK();
    }
    else
    {
        vACK();
    }
}
/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/
void I2C_vMasterInit(I2C_tstInitConfigMaster *MasterInitConfig)
{
    I2C_HND->u8TWSR = MasterInitConfig->enmParserValue;
    I2C_HND->u8TWBR = MasterInitConfig->u8BitRate;
    I2C_HND->u8TWCR = 0x04;
    return;
}

void I2C_vTransmitBuffMaster(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress)
{
    I2C_HND->u8TWCR |= (1<<TWINT0) | (1<<TWSTA0) | (1<<TWEN0); // start
    while(!((I2C_HND->u8TWCR)&(1<<TWINT0)));
    if((I2C_HND->u8TWSR & 0xF8)==0x08)
    {
        I2C_HND->u8TWDR = u8SlaveAddress;
        I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0);
        while(!((I2C_HND->u8TWCR)&(1<<TWINT0)));
    }
    if((I2C_HND->u8TWSR & 0xF8)==0x18)
    {
        for(int i = 0 ; i < u16Length ;)
        {
            I2C_HND->u8TWDR = ((uint8*)pvBuff)[i];
            I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0); 
            while(!((I2C_HND->u8TWCR)&(1<<TWINT0)));  
             if((I2C_HND->u8TWSR & 0xF8)==0x20 || (I2C_HND->u8TWSR & 0xF8)==0x30)
             {
                  I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0) | (1<<TWSTO0); //stop
                return;
             }
             else
             {
                i++;
             }
        }
        (*(pfnCallback))(pvBuff,u16Length);
    }
    return;
}

void I2C_vReceiveBuffMaster(void* pvBuff, uint16 u16Length, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress)
{
    I2C_HND->u8TWCR |= (1<<TWINT0) | (1<<TWSTA0) | (1<<TWEN0); // start
    while(!((I2C_HND->u8TWCR)&(1<<TWINT0)));
    if((I2C_HND->u8TWSR & 0xF8)==0x08)
    {
        I2C_HND->u8TWDR = u8SlaveAddress;
        I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0);
        while(!((I2C_HND->u8TWCR)&(1<<TWINT0)));
    }
    if((I2C_HND->u8TWSR & 0xF8)==0x40)
    {
        for(int i = 0 ; i < u16Length ; )
        {
            if(i == u16Length-1)
            {
                I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0);
            }
            else
            {
                I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0) | (1<<TWEA0);
            }
            while(!((I2C_HND->u8TWCR)&(1<<TWINT0)));
            if((I2C_HND->u8TWSR & 0xF8)==0x48 || (I2C_HND->u8TWSR & 0xF8)==0x58 )
            {
                I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0) | (1<<TWSTO0); //stop
                return;
            }
            else
            {
                ((uint8*)pvBuff)[i]= I2C_HND->u8TWDR;
                i++;
            }

        }
           (*(pfnCallback))(pvBuff,u16Length);
    }

    return;
}

void I2C_vTransmitBuffTimeoutMaster(void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress)
{
    I2C_HND->u8TWCR |= (1<<TWINT0) | (1<<TWSTA0) | (1<<TWEN0); // start
    while(!((I2C_HND->u8TWCR)&(1<<TWINT0))&& u16Timeout--) ;
    if((I2C_HND->u8TWSR & 0xF8)==0x08)
    {
        I2C_HND->u8TWDR = u8SlaveAddress;
        I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0);
        while(!((I2C_HND->u8TWCR)&(1<<TWINT0))&& u16Timeout--);
    }
    if((I2C_HND->u8TWSR & 0xF8)==0x18)
    {
        for(int i = 0 ; i < u16Length ;)
        {
            I2C_HND->u8TWDR = ((uint8*)pvBuff)[i];
            I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0); 
            while(!((I2C_HND->u8TWCR)&(1<<TWINT0)) && u16Timeout--);
            if(!u16Timeout)return;  
             if((I2C_HND->u8TWSR & 0xF8)==0x20 || (I2C_HND->u8TWSR & 0xF8)==0x30)
             {
                  I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0) | (1<<TWSTO0); //stop
                return;
             }
             else
             {
                i++;
             }
        }
        (*(pfnCallback))(pvBuff,u16Length);
    }
    return;
}

void I2C_vReceiveBuffTimeoutMaster(void* pvBuff, uint16 u16Length, uint16 u16Timeout, void (*pfnCallback)(void*, uint16),uint8 u8SlaveAddress)
{
    I2C_HND->u8TWCR |= (1<<TWINT0) | (1<<TWSTA0) | (1<<TWEN0); // start
    while(!((I2C_HND->u8TWCR)&(1<<TWINT0)) && u16Timeout--);
    if((I2C_HND->u8TWSR & 0xF8)==0x08)
    {
        I2C_HND->u8TWDR = u8SlaveAddress;
        I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0);
        while(!((I2C_HND->u8TWCR)&(1<<TWINT0))&& u16Timeout--);
    }
    if((I2C_HND->u8TWSR & 0xF8)==0x40)
    {
        for(int i = 0 ; i < u16Length ; )
        {
            if(i == u16Length-1)
            {
                I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0);
            }
            else
            {
                I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0) | (1<<TWEA0);
            }
            while(!((I2C_HND->u8TWCR)&(1<<TWINT0))&& u16Timeout--)
            if(!u16Timeout)return;
            if((I2C_HND->u8TWSR & 0xF8)==0x48 || (I2C_HND->u8TWSR & 0xF8)==0x58 )
            {
                I2C_HND->u8TWCR |=(1<<TWINT0) | (1<<TWEN0) | (1<<TWSTO0); //stop
                return;
            }
            else
            {
                ((uint8*)pvBuff)[i]= I2C_HND->u8TWDR;
                i++;
            }

        }
           (*(pfnCallback))(pvBuff,u16Length);
    }

    return;    



}
void I2C_vTransmitBuffInterruptMaster(void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16), uint8 u8SlaveAddress)
{
    pvaBuff = pvBuff;
    u16aLength = u16Length;
    pfnaCallback = pfnCallback;
    u8aSlaveAddress = u8SlaveAddress;
    u16aidx = 0;
    vStart();
}

void I2C_vReceiveBuffInterruptMaster(void *pvBuff, uint16 u16Length, void (*pfnCallback)(void *, uint16), uint8 u8SlaveAddress)
{
    pvaBuff = pvBuff;
    u16aLength = u16Length;
    u16aidx = 0;
    pfnaCallback = pfnCallback;
    u8aSlaveAddress = u8SlaveAddress;
    vStart();
}
ISR(TWI_vect)
{
    uint8 status = (I2C_HND->u8TWSR & 0xF8);
    if(status ==0x08 || status == 0x10)
    {
        write(u8aSlaveAddress);
        vNACK();
    }
    else if(status == 0x18 || status == 0x28)
    {
        if(u16aidx < u16aLength)
        {
            write(((uint8*)pvaBuff)[u16aidx++]);
            vNACK();
        }
        else
        {
            vStop();
            (*pfnaCallback)(pvaBuff,u16aLength);
        }
    }
    else if(status == 0x30 || status == 0x20 )
    {
        vStop();
    }
}

/******************************************************************************/
