/******************************************************************************/
/**
 * @file Termianl.c
 * @brief The source file of the implemation of a simple termianl
 *
 * @par Project Name
 * Terminal Project
 *
 * @par Code Language
 * C
 *
 * @par Description
 * The source file of the implemation of a simple termianl
 * 
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/

#include "Terminal.h"

/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

#define RED_LED_PIN         0
#define BLUE_LED_PIN        1
#define GREEN_LED_PIN       2 

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
    uint16 u16Size;
    uint16 *pu16Numbers;
    uint8 *pu8Signs;

} tstCalculator;

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

static sint16 s16Sum = 0;
/* Initialization */
static uint8 au8Buffer[100] = {'0'};
static uint8 au8Command[30];
static uint8 au8Procss[30];
static uint16 au16Numbers[30];
static uint8 au8Signs[30];
static tstCalculator stCalculator;
static uint8 au8Result[30];
static uint8 au8Serial[30];
static bool bIsOperandNotProcessed = 0;
static void* pvUart;

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

static sint16 s16Calculate(uint16 u16LastNumber, uint16 u16SignIndex, uint16 u16Index, tstCalculator *pstCal);
static uint16 u16ProcessCalculatorSentData(uint8 au8SentData[], uint16 au16Num[], uint8 au8sign[], uint16 u16Size);
static void vAnalsysOperand(uint8 *au8pDataSent ,uint8 *au8pCommand , uint8 *au8pProcess,uint16 u16Length);
static bool bIsEqual(uint8 *au8pFirstString, uint8 *au8pSecondString);
static uint16 u16GetLength(uint8 *au8pString);
static void vReverseString(uint8* au8pString, uint16 u16Length);
static void vConvResultToCharArr(int Number, uint8* au8pResult);
static void vCheckEnd(void* au8pvBuffer, uint16 u16Length);

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/

static sint16 s16Calculate(uint16 u16LastNumber, uint16 u16SignIndex, uint16 u16Index, tstCalculator *pstCal)
{
    if (u16Index == pstCal->u16Size-1)
    {
        if(pstCal->pu8Signs[u16SignIndex] == '+' || pstCal->pu8Signs[u16SignIndex]=='-')
        {
            s16Sum+=(u16LastNumber + ((pstCal->pu16Numbers[u16Index])*((pstCal->pu8Signs[u16SignIndex] == '+')?1:-1)));
        }
        else
        {
            if(pstCal->pu8Signs[u16SignIndex] == '*')
            {
                s16Sum+=(u16LastNumber * ((pstCal->pu16Numbers[u16Index])*((pstCal->pu8Signs[u16SignIndex+1] == '+')?1:-1)));
            }
            else
            {
                s16Sum+=(u16LastNumber / ((pstCal->pu16Numbers[u16Index])*((pstCal->pu8Signs[u16SignIndex+1] == '+')?1:-1)));
            }
        }
        return s16Sum;
    }
    if (pstCal->pu8Signs[u16SignIndex] == '+' || pstCal->pu8Signs[u16SignIndex]=='-' )
    {
        s16Sum+=u16LastNumber;
        return s16Calculate(pstCal->pu16Numbers[u16Index]*((pstCal->pu8Signs[u16SignIndex] == '+')?1:-1),u16SignIndex+1 ,u16Index+1,pstCal );
    }
    else if (pstCal->pu8Signs[u16SignIndex] == '*' )
    {
       return s16Calculate(u16LastNumber * (pstCal->pu16Numbers[u16Index]*((pstCal->pu8Signs[u16SignIndex+1] == '+')?1:-1)),u16SignIndex+2,u16Index+1,pstCal);
    }
    else
    {
       return s16Calculate(u16LastNumber / (pstCal->pu16Numbers[u16Index]*((pstCal->pu8Signs[u16SignIndex+1] == '+')?1:-1)),u16SignIndex+2,u16Index+1,pstCal);
    }
}

