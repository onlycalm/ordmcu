#ifndef __CLK_H__
#define __CLK_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "typ.h"

typedef enum
{
    // AHB.
    CLK_DMA1,
    CLK_SRAM,
    CLK_FLITF,
    CLK_CRC,
    CLK_DMA2,
    CLK_FSMC,
    CLK_SDIO,

    // APB1.
    CLK_TIM2,
    CLK_TIM3,
    CLK_WWDG,
    CLK_USART2,
    CLK_I2C1,
    CLK_CAN1,
    CLK_BKP,
    CLK_PWR,
    CLK_TIM4,
    CLK_SPI2,
    CLK_USART3,
    CLK_I2C2,
    CLK_USB,
    CLK_TIM5,
    CLK_TIM6,
    CLK_TIM7,
    CLK_SPI3,
    CLK_UART4,
    CLK_UART5,
    CLK_DAC,

    // APB2.
    CLK_AFIO,
    CLK_PT_A,
    CLK_PT_B,
    CLK_PT_C,
    CLK_PT_D,
    CLK_ADC1,
    CLK_ADC2,
    CLK_TIM1,
    CLK_SPI1,
    CLK_USART1,
    CLK_PT_E,
    CLK_PT_F,
    CLK_PT_G,
    CLK_TIM8,
    CLK_ADC3,
} EClk;

extern er erEnClk(const EClk keClk, bl bEn);
extern er erEnClkGrp(const EClk* const kpkeClk, const u8 ku8ArrSz);

#ifdef __cplusplus
}
#endif

#endif // __CLK_H__
