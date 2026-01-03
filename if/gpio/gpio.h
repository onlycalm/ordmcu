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
extern "C"
{
#endif

#include "typ.h"

typedef enum
{
    PT_A,
    PT_B,
    PT_C,
    PT_D,
    PT_E,
    PT_F,
    PT_G,
    PT_H,
    PT_I,
    PT_J,
    PT_K,

    PT_MAX, /*!< Maximum port value, not a valid port. */
} EPt;

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
    PIN_MD_INP,        /*!< Input Floating Mode. */
    PIN_MD_OUTP_PP,    /*!< Output Push Pull Mode. */
    PIN_MD_OUTP_OD,    /*!< Output Open Drain Mode. */
    PIN_MD_AF_PP,      /*!< Alternate Function Push Pull Mode. */
    PIN_MD_AF_OD,      /*!< Alternate Function Open Drain Mode. */
    PIN_MD_AF_INP,     /*!< Alternate Function Input Mode. */
    PIN_MD_ANLG,       /*!< Analog Mode. */
    PIN_MD_IT_RSN,     /*!< External Interrupt Mode with Rising edge trigger
                            detection. */
    PIN_MD_IT_FLG,     /*!< External Interrupt Mode with Falling edge trigger
                            detection. */
    PIN_MD_IT_RSN_FLG, /*!< External Interrupt Mode with
                            Rising/Falling edge trigger detection. */
    PIN_MD_EVT_RSN,    /*!< External Event Mode with Rising edge trigger
                            detection. */
    PIN_MD_EVT_FLG,    /*!< External Event Mode with Falling edge trigger
                            detection. */
    PIN_MD_EVT_RSN_FLG,

    PIN_MD_EVT_MAX, /*!< Maximum mode value, not a valid mode. */
} EPinMd;

typedef enum
{
    PIN_PUL_NONE,
    PIN_PUL_UP,
    PIN_PUL_DN,

    PIN_PUL_MAX, /*!< Maximum pull value, not a valid pull. */
} EPinPul;

typedef enum
{
    PIN_SPD_LW, /*!< Low speed. */
    PIN_SPD_MD, /*!< Medium speed. */
    PIN_SPD_HI, /*!< High speed. */

    PIN_SPD_MAX, /*!< Maximum speed value, not a valid speed. */
} EPinSpd;

typedef enum
{
    PIN_LV_RST, /*!< Reset the pin output to low level. */
    PIN_LV_SET, /*!< Set the pin output to high level. */

    PIN_LV_MAX, /*!< Maximum level value, not a valid level. */
} EPinLv;

typedef struct
{
    EPt ePt;
    EPin ePin;
    EPinMd eMd;
    EPinPul ePul;
    EPinSpd eSpd;
} TPin;

extern er erInitPin(const TPin ktPin);
extern er erInitPinGrp(const TPin* const kpktPin, const u16 ku16ArSz);
extern er erGetPinLv(const EPt kePt, const EPin kePin, EPinLv* const kpkePinLv);
extern er erSetPinLv(const EPt kePt, const EPin kePin, const EPinLv kePinLv);
extern er erTglPinLv(const EPt kePt, const EPin kePin);

#ifdef __cplusplus
}
#endif

#endif // __GPIO_H__
