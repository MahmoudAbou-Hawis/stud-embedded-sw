/******************************************************************************/
/**
 * @file <file-name>.h
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
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef <FILE_NAME_H>
#define <FILE_NAME_H>
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
#include "Any.h"
#include <AnyLib.h>

/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 */
/*----------------------------------------------------------------------------*/
#define MODULE_SYMBOL_NAME      ((uint8)9)
/*----------------------------------------------------------------------------*/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 * @param _Arg1 <ARG_1-description>
 * @param _Arg2 <ARG_2-description>
 * @return <return-description>
 */
/*----------------------------------------------------------------------------*/
#define MODULE_MACRO_NAME(_Arg1, _Arg2)      (_Arg1 * _Arg2)
/*----------------------------------------------------------------------------*/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 */
/*----------------------------------------------------------------------------*/
typedef enum
{

    /** @brief <short-description>
     *
     * <long-description-if-needed>
     */
    MODULE_ENUM_1  = 0,

    /** @brief <short-description>
     *
     * <long-description-if-needed>
     */
    MODULE_ENUM_2,

    /** @brief <short-description>
     *
     * <long-description-if-needed>
     */
    MODULE_ENUM_3

} MODULE_tenmEnumName;
/*----------------------------------------------------------------------------*/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 */
/*----------------------------------------------------------------------------*/
typedef struct
{

    /** @brief <short-description>
     *
     * <long-description-if-needed>
     */
    uint8 u8Element1;

    /** @brief <short-description>
     *
     * <long-description-if-needed>
     */
    uint16 u16Element2;

    /** @brief <short-description>
     *
     * <long-description-if-needed>
     */
    float32 f32Element3;

} MODULE_tstStructName;
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 */
/*----------------------------------------------------------------------------*/
typedef union
{

    /** @brief <short-description>
     *
     * <long-description-if-needed>
     */
    uint32 u32Element1;

    /** @brief <short-description>
     *
     * <long-description-if-needed>
     */
    uint64 u64Element2;

    /** @brief <short-description>
     *
     * <long-description-if-needed>
     */
    float64 f64Element3;

} MODULE_tunUnionName;
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 */
/*----------------------------------------------------------------------------*/
typedef MODULE_tstStructName* MODULE_tpstPtrToStructName;
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 */
/*----------------------------------------------------------------------------*/
typedef void (*MODULE_tpfnPtrToFunName) (void);
/*----------------------------------------------------------------------------*/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DECLARATIONS */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 */
/*----------------------------------------------------------------------------*/
extern const sint8 MODULE_cs8ConstantName;
/*----------------------------------------------------------------------------*/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DECLARATIONS */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 */
/*----------------------------------------------------------------------------*/
extern sint32 MODULE_s32VariableName;
/*----------------------------------------------------------------------------*/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION PROTOTYPES */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 * @param[in] u8Arg1 <Arg1-description>
 * @param[in,out] pstArg2 <Arg2-description>
 * @param[out] ps16Arg3 <Arg3-description>
 * @return None
 */
/*----------------------------------------------------------------------------*/
void MODULE_vFun1Name(uint8 u8Arg1, MODULE_tpstPtrToStructName pstArg2,
                     sint16* ps16Arg3);
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 * @param[in] u8Arg1 <Arg1-description>
 * @param[in] pfunArg2 <Arg2-description>
 * @param[out] ps16Arg3 <Arg3-description>
 * @return <return-description>
 */
/*----------------------------------------------------------------------------*/
sint32 MODULE_s32Fun2Name(uint8 u8Arg1, MODULE_tpfnPtrToFunName pfunArg2,
                     sint16* ps16Arg3);
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @brief <short-description>
 *
 * <long-description-if-needed>
 * @param[in] u8Arg1 <Arg1-description>
 * @param[in] u8Arg2 <Arg2-description>
 * @return <return-description>
 */
/*----------------------------------------------------------------------------*/
MODULE_tunUnionName* MODULE_punFun3Name(uint8 u8Arg1, uint u8Arg2);
/*----------------------------------------------------------------------------*/

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
