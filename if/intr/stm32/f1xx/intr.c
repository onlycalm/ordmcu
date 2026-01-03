#include "intr.h"

#ifdef __INTR_H__

#include "typ.h"
#include "err.h"
#include "com.h"
#include "stm32f1xx_hal.h"

#define ER_MOD ER_MOD_INTR

static u8 s_au8IntrPriGrp[] =
{
    NVIC_PRIORITYGROUP_0,
    NVIC_PRIORITYGROUP_1,
    NVIC_PRIORITYGROUP_2,
    NVIC_PRIORITYGROUP_3,
    NVIC_PRIORITYGROUP_4,
};

static IRQn_Type s_aeIrqnPin[] =
{
    EXTI0_IRQn,
    EXTI1_IRQn,
    EXTI2_IRQn,
    EXTI3_IRQn,
    EXTI4_IRQn,
    EXTI9_5_IRQn,
    EXTI15_10_IRQn,
};

er erSetIntrPriMode(const EIntrPriMod eIntrPriMod)
{
    er erRtn = ER_SW_UNKN;

    Asrt((u32)eIntrPriMod < u32GetArrSz(s_au8IntrPriGrp));

    if((u32)eIntrPriMod < u32GetArrSz(s_au8IntrPriGrp))
    {
        HAL_NVIC_SetPriorityGrouping(s_au8IntrPriGrp[eIntrPriMod]);
        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erEnIrqnPin(const EIrqnPin keIrqnPin, bl bEn)
{
    er erRtn = ER_SW_UNKN;

    Asrt(keIrqnPin < u32GetArrSz(s_aeIrqnPin));

    if((u32)keIrqnPin < u32GetArrSz(s_aeIrqnPin))
    {
        if(bEn)
        {
            HAL_NVIC_EnableIRQ(s_aeIrqnPin[keIrqnPin]);
        }
        else
        {
            HAL_NVIC_DisableIRQ(s_aeIrqnPin[keIrqnPin]);
        }

        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erSetIrqnPriPin(const EIrqnPin keIrqnPin, u8 u8PrmtPri, u8 u8RespPri)
{
    er erRtn = ER_SW_UNKN;

    Asrt(keIrqnPin < u32GetArrSz(s_aeIrqnPin));

    if((u32)keIrqnPin < u32GetArrSz(s_aeIrqnPin))
    {
        HAL_NVIC_SetPriority(s_aeIrqnPin[keIrqnPin], u8PrmtPri, u8RespPri);
        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

#endif // __INTR_H__
