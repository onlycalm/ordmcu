#ifndef __INTR_H__
#define __INTR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "typ.h"

typedef enum
{
    INTR_PRI_MOD0,
    INTR_PRI_MOD1,
    INTR_PRI_MOD2,
    INTR_PRI_MOD3,
    INTR_PRI_MOD4,
} EIntrPriMod;

typedef enum
{
    IRQN_PIN0,
    IRQN_PIN1,
    IRQN_PIN2,
    IRQN_PIN3,
    IRQN_PIN4,
    IRQN_PIN5_9,
    IRQN_PIN10_15,
} EIrqnPin;

extern er erSetIntrPriMode(const EIntrPriMod eIntrPriMod);
extern er erEnIrqnPin(const EIrqnPin keIrqnPin, bl bEn);
extern er erSetIrqnPriPin(const EIrqnPin keIrqnPin, u8 u8PrmtPri, u8 u8RespPri);

#ifdef __cplusplus
}
#endif

#endif // __INTR_H__
