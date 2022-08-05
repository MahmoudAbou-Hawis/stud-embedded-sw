/******************************************************************************/
/**
 * @file AppCfg.h
 * @brief <file-short-description>
 *
 * @par Project Name
 * Terminal Project
 *
 * @par Code Language
 * C
 *
 * @par Description
 * <file-long-description>
 * 
 * @par Author
 *Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef APP_CFG_H
#define APP_CFG_H
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

/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

#define CFG_APP_MAIN                 0
#define CFG_APP_TEST_TERMINAL        1
#define CFG_APP_TEST_UART            2


#define CURRENT_APP                  CFG_APP_MAIN  

/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

#define CFG_IS_CURRENT_APP(_App) (CURRENT_APP == _App)

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
#endif /* APP_CFG_H */
/******************************************************************************/
