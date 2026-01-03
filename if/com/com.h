/**
 * @file 文件名（*.h *.c）
 * @brief 该模块功能的简介。
 * @details 使用该模块有哪些细节注意等。
 * @author 创建该文件的人名。
 * @data 该文件的创建日期（2020-03-10）。
 * @version 文件或模块版本号（V1.0.0）。
 * @copyright 版权所属公司。
 */

#ifndef __COM_H__
#define __COM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "comp.h"
#include "typ.h"

#define SetBit(Var, Msk) ((Var) |= (Msk))
#define ClrBit(Var, Msk) ((Var) &= ~(Msk))
#define RdBit(Var, Msk) ((Var) & (Msk))

#if DEBUG
#define Asrt(expr) \
    do { \
        if(!(expr)) \
        { \
            while(1); \
        } \
    } \
    while(0)
#else
#define Asrt(expr) ((void)0)
#endif

#define u32GetArrSz(aArr) ((u32)(sizeof((aArr)) / sizeof((aArr)[0])))
#define u32GetBySz(Var) ((u32)sizeof((Var)))

FORCE_INLINE
void vidWrReg32(u32 u32Adr, u32 u32Val)
{
    *(volatile u32*)u32Adr = u32Val;
}

FORCE_INLINE
u32 u32RdReg32(u32 u32Adr)
{
    return *(volatile u32*)u32Adr;
}

#ifdef __cplusplus
}
#endif

#endif // __COM_H__
