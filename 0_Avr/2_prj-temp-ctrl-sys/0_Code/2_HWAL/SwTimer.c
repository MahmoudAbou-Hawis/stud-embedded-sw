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

#include "SwTimer.h"

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

typedef struct 
{
    void (*pfnCallBack)(void*);
    uint8 u8Counter;
    uint8 u8Periodicity;
    void * pvArgs;
    boolean bIsBusy;
    boolean bIsWorking;
} Tasks;

Tasks astTasksArr[SW_TIMER_CFG_TASKS_NUM] = {0};
uint8 u8CounterActiveTasks = 0;

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

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

void vCallback(void* Args)
{
    for(uint8 i = 0; i < SW_TIMER_CFG_TASKS_NUM; i++)
    {
        ++(astTasksArr[i].u8Counter);
        if(astTasksArr[i].bIsBusy && 
           (astTasksArr[i].u8Counter == astTasksArr[i].u8Periodicity) && 
           (astTasksArr[i].bIsWorking))
        {
            if(astTasksArr[i].pfnCallBack != NULL)
            {
                (astTasksArr[i].pfnCallBack)(astTasksArr[i].pvArgs);
                astTasksArr[i].u8Counter = 0;
            }
        }
    }
}

/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/

void  SwTimer_vInit(uint16 u16Payload ,SW_Timer_enmPrescaler prescaler)
{
    Timer1_tstConfig config =
    {
        .enmInterrupt = TIMER1_INTERRUPT_ON,
        .enmMode      = TIMER1_CTC,
        .u16prescaler = prescaler
    };
    Timer1_vInit(&config);
    Timer1_vSetPayload(u16Payload);
    Timer1_vSetCallbackFunc(vCallback,NULL);
}

SwTimer_tenmRetStatus SwTimer_enmMakeTimer(void** ppvHnd , uint16 u16Periodicity,void (*pfnCallbcak)(void*) ,void* pvArgs)
{
    
    for(uint8 i = 0; i < SW_TIMER_CFG_TASKS_NUM; i++)
    {
        if(!astTasksArr[i].bIsBusy)
        {
            astTasksArr[i].pfnCallBack = pfnCallbcak;
            astTasksArr[i].u8Periodicity = u16Periodicity;
            astTasksArr[i].u8Counter = 0;
            astTasksArr[i].pvArgs = pvArgs;
            astTasksArr[i].bIsBusy = TRUE;
            astTasksArr[i].bIsWorking = FALSE;

            
            (*ppvHnd) = (void*)&astTasksArr[i];

            return SW_TIMER_RET_STAT_OK;
        }
    }

    return SW_TIMER_RET_STAT_ERR_FULL;
}

SwTimer_tenmRetStatus SwTimer_enmDeleteTimer(void** ppvHnd)
{
    if ((*ppvHnd) != NULL)
    {
        ((Tasks*)(*ppvHnd))->bIsBusy = FALSE;
        ((Tasks*)(*ppvHnd))->bIsWorking = FALSE;

        if(u8CounterActiveTasks--)
        {
            Timer1_vDisable();
        }

        (*ppvHnd) = NULL;
        return SW_TIMER_RET_STAT_OK;
    }
    return SW_TIMER_RET_STAT_ERR_NOT_FND;
}

SwTimer_tenmRetStatus SwTimer_enmStart(void * pvHnd)
{
    if (pvHnd !=NULL)
    {
        ((Tasks*)(pvHnd))->bIsWorking = TRUE;

        if (++u8CounterActiveTasks)
        {
            Timer1_vEnable();
            return SW_TIMER_RET_STAT_OK;
        }
    }
    return SW_TIMER_RET_STAT_ERR_NOT_FND;
}

SwTimer_tenmRetStatus SwTimer_enmEnd(void * pvHnd)
{
    if (pvHnd != NULL)
    {
        ((Tasks*)(pvHnd))->bIsWorking = FALSE;

        if(u8CounterActiveTasks--)
        {
            Timer1_vDisable();
        }
        return SW_TIMER_RET_STAT_OK;
    }
    else
    {
        return SW_TIMER_RET_STAT_ERR_NOT_FND;
    }
}

/******************************************************************************/