/******************************************************************************/
/**
 * @file <file-name>.c
 * @brief <file-short-description>
 *
 * @par Project Name
 * <project-name>
 *
 * @par Code Language
 * C
 *
 * @par Description
 * <file-long-description>
 * 
 * @par Author
 * <author-name>
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

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/
int sum = 0;
/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DEFINITIONS */
/******************************************************************************/
int terminal_vCalculate(uint16 u16LastNumber , uint16 u16SignIndex ,uint16 u16Index, terminal_tstCalculator *tstCal)
{
    if(u16Index == tstCal->u16Size-1) {
        if(tstCal->u8ptrSigns[u16SignIndex] == '+' || tstCal->u8ptrSigns[u16SignIndex]=='-' )
        {
            sum+=(u16LastNumber + ((tstCal->u16ptrNumbers[u16Index])*((tstCal->u8ptrSigns[u16SignIndex] == '+')?1:-1)));
        }
        else
        {
            if(tstCal->u8ptrSigns[u16SignIndex] == '*')
                sum+=(u16LastNumber * ((tstCal->u16ptrNumbers[u16Index])*((tstCal->u8ptrSigns[u16SignIndex+1] == '+')?1:-1)));
            else
                sum+=(u16LastNumber / ((tstCal->u16ptrNumbers[u16Index])*((tstCal->u8ptrSigns[u16SignIndex+1] == '+')?1:-1)));

        }
        return sum;
    }
    if(tstCal->u8ptrSigns[u16SignIndex] == '+' || tstCal->u8ptrSigns[u16SignIndex]=='-' )
    {
        sum+=u16LastNumber;
        return terminal_vCalculate(tstCal->u16ptrNumbers[u16Index]*((tstCal->u8ptrSigns[u16SignIndex] == '+')?1:-1),u16SignIndex+1 ,u16Index+1,tstCal );
    }
    else if(tstCal->u8ptrSigns[u16SignIndex] == '*' )
    {
       return terminal_vCalculate(u16LastNumber * (tstCal->u16ptrNumbers[u16Index]*((tstCal->u8ptrSigns[u16SignIndex+1] == '+')?1:-1)),u16SignIndex+2,u16Index+1,tstCal);
    }
    else
    {
       return terminal_vCalculate(u16LastNumber / (tstCal->u16ptrNumbers[u16Index]*((tstCal->u8ptrSigns[u16SignIndex+1] == '+')?1:-1)),u16SignIndex+2,u16Index+1,tstCal);
    }
}

uint16 terminal_u16ProcessCalculatorSentData(uint8 u8SentData[],uint16 u16Num[] ,uint8 u8sign[] , uint16 u16Size)
{
    int idxsign =0;
    int idxNum = 0;
    int Number = -1;
    int s= 1;
    sum = 0;
    for(int i = 0 ;i < u16Size ;i++)
    {
        if(u8SentData[i]-'0' >=0 && u8SentData[i]-'0' <=10)
        {
            if(i==0||!(u8SentData[i-1]-'0' >=0 && u8SentData[i-1]-'0' <=10)){
                if(i==0 || (u8SentData[i-1] == '*' || u8SentData[i-1] == '/' ))
                    u8sign[idxsign++] = '+';
                Number =0;
            }
            Number+=u8SentData[i]-'0';
            Number*=10;
        }else{
            if(Number != -1) {
                u16Num[idxNum++] = (Number / 10);
                Number = -1;
                s++;
            }
            u8sign[idxsign++] = u8SentData[i];
        }
    }
    u16Num[idxNum++] = (Number / 10);
    u8sign[idxsign]='\0';
    return s;
}

void terminal_vAnalsysOperand(uint8 *DataSent ,uint8 *u8Command , uint8 *u8Process,uint16 u16Length  )
{
    uint16 keyIndex =0;
    int i = 0;
    for(i ; i < u16Length ; i++)
    {
        if( keyIndex==0 &&(DataSent)[i] != ' ' )
        { 
         u8Command[i]=(DataSent)[i] ;
        }
        else
        {
            if((DataSent)[i] == ' ')
            {
                keyIndex = i+1; 
                u8Command[i] = '\0';
            }
            else
            {
                u8Process[i-keyIndex] = (DataSent)[i];
            }
        }
    }
     u8Process[i-keyIndex] = '\0';
}

bool IsEqual(uint8 *ptrFirstString ,uint8 *ptrSecondString)
{
    for(int i = 0 ; (ptrFirstString[i] != '\0' || ptrSecondString[i] != '\0' ) ;i++)
    {
        if(ptrFirstString[i] != ptrSecondString[i])
        {
            return false;
        }
    }
  return true;
}

uint16 u16length(uint8 *String)
{
    int len = 0;
    for(len ; String[len]!='\0';len++);
    return len;
}

void Convert(int Number,uint8 *result )
{
    uint8 r[30];
    int i = 0;
    bool negative = false;
    if(Number < 0)
    {
        result[0]='-';
        Number*=-1;
        negative = true;
    }
    for( i; Number ; i++)
    {
        r[i] = (Number%10)+'0';

        Number/=10;
    }
    for(int e = i-1 ; e >= 0 ;e--)
    {
        result[(i-((negative)?0:1))-e] = r[e];
    }
    result[i+((negative)?1:0)]='\0';

}

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

/******************************************************************************/
