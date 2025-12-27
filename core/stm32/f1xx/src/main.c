#include <stdint.h>
#include "com.h"
#include "main.h"
#include "err.h"
#include "gpio.h"
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

int main(void)
{
    EGpioLv eGpioLv = GPIO_LV_RST;
    TGpio ktGpio[] = {
        {
            .ePt = PORT_B,
            .ePin = PIN_5,
            .eMd = GPIO_MD_OUTP_PP,
            .ePul = GPIO_PUL_DN,
            .eSpd = GPIO_SPD_LW,
        },
        {
            .ePt = PORT_E,
            .ePin = PIN_5,
            .eMd = GPIO_MD_OUTP_PP,
            .ePul = GPIO_PUL_DN,
            .eSpd = GPIO_SPD_LW,
        },
        {
            .ePt = PORT_A,
            .ePin = PIN_0,
            .eMd = GPIO_MD_INP,
            .ePul = GPIO_PUL_NOPL,
            .eSpd = GPIO_SPD_LW,
        },
    };

    HAL_Init();
    SystemClock_Config();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    erInitGpioGrp(ktGpio, u32GetArrSz(ktGpio));

    while(1)
    {
        if((erGetGpioLv(PORT_A, PIN_0, &eGpioLv) == ER_SUC) &&
           (eGpioLv == GPIO_LV_SET))
        {
            erTglGpioLv(PORT_B, PIN_5);
            erTglGpioLv(PORT_E, PIN_5);
            Software_DelayMs(20);
        }
    }
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    while(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    while(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK);
}
