#include "clk.h"
#include <stdbool.h>

#ifdef __CLK_H__

#include "typ.h"
#include "err.h"
#include "com.h"
#include "stm32f103xe.h"

#define ER_MOD ER_MOD_CLK

static u32 s_au32ApbClk[] =
{
    RCC_APB2ENR_IOPAEN,
    RCC_APB2ENR_IOPBEN,
    RCC_APB2ENR_IOPCEN,
    RCC_APB2ENR_IOPDEN,
    RCC_APB2ENR_IOPEEN,
    RCC_APB2ENR_IOPFEN,
    RCC_APB2ENR_IOPGEN,
};

er erEnApbClk(const EApbClk keApbClk, bl bEn)
{
    er erRtn = ER_SW_UNKN;

    Asrt((u32)keApbClk < u32GetArrSz(s_au32ApbClk));

    if((u32)keApbClk < u32GetArrSz(s_au32ApbClk))
    {
        if(bEn)
        {
            SetBit(RCC->APB2ENR, s_au32ApbClk[keApbClk]); // To do: 统一AHB, APB1, APB2配置。
        }
        else
        {
            RstBit(RCC->APB2ENR, s_au32ApbClk[keApbClk]);
        }

        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erEnApbClkGrp(const EApbClk* const kpkeApbClk, const u8 ku8ArrSz)
{
    u8 u8Idx = 0u;
    er erRtn = ER_SUC;

    Asrt(kpkeApbClk != NULL);
    Asrt(ku8ArrSz > 0u);

    if((kpkeApbClk != NULL) && (ku8ArrSz > 0u))
    {
        for(u8Idx = 0u; (u8Idx < ku8ArrSz) && (erRtn == ER_SUC); u8Idx++)
        {
            erRtn = erEnApbClk(kpkeApbClk[u8Idx], true);
        }
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

#endif // __CLK_H__
