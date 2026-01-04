#ifndef __INTR_H__
#define __INTR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "typ.h"

typedef enum
{
    INTR_PRI_MOD0,
    INTR_PRI_MOD1,
    INTR_PRI_MOD2,
    INTR_PRI_MOD3,
    INTR_PRI_MOD4,
} EIntrPriMod;

typedef enum
{
    INTR_NUM_PIN0,
    INTR_NUM_PIN1,
    INTR_NUM_PIN2,
    INTR_NUM_PIN3,
    INTR_NUM_PIN4,
    INTR_NUM_PIN5_9,
    INTR_NUM_PIN10_15,
} EIntrNum;

typedef struct
{
    bl bEn;
    EIntrNum keIntrNum;
    u8 u8PrmtPri;
    u8 u8RespPri;
} TIntr;

extern er erEnAlIntr(const bl kbEn);
extern er erSetIntrPriMode(const EIntrPriMod eIntrPriMod);
extern er erEnIntr(const EIntrNum keIntrn, const bl bEn);
extern er erSetIntrPri(const EIntrNum keIntrn, const u8 u8PrmtPri,
                       const u8 u8RespPri);
extern er erCfgIntrGrp(const TIntr* const kpktIntr, const u16 ku16ArrSz);

#ifdef __cplusplus
}
#endif

#endif // __INTR_H__
