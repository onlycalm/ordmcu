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

static IRQn_Type s_aeIntrNum[] =
{
    EXTI0_IRQn,
    EXTI1_IRQn,
    EXTI2_IRQn,
    EXTI3_IRQn,
    EXTI4_IRQn,
    EXTI9_5_IRQn,
    EXTI15_10_IRQn,
};

er erEnAlIntr(const bl kbEn)
{
    if(kbEn)
    {
        __enable_irq();
    }
    else
    {
        __disable_irq();
    }

    return ER_SUC;
}

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

er erEnIntr(const EIntrNum keIntrNum, const bl kbEn)
{
    er erRtn = ER_SW_UNKN;

    Asrt(keIntrNum < u32GetArrSz(s_aeIntrNum));

    if((u32)keIntrNum < u32GetArrSz(s_aeIntrNum))
    {
        if(kbEn)
        {
            HAL_NVIC_EnableIRQ(s_aeIntrNum[keIntrNum]);
        }
        else
        {
            HAL_NVIC_DisableIRQ(s_aeIntrNum[keIntrNum]);
        }

        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erSetIntrPri(const EIntrNum keIntrNum, const u8 ku8PrmtPri,
                const u8 ku8RespPri)
{
    er erRtn = ER_SW_UNKN;

    Asrt(keIntrNum < u32GetArrSz(s_aeIntrNum));

    if((u32)keIntrNum < u32GetArrSz(s_aeIntrNum))
    {
        HAL_NVIC_SetPriority(s_aeIntrNum[keIntrNum], ku8PrmtPri, ku8RespPri);
        erRtn = ER_SUC;
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

er erCfgIntrGrp(const TIntr* const kpktIntr, const u16 ku16ArrSz)
{
    u16 u16Idx = 0u;
    er erRtn = ER_SUC;

    Asrt(kpktIntr != NULL);
    Asrt(ku16ArrSz > 0u);

    if((kpktIntr != NULL) && (ku16ArrSz > 0u))
    {
        for(u16Idx = 0u; (u16Idx < ku16ArrSz) && (erRtn == ER_SUC); u16Idx++)
        {
            erRtn = erEnIntr(kpktIntr[u16Idx].keIntrNum, kpktIntr[u16Idx].bEn);

            if(erRtn == ER_SUC)
            {
                erRtn = erSetIntrPri(kpktIntr[u16Idx].keIntrNum,
                                     kpktIntr[u16Idx].u8PrmtPri,
                                     kpktIntr[u16Idx].u8RespPri);
            }
            else
            {
                // Do nothing.
            }
        }
    }
    else
    {
        erRtn = ER_SW_INV_PARAM;
    }

    return erRtn;
}

#endif // __INTR_H__