static uint16 u16ProcessCalculatorSentData(uint8 au8SentData[], uint16 au16Num[], uint8 au8sign[], uint16 u16Size)
{
    int idxsign =0;
    int idxNum = 0;
    int Number = -1;
    int s= 1;
    s16Sum = 0;
    for(int i = 0 ;i < u16Size ;i++)
    {
        if(au8SentData[i]-'0' >=0 && au8SentData[i]-'0' <=10)
        {
            if(i==0||!(au8SentData[i-1]-'0' >=0 && au8SentData[i-1]-'0' <=10))
            {
                if(i==0 || (au8SentData[i-1] == '*' || au8SentData[i-1] == '/' ))
                {
                    au8sign[idxsign++] = '+';
                }
                Number =0;
            }
            Number+=au8SentData[i]-'0';
            Number*=10;
        }
        else
        {
            if (Number != -1)
            {
                au16Num[idxNum++] = (Number / 10);
                Number = -1;
                s++;
            }
            au8sign[idxsign++] = au8SentData[i];
        }
    }
    au16Num[idxNum++] = (Number / 10);
    au8sign[idxsign]='\0';
    return s;
}

static void vAnalsysOperand(uint8 *au8pDataSent ,uint8 *au8pCommand , uint8 *au8pProcess,uint16 u16Length)
{
    uint16 keyIndex =0;
    int i = 0;
    for(i ; i < u16Length ; i++)
    {
        if(keyIndex==0 &&(au8pDataSent)[i] != ' ')
        { 
         au8pCommand[i]=(au8pDataSent)[i] ;
        }
        else
        {
            if((au8pDataSent)[i] == ' ')
            {
                keyIndex = i+1; 
                au8pCommand[i] = '\0';
            }
            else
            {
                au8pProcess[i-keyIndex] = (au8pDataSent)[i];
            }
        }
    }
    au8pProcess[i-keyIndex] = '\0';
}

static bool bIsEqual(uint8 *au8pFirstString, uint8 *au8pSecondString)
{
    for(int i = 0; (au8pFirstString[i] != '\0' || au8pSecondString[i] != '\0' ); i++)
    {
        if(au8pFirstString[i] != au8pSecondString[i])
        {
            return false;
        }
    }

    return true;
}

static uint16 u16GetLength(uint8 *au8pString)
{
    int len = 0;
    for(len; au8pString[len]!='\0'; len++);
    return len;
}

static void vReverseString(uint8* au8pString, uint16 u16Length)
{
    uint8 temp;
    for(int i = 0 ; i < u16Length/2 ; i++)
    {
        temp = au8pString[i];
        au8pString[i] = au8pString[(u16Length-1)-i];
        au8pString[(u16Length-1)-i] = temp;
    }
}

static void vConvResultToCharArr(int Number, uint8* au8pResult)
{
    int i = 0;
    bool negative = (Number<0)?Number*=-1:0;
    while(Number)
    {
        au8pResult[i++] = (Number%10)+'0';
        Number /= 10;
    }
    if(negative)au8pResult[i++] = '-';
    au8pResult[i] = '\0';
    vReverseString(au8pResult, i);
}

static void vCheckEnd(void* au8pvBuffer, uint16 u16Length)
{
    if(((uint8*)au8pvBuffer)[0] != ';')
    {
        Uart_vReceiveBuffInterrupt(pvUart,(void*)(au8pvBuffer+1), 1, vCheckEnd);
    }
    else
    {
        ((uint8*)au8pvBuffer)[1] = '\0';
        vAnalsysOperand(au8Buffer,au8Command, au8Procss, u16GetLength(au8Buffer)-1);
        Uart_vReceiveBuffInterrupt(pvUart,(void*)au8Buffer, 1, vCheckEnd);
        bIsOperandNotProcessed = true ;
    }
}

/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/

void Terminal_vInit(void)
{
    Uart_tstInitConfig stConfigrations = {
    .u8UartIdx       = UART1,
    .enmCharSize     = UART_SIZE_8,
    .enmParityType   = UART_PARITY_NONE,
    .u32BaudRate     = 9600,
    .u32SystemClock  = 16000000.0,
    .u8Direction     = UART_DIR_TX | UART_DIR_RX ,
    .u8InterruptType = UART_INTERRUPT_RX | UART_INTERRUPT_TX,
    .enmStopBits     = UART_STOP_1

    };


    pvUart = Uart_pvInit(&stConfigrations);

    /*Global Interrupt Enable*/
    sei();
   

    Gpio_vPinMode(GPIO_B,RED_LED_PIN,GPIO_LEVEL_HIGH);
    Gpio_vPinMode(GPIO_B,GREEN_LED_PIN,GPIO_LEVEL_HIGH);
    Gpio_vPinMode(GPIO_B,BLUE_LED_PIN,GPIO_LEVEL_HIGH);
    Uart_vReceiveBuffInterrupt(pvUart,au8Buffer,1,vCheckEnd);
}

