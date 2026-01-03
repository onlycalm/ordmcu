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

#include "typ.h"
#include "err.h"
#include "com.h"
#include "stm32f1xx_hal.h"

#define ER_MOD ER_MOD_GPIO

static GPIO_TypeDef* s_atPortMap[] =
{
    GPIOA, // PT_A
    GPIOB, // PT_B
    GPIOC, // PT_C
    GPIOD, // PT_D
    GPIOE, // PT_E
    GPIOF, // PT_F
    GPIOG, // PT_G
};

static u32 s_au32PinMap[] =
{
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

static u32 s_au32MdMap[] =
{
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

static u32 s_au32PulMap[] =
{
    GPIO_NOPULL,   // GPIO_PUL_NOPL
    GPIO_PULLUP,   // GPIO_PUL_UP
    GPIO_PULLDOWN, // GPIO_PUL_DN
};

static u32 s_au32SpdMap[] =
{
    GPIO_SPEED_FREQ_LOW,    // GPIO_SPD_LW
    GPIO_SPEED_FREQ_MEDIUM, // GPIO_SPD_MD
    GPIO_SPEED_FREQ_HIGH,   // GPIO_SPD_HI
};

er erInitPin(const TPin ktPin)
{
    GPIO_InitTypeDef tPt = {0};
    er erRtn = ER_SW_UNKN;

    Asrt((u32)ktPin.ePt < u32GetArrSz(s_atPortMap));
    Asrt((u32)ktPin.ePin < u32GetArrSz(s_au32PinMap));
    Asrt((u32)ktPin.eMd < u32GetArrSz(s_au32MdMap));
    Asrt((u32)ktPin.ePul < u32GetArrSz(s_au32PulMap));
    Asrt((u32)ktPin.eSpd < u32GetArrSz(s_au32SpdMap));

    if(((u32)ktPin.ePt < u32GetArrSz(s_atPortMap)) &&
       ((u32)ktPin.ePin < u32GetArrSz(s_au32PinMap)) &&
       ((u32)ktPin.eMd < u32GetArrSz(s_au32MdMap)) &&
       ((u32)ktPin.ePul < u32GetArrSz(s_au32PulMap)) &&
       ((u32)ktPin.eSpd < u32GetArrSz(s_au32SpdMap)))
    {
        tPt.Pin = s_au32PinMap[ktPin.ePin];
        tPt.Mode = s_au32MdMap[ktPin.eMd];
        tPt.Pull = s_au32PulMap[ktPin.ePul];
        tPt.Speed = s_au32SpdMap[ktPin.eSpd];

        HAL_GPIO_Init(s_atPortMap[ktPin.ePt], &tPt);
        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erInitPinGrp(const TPin* const kpktPin, const u16 ku16ArrSz)
{
    u16 u16Idx = 0u;
    er erRtn = ER_SUC;

    Asrt(kpktPin != NULL);
    Asrt(ku16ArrSz > 0u);

    if((kpktPin != NULL) && (ku16ArrSz > 0u))
    {
        for(u16Idx = 0u; (u16Idx < ku16ArrSz) && (erRtn == ER_SUC); u16Idx++)
        {
            erRtn = erInitPin(kpktPin[u16Idx]);
        }
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erGetPinLv(const EPt kePt, const EPin kePin, EPinLv* const kpkePinLv)
{
    er erRtn = ER_SW_UNKN;

    Asrt((u32)kePt < u32GetArrSz(s_atPortMap));
    Asrt((u32)kePin < u32GetArrSz(s_au32PinMap));
    Asrt(kpkePinLv != NULL);

    if(((u32)kePt < u32GetArrSz(s_atPortMap)) &&
       ((u32)kePin < u32GetArrSz(s_au32PinMap)) && (kpkePinLv != NULL))
    {
        *kpkePinLv =
            (EPinLv)HAL_GPIO_ReadPin(s_atPortMap[kePt], s_au32PinMap[kePin]);
        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erSetPinLv(const EPt kePt, const EPin kePin, const EPinLv kePinLv)
{
    er erRtn = ER_SW_UNKN;

    Asrt((u32)kePt < u32GetArrSz(s_atPortMap));
    Asrt((u32)kePin < u32GetArrSz(s_au32PinMap));
    Asrt((u32)kePinLv < (u32)PIN_LV_MAX);

    if(((u32)kePt < u32GetArrSz(s_atPortMap)) &&
       ((u32)kePin < u32GetArrSz(s_au32PinMap)))
    {
        HAL_GPIO_WritePin(s_atPortMap[kePt],
                          s_au32PinMap[kePin],
                          (GPIO_PinState)kePinLv);
        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erTglPinLv(const EPt kePt, const EPin kePin)
{
    er erRtn = ER_SW_UNKN;

    Asrt((u32)kePt < u32GetArrSz(s_atPortMap));
    Asrt((u32)kePin < u32GetArrSz(s_au32PinMap));

    if(((u32)kePt < u32GetArrSz(s_atPortMap)) &&
       ((u32)kePin < u32GetArrSz(s_au32PinMap)))
    {
        HAL_GPIO_TogglePin(s_atPortMap[kePt], s_au32PinMap[kePin]);
        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

#endif // __GPIO_H__
