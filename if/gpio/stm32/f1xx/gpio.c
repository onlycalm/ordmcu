/**
 * @file gpio.c
 * @brief GPIO module source file.
 * @details This file contains type definitions and function declarations for
 *          the GPIO module, used for initializing and controlling GPIO pins.
 * @author Calm
 * @data 2025-12-21
 * @version v1.0.0
 * @copyright (C) 2025 Ordinary People. This project is open source under
              the MIT License.
 */

#include "gpio.h"

#ifdef __GPIO_H__

#include "com.h"
#include "err.h"
#include "stm32f1xx_hal.h"
#include "typ.h"

#define ER_MOD ER_MOD_GPIO

static GPIO_TypeDef* s_atPortMap[] = {
    GPIOA, // PORT_A
    GPIOB, // PORT_B
    GPIOC, // PORT_C
    GPIOD, // PORT_D
    GPIOE, // PORT_E
    GPIOF, // PORT_F
    GPIOG, // PORT_G
};

static u32 s_au32PinMap[] = {
    GPIO_PIN_0,  // PIN_0
    GPIO_PIN_1,  // PIN_1
    GPIO_PIN_2,  // PIN_2
    GPIO_PIN_3,  // PIN_3
    GPIO_PIN_4,  // PIN_4
    GPIO_PIN_5,  // PIN_5
    GPIO_PIN_6,  // PIN_6
    GPIO_PIN_7,  // PIN_7
    GPIO_PIN_8,  // PIN_8
    GPIO_PIN_9,  // PIN_9
    GPIO_PIN_10, // PIN_10
    GPIO_PIN_11, // PIN_11
    GPIO_PIN_12, // PIN_12
    GPIO_PIN_13, // PIN_13
    GPIO_PIN_14, // PIN_14
    GPIO_PIN_15, // Pin_15
};

static u32 s_au32MdMap[] = {
    GPIO_MODE_INPUT,              // GPIO_MD_INP
    GPIO_MODE_OUTPUT_PP,          // GPIO_MD_OUTP_PP
    GPIO_MODE_OUTPUT_OD,          // GPIO_MD_OUTP_OD
    GPIO_MODE_AF_PP,              // GPIO_MD_AF_PP
    GPIO_MODE_AF_OD,              // GPIO_MD_AF_OD
    GPIO_MODE_AF_INPUT,           // GPIO_MD_AF_INP
    GPIO_MODE_ANALOG,             // GPIO_MD_ANLG
    GPIO_MODE_IT_RISING,          // GPIO_MD_IT_RSN
    GPIO_MODE_IT_FALLING,         // GPIO_MD_IT_FLG
    GPIO_MODE_IT_RISING_FALLING,  // GPIO_MD_IT_RSN_FLG
    GPIO_MODE_EVT_RISING,         // GPIO_MD_EVT_RSN
    GPIO_MODE_EVT_FALLING,        // GPIO_MD_EVT_FLG
    GPIO_MODE_EVT_RISING_FALLING, // GPIO_MD_EVT_RSN_FLG
};

static u32 s_au32PulMap[] = {
    GPIO_NOPULL,   // GPIO_PUL_NOPL
    GPIO_PULLUP,   // GPIO_PUL_UP
    GPIO_PULLDOWN, // GPIO_PUL_DN
};

static u32 s_au32SpdMap[] = {
    GPIO_SPEED_FREQ_LOW,    // GPIO_SPD_LW
    GPIO_SPEED_FREQ_MEDIUM, // GPIO_SPD_MD
    GPIO_SPEED_FREQ_HIGH,   // GPIO_SPD_HI
};

er erInitGpio(const TGpio ktGpio)
{
    GPIO_InitTypeDef tGpio = {0};
    er erRtn = ER_SUC;

    Asrt((u32)ktGpio.ePt < u32GetArrSz(s_atPortMap));
    Asrt((u32)ktGpio.ePin < u32GetArrSz(s_au32PinMap));
    Asrt((u32)ktGpio.eMd < u32GetArrSz(s_au32MdMap));
    Asrt((u32)ktGpio.ePul < u32GetArrSz(s_au32PulMap));
    Asrt((u32)ktGpio.eSpd < u32GetArrSz(s_au32SpdMap));

    if(((u32)ktGpio.ePt < u32GetArrSz(s_atPortMap)) &&
       ((u32)ktGpio.ePin < u32GetArrSz(s_au32PinMap)) &&
       ((u32)ktGpio.eMd < u32GetArrSz(s_au32MdMap)) &&
       ((u32)ktGpio.ePul < u32GetArrSz(s_au32PulMap)) &&
       ((u32)ktGpio.eSpd < u32GetArrSz(s_au32SpdMap)))
    {
        tGpio.Pin = s_au32PinMap[ktGpio.ePin];
        tGpio.Mode = s_au32MdMap[ktGpio.eMd];
        tGpio.Pull = s_au32PulMap[ktGpio.ePul];
        tGpio.Speed = s_au32SpdMap[ktGpio.eSpd];

        HAL_GPIO_Init(s_atPortMap[ktGpio.ePt], &tGpio);
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erInitGpioGrp(const TGpio* const kpktGpio, u16 u16ArrSz)
{
    u16 u16Idx = 0u;
    er erRtn = ER_SUC;

    Asrt(kpktGpio != NULL);
    Asrt(u16ArrSz > 0u);

    if((kpktGpio != NULL) && (u16ArrSz > 0))
    {
        for(u16Idx = 0u; (u16Idx < u16ArrSz) && (erRtn != ER_SUC); u16Idx++)
        {
            erRtn = erInitGpio(kpktGpio[u16Idx]);
        }
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erGetGpioLv(const EPort kePt, const EPin kePin, EGpioLv* const kpkeGpioLv)
{
    er erRtn = ER_SUC;

    Asrt((u32)kePt < u32GetArrSz(s_atPortMap));
    Asrt((u32)kePin < u32GetArrSz(s_au32PinMap));
    Asrt(kpkeGpioLv != NULL);

    if(((u32)kePt < u32GetArrSz(s_atPortMap)) && ((u32)kePin < u32GetArrSz(s_au32PinMap)) &&
       (kpkeGpioLv != NULL))
    {
        *kpkeGpioLv =
            (EGpioLv)HAL_GPIO_ReadPin(s_atPortMap[kePt], s_au32PinMap[kePin]);
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erSetGpioLv(const EPort kePt, const EPin kePin, const EGpioLv keGpioLv)
{
    er erRtn = ER_SUC;

    Asrt((u32)kePt < u32GetArrSz(s_atPortMap));
    Asrt((u32)kePin < u32GetArrSz(s_au32PinMap));
    Asrt((u32)keGpioLv < (u32)GPIO_LV_MAX);

    if(((u32)kePt < u32GetArrSz(s_atPortMap)) && ((u32)kePin < u32GetArrSz(s_au32PinMap)))
    {
        HAL_GPIO_WritePin(s_atPortMap[kePt],
                          s_au32PinMap[kePin],
                          (GPIO_PinState)keGpioLv);
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erTglGpioLv(const EPort kePt, const EPin kePin)
{
    er erRtn = ER_SUC;

    Asrt((u32)kePt < u32GetArrSz(s_atPortMap));
    Asrt((u32)kePin < u32GetArrSz(s_au32PinMap));

    if(((u32)kePt < u32GetArrSz(s_atPortMap)) && ((u32)kePin < u32GetArrSz(s_au32PinMap)))
    {
        HAL_GPIO_TogglePin(s_atPortMap[kePt], s_au32PinMap[kePin]);
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

#endif // __GPIO_H__