void Terminal_vMain(void)
{
    if (bIsOperandNotProcessed)
    {
        if (bIsEqual("Cal", au8Command))
        {
            stCalculator.u16Size = u16ProcessCalculatorSentData(au8Procss, au16Numbers, au8Signs, u16GetLength(au8Procss));
            stCalculator.pu8Signs = au8Signs;
            stCalculator.pu16Numbers = au16Numbers;
            uint16 n = s16Calculate(0, 0, 0, &stCalculator);
            vConvResultToCharArr(n, au8Result);
            Uart_vTransmitBuffInterrupt(pvUart, au8Result, u16GetLength(au8Result), NULL);
            _delay_ms(10);
            Uart_vTransmitBuffInterrupt(pvUart,(void *)"\n", 1, NULL);
        }
        else if (bIsEqual("LED", au8Command))
        {
            if (bIsEqual("RED", au8Procss))
            {
                Gpio_vDigitalWrite(GPIO_B, GREEN_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, BLUE_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, RED_LED_PIN, GPIO_LEVEL_HIGH);
            }
            else if (bIsEqual("GREEN", au8Procss))
            {
                Gpio_vDigitalWrite(GPIO_B, RED_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, BLUE_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, GREEN_LED_PIN, GPIO_LEVEL_HIGH);
            }
            else if (bIsEqual("BLUE", au8Procss))
            {
                Gpio_vDigitalWrite(GPIO_B, RED_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, GREEN_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, BLUE_LED_PIN, GPIO_LEVEL_HIGH);
            }
            else if (bIsEqual("TURQUOSE", au8Procss))
            {
                Gpio_vDigitalWrite(GPIO_B, RED_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, GREEN_LED_PIN, GPIO_LEVEL_HIGH);
                Gpio_vDigitalWrite(GPIO_B, BLUE_LED_PIN, GPIO_LEVEL_HIGH);
            }
            else if (bIsEqual("ORANGE", au8Procss))
            {
                Gpio_vDigitalWrite(GPIO_B, RED_LED_PIN, GPIO_LEVEL_HIGH);
                Gpio_vDigitalWrite(GPIO_B, GREEN_LED_PIN, GPIO_LEVEL_HIGH);
                Gpio_vDigitalWrite(GPIO_B, BLUE_LED_PIN, GPIO_LEVEL_LOW);
            }
            else if (bIsEqual("PURPLE", au8Procss))
            {
                Gpio_vDigitalWrite(GPIO_B, RED_LED_PIN, GPIO_LEVEL_HIGH);
                Gpio_vDigitalWrite(GPIO_B, GREEN_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, BLUE_LED_PIN, GPIO_LEVEL_HIGH);
            }
            else if (bIsEqual("WHITE", au8Procss))
            {
                Gpio_vDigitalWrite(GPIO_B, RED_LED_PIN, GPIO_LEVEL_HIGH);
                Gpio_vDigitalWrite(GPIO_B, GREEN_LED_PIN, GPIO_LEVEL_HIGH);
                Gpio_vDigitalWrite(GPIO_B, BLUE_LED_PIN, GPIO_LEVEL_HIGH);
            }
            else if (bIsEqual("OFF", au8Procss))
            {
                Gpio_vDigitalWrite(GPIO_B, RED_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, GREEN_LED_PIN, GPIO_LEVEL_LOW);
                Gpio_vDigitalWrite(GPIO_B, BLUE_LED_PIN, GPIO_LEVEL_LOW);
            }
            Uart_vTransmitBuffInterrupt(pvUart,(void *)"ACK\n", 4, NULL);
        }
        else
        {
            if (bIsEqual("SET", au8Command))
            {
                int i = 0;
                for (; i < u16GetLength(au8Procss); i++)
                {
                    au8Serial[i] = au8Procss[i];
                }
                au8Serial[i] = '\0';
            }
            else
            {
                Uart_vTransmitBuff(pvUart,au8Serial, u16GetLength(au8Serial), NULL);
            }
        }
        bIsOperandNotProcessed = false;
    }
}

/******************************************************************************/
