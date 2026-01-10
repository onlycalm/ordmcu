#include "clk.h"
#include <stdbool.h>

#ifdef __CLK_H__

#include "typ.h"
#include "err.h"
#include "com.h"
#include "stm32f103xe.h"

#define ER_MOD ER_MOD_CLK

#define REG_RCC_APB1ENR (RCC_BASE + 0x00000010u)
#define REG_RCC_AHBENR (RCC_BASE + 0x00000014u)
#define REG_RCC_APB2ENR (RCC_BASE + 0x00000018u)

typedef struct
{
    u32 u32ClkReg;
    u32 u32ClkEnMsk;
} TClkMap;

static const TClkMap s_katClkMap[] =
{
    // AHB.
    {REG_RCC_AHBENR, RCC_AHBENR_DMA1EN},
    {REG_RCC_AHBENR, RCC_AHBENR_SRAMEN},
    {REG_RCC_AHBENR, RCC_AHBENR_FLITFEN},
    {REG_RCC_AHBENR, RCC_AHBENR_CRCEN},
    {REG_RCC_AHBENR, RCC_AHBENR_DMA2EN},
    {REG_RCC_AHBENR, RCC_AHBENR_FSMCEN},
    {REG_RCC_AHBENR, RCC_AHBENR_SDIOEN},

    // APB1.
    {REG_RCC_AHBENR, RCC_APB1ENR_TIM2EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_TIM3EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_WWDGEN},
    {REG_RCC_AHBENR, RCC_APB1ENR_USART2EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_I2C1EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_CAN1EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_BKPEN},
    {REG_RCC_AHBENR, RCC_APB1ENR_PWREN},
    {REG_RCC_AHBENR, RCC_APB1ENR_TIM4EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_SPI2EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_USART3EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_I2C2EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_USBEN},
    {REG_RCC_AHBENR, RCC_APB1ENR_TIM5EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_TIM6EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_TIM7EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_SPI3EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_UART4EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_UART5EN},
    {REG_RCC_AHBENR, RCC_APB1ENR_DACEN},

    // APB2.
    {REG_RCC_APB2ENR, RCC_APB2ENR_AFIOEN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_IOPAEN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_IOPBEN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_IOPCEN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_IOPDEN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_ADC1EN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_ADC2EN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_TIM1EN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_SPI1EN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_USART1EN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_IOPEEN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_IOPFEN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_IOPGEN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_TIM8EN},
    {REG_RCC_APB2ENR, RCC_APB2ENR_ADC3EN},
};

er erEnClk(const EClk keClk, bl bEn)
{
    er erRtn = ER_SW_UNKN;

    Asrt((u32)keClk < u32GetArrSz(s_katClkMap));

    if((u32)keClk < u32GetArrSz(s_katClkMap))
    {
        if(bEn)
        {
            SetBit(Reg32(s_katClkMap[keClk].u32ClkReg),
                   s_katClkMap[keClk].u32ClkEnMsk);
        }
        else
        {
            RstBit(Reg32(s_katClkMap[keClk].u32ClkReg),
                   s_katClkMap[keClk].u32ClkEnMsk);
        }

        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erEnClkGrp(const EClk* const kpkeClk, const u8 ku8ArrSz)
{
    u8 u8Idx = 0u;
    er erRtn = ER_SUC;

    Asrt(kpkeClk != NULL);
    Asrt(ku8ArrSz > 0u);

    if((kpkeClk != NULL) && (ku8ArrSz > 0u))
    {
        for(u8Idx = 0u; (u8Idx < ku8ArrSz) && (erRtn == ER_SUC); u8Idx++)
        {
            erRtn = erEnClk(kpkeClk[u8Idx], true);
        }
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

#endif // __CLK_H__
