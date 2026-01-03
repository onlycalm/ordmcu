#include "clk.h"

#ifdef __CLK_H__

#include "typ.h"
#include "err.h"
#include "com.h"
#include "stm32f103xe.h"

#define ER_MOD ER_MOD_CLK

static u32 s_au32ClkPtEn[] =
{
    RCC_APB2ENR_IOPAEN,
    RCC_APB2ENR_IOPBEN,
    RCC_APB2ENR_IOPCEN,
    RCC_APB2ENR_IOPDEN,
    RCC_APB2ENR_IOPEEN,
    RCC_APB2ENR_IOPFEN,
    RCC_APB2ENR_IOPGEN,
};

er erSetClkPt(const EClkPt keClkPt)
{
    er erRtn = ER_SW_UNKN;

    Asrt((u32)keClkPt < u32GetArrSz(s_au32ClkPtEn));

    if((u32)keClkPt < u32GetArrSz(s_au32ClkPtEn))
    {
        SetBit(RCC->APB2ENR, s_au32ClkPtEn[keClkPt]);
        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erSetClkPtGrp(const EClkPt* const kpkeClkPt, const u8 ku8ArrSz)
{
    u8 u8Idx = 0u;
    er erRtn = ER_SUC;

    Asrt(kpkeClkPt != NULL);
    Asrt(ku8ArrSz > 0u);

    if((kpkeClkPt != NULL) && (ku8ArrSz > 0u))
    {
        for(u8Idx = 0u; (u8Idx < ku8ArrSz) && (erRtn == ER_SUC); u8Idx++)
        {
            erRtn = erSetClkPt(kpkeClkPt[u8Idx]);
        }
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

#endif // __CLK_H__
