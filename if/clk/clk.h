#ifndef __CLK_H__
#define __CLK_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "typ.h"

typedef enum
{
    CLK_PT_A,
    CLK_PT_B,
    CLK_PT_C,
    CLK_PT_D,
    CLK_PT_E,
    CLK_PT_F,
    CLK_PT_G,
    CLK_PT_H,
    CLK_PT_I,
    CLK_PT_J,
    CLK_PT_K,
} EApbClk;

extern er erEnApbClk(const EApbClk keApbClk, bl bEn);
extern er erEnApbClkGrp(const EApbClk* const kpkeApbClk, const u8 ku8ArrSz);

#ifdef __cplusplus
}
#endif

#endif // __CLK_H__
