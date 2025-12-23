/**
 * @file gpio.h
 * @brief GPIO module header file.
 * @details This file contains type definitions and function declarations for
 *          the GPIO module, used for initializing and controlling GPIO pins.
 * @author Calm
 * @data 2025-12-21
 * @version v1.0.0
 * @copyright (C) 2025 Ordinary People. This project is open source under
              the MIT License.
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "typ.h"

typedef enum
{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    PORT_H,
    PORT_I,
    PORT_J,
    PORT_K,

    PORT_MAX, /*!< Maximum port value, not a valid port. */
} EPort;

typedef enum
{
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15,

    PIN_MAX, /*!< Maximum pin value, not a valid pin. */
} EPin;

typedef enum
{
    GPIO_MD_INP,     /*!< Input Floating Mode. */
    GPIO_MD_OUTP_PP, /*!< Output Push Pull Mode. */
    GPIO_MD_OUTP_OD, /*!< Output Open Drain Mode. */
    GPIO_MD_AF_PP,   /*!< Alternate Function Push Pull Mode. */
    GPIO_MD_AF_OD,   /*!< Alternate Function Open Drain Mode. */
    GPIO_MD_AF_INP,  /*!< Alternate Function Input Mode. */
    GPIO_MD_ANLG,    /*!< Analog Mode. */
    GPIO_MD_IT_RSN,  /*!< External Interrupt Mode with Rising edge trigger
                          detection. */
    GPIO_MD_IT_FLG,  /*!< External Interrupt Mode with Falling edge trigger
                          detection. */
    GPIO_MD_IT_RSN_FLG, /*!< External Interrupt Mode with
                             Rising/Falling edge trigger detection. */
    GPIO_MD_EVT_RSN,    /*!< External Event Mode with Rising edge trigger
                             detection. */
    GPIO_MD_EVT_FLG,    /*!< External Event Mode with Falling edge trigger
                             detection. */
    GPIO_MD_EVT_RSN_FLG,

    GPIO_MD_EVT_MAX, /*!< Maximum mode value, not a valid mode. */
} EGpioMd;

typedef enum
{
    GPIO_PUL_NOPL,
    GPIO_PUL_UP,
    GPIO_PUL_DN,

    GPIO_PUL_MAX, /*!< Maximum pull value, not a valid pull. */
} EGpioPul;

typedef enum
{
    GPIO_SPD_LW, /*!< Low speed. */
    GPIO_SPD_MD, /*!< Medium speed. */
    GPIO_SPD_HI, /*!< High speed. */

    GPIO_SPD_MAX, /*!< Maximum speed value, not a valid speed. */
} EGpioSpd;

typedef enum
{
    GPIO_LV_RST, /*!< Reset the pin output to low level. */
    GPIO_LV_SET, /*!< Set the pin output to high level. */

    GPIO_LV_MAX, /*!< Maximum level value, not a valid level. */
} EGpioLv;

typedef struct
{
    EPort ePt;
    EPin ePin;
    EGpioMd eMd;
    EGpioPul ePul;
    EGpioSpd eSpd;
} TGpio;

extern er erInitGpio(const TGpio ktGpio);
extern er erInitGpioGrp(const TGpio* const kpktGpio, u16 u16ArSz);
extern er erGetGpioLv(const EPort kePt, const EPin kePin, EGpioLv* const kpkeGpioLv);
extern er erSetGpioLv(const EPort kePt, const EPin kePin,
                      const EGpioLv keGpioLv);
extern er erTglGpioLv(const EPort kePt, const EPin kePin);

#ifdef __cplusplus
}
#endif

#endif // __GPIO_H__
