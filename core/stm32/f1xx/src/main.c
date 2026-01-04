#include <stdbool.h>
#include <stdint.h>
#include "typ.h"
#include "err.h"
#include "com.h"
#include "main.h"
#include "gpio.h"
#include "clk.h"
#include "intr.h"
#include "stm32f1xx_hal_gpio.h"

void SystemClock_Config(void);

void Software_DelayMs(uint32_t ms)
{
#define LOOPS_PER_MS 7200 // 72MHz下的大概值

    for(uint32_t i = 0; i < ms; i++)
    {
        for(uint32_t j = 0; j < LOOPS_PER_MS; j++)
        {
            __asm__("nop"); // 空操作，防止被优化
        }
    }
}

void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_0)
    {
        erTglPinLv(PT_E, PIN_5);
    }
    else
    {
        // Do nothing.
    }
}

int main(void)
{
    EPinLv ePinLv = PIN_LV_RST;
    const TPin katPin[] =
    {
        {
            .ePt = PT_B,
            .ePin = PIN_5,
            .eMd = PIN_MD_OUTP_PP,
            .ePul = PIN_PUL_DN,
            .eSpd = PIN_SPD_LW,
        },
        {
            .ePt = PT_E,
            .ePin = PIN_5,
            .eMd = PIN_MD_OUTP_PP,
            .ePul = PIN_PUL_DN,
            .eSpd = PIN_SPD_LW,
        },
        {
            .ePt = PT_A,
            .ePin = PIN_0,
            .eMd = PIN_MD_IT_RSN,
            .ePul = PIN_PUL_DN,
            .eSpd = PIN_SPD_LW,
        },
    };
    const EApbClk kaeClk[] =
    {
        CLK_PT_A,
        CLK_PT_B,
        CLK_PT_E,
    };
    const TIntr atIntr[] =
    {
        {true, INTR_NUM_PIN0, 0u, 0u},
    };

    erEnAlIntr(true);
    erSetIntrPriMode(INTR_PRI_MOD4);
    HAL_Init();
    SystemClock_Config();

    erEnApbClkGrp(kaeClk, u32GetArrSz(kaeClk));
    erCfgPinGrp(katPin, u32GetArrSz(katPin));
    erCfgIntrGrp(atIntr, u32GetArrSz(atIntr));

    while(1)
    {
        if((erGetPinLv(PT_A, PIN_0, &ePinLv) == ER_SUC) &&
           (ePinLv == PIN_LV_SET))
        {
            erTglPinLv(PT_B, PIN_5);
            Software_DelayMs(80);
        }
        else
        {
            // Do nothing.
        }
    }
}

void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef clkinitstruct = {0};
    RCC_OscInitTypeDef oscinitstruct = {0};

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    oscinitstruct.HSEState = RCC_HSE_ON;
    oscinitstruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
    oscinitstruct.PLL.PLLState = RCC_PLL_ON;
    oscinitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    oscinitstruct.PLL.PLLMUL = RCC_PLL_MUL6;
    if(HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
    clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                               RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV1;
    if(HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_0) != HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }
}
