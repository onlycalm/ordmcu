/**
 * @file err.h
 * @brief err Module
 * @details This file contains type definitions and function declarations for
 *          the GPIO module, used for initializing and controlling GPIO pins.
 * @author Calm
 * @data 2025-12-21
 * @version v1.0.0
 * @copyright (C) 2025 Ordinary People. This project is open source under
              the MIT License.
 */

#ifndef __ERR_H__
#define __ERR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "typ.h"

#ifndef ER_DOM
#error Please define ER_DOM
#endif

#ifndef ER_SUB_DOM
#error Please define ER_SUB_DOM
#endif

#define u32PkgEr(eLv, eCd, eCls, eMod, eSubDom, eDom) \
    ((((u32)(eLv)&0x07u) << 0) | (((u32)(eCd)&0x3Fu) << 3) | \
     (((u32)(eCls)&0x1Fu) << 9) | (((u32)(eMod)&0xFFu) << 14) | \
     (((u32)(eSubDom)&0x0Fu) << 22) | (((u32)(eDom)&0x0Fu) << 26))

#define u32GetErLv(erEr)     ((u32)(((erEr) >> 0) & 0x07u))
#define u32GetErCd(erEr)     ((u32)(((erEr) >> 3) & 0x3Fu))
#define u32GetErCls(erEr)    ((u32)(((erEr) >> 9) & 0x1Fu))
#define u32GetErMod(erEr)    ((u32)(((erEr) >> 14) & 0xFFu))
#define u32GetErSubDom(erEr) ((u32)(((erEr) >> 22) & 0x0Fu))
#define u32GetErDom(erEr)    ((u32)(((erEr) >> 26) & 0x0Fu))

#define u32PkgClsEr(eLv, eCd, eCls) u32PkgEr((eLv), (eCd), (eCls), (ER_MOD), \
                                             (ER_SUB_DOM), (ER_DOM))

// Error code.
#define ER_SUC 0u

// Software Class.
#define ER_SW_UNKN \
    u32PkgClsEr((ER_LV_ER), (ER_CD_SW_UNKN), (ER_CLS_SW))
#define ER_SW_NUL_PTR \
    u32PkgClsEr((ER_LV_ER), (ER_CD_SW_NUL_PTR), (ER_CLS_SW))
#define ER_SW_INV_PARAM \
    u32PkgClsEr((ER_LV_ER), (ER_CD_SW_INV_PARAM), (ER_CLS_SW))

typedef union
{
    struct
    {
        u32 btLv     : 3; // [2:0] Error level.
        u32 btCd     : 6; // [8:3] Error code.
        u32 btCls    : 5; // [13:9] Class.
        u32 btMod    : 8; // [21:14] Module ID.
        u32 btSubDom : 4; // [25:22] Sub-Domain.
        u32 btDom    : 4; // [29:26] Domain.
        u32 Rsv      : 2; // [31:30] Reserved.
    } bt;

    u32 al;
} UEr;

typedef enum
{
    ER_LV_SUC, // The other bits should be zero, indicating no fault.
    ER_LV_WRN,
    ER_LV_ER,
    ER_LV_CRIT,
} EErLv;

typedef enum
{
    ER_CD_COMM_ACK_TMOT,   // Timeout Error.
    ER_CD_COMM_TX_BUF_FUL, // Transmit Buffer Full.
    ER_CD_COMM_RX_BUF_FUL, // Receive Buffer Full.
} EErCdComm;

typedef enum
{
    ER_CD_PERI_INIT, // Peripheral Initialization Error.
    ER_CD_PERI_CFG,  // Peripheral Configuration Error.
} EErCdPeri;

typedef enum
{
    ER_CD_SNSR_DISCONN, // Sensor Disconnected.
    ER_CD_SNSR_CFG,     // Sensor Configuration Error.
} EErCdSnsr;

typedef enum
{
    ER_CD_ACT_STALL, // Actuator Stalled.
} EErCdAct;

typedef enum
{
    ER_CD_MEM_ECC,      // Memory ECC Error.
    ER_CD_MEM_WRT_FAIL, // Memory Write Failure.
    ER_CD_MEM_RD_FAIL,  // Memory Read Failure.
} EErCdMem;

typedef enum
{
    ER_CD_PROC_BRG_UP, // Bring up Error.
    ER_CD_PROC_BRG_DN, // Bring down Error.
} EErCdProc;

typedef enum
{
    ER_CD_SW_UNKN,      // Unknown.
    ER_CD_SW_NUL_PTR,   // Null Pointer.
    ER_CD_SW_INV_PARAM, // Invalid Parameter.
} EErCdSw;

typedef enum
{
    ER_CD_VRFY_AUTH_FAIL, // Authentication Failure.
    ER_CD_VRFY_ENC_FAIL,  // Encryption Failure.
    ER_CD_VRFY_CRC_FAIL,  // CRC Check Failure.
} EErCdVrfy;

typedef enum
{
    ER_CD_OS_TSK_LD_HIGH, // Task Load Too High.
    ER_CD_OS_MEM_LD_HIGH, // Memory Load Too High.
    ER_CD_OS_STK_HP_LD_HIGH, // Stack/Heap Load Too High.
} EErCdOs;

typedef enum
{
    ER_CD_ENV_TEMP_HIGH, // Temperature Too Hight.
    ER_CD_ENV_TEMP_LOW,  // Temperature Too Low.
} EErCdEnv;

typedef enum
{
    ER_CLS_SW,   // Software Class.
    ER_CLS_COMM, // Communication Class.
    ER_CLS_PERI, // Peripheral Class.
    ER_CLS_SNSR, // Sensor Class.
    ER_CLS_ACT,  // Actuator Class.
    ER_CLS_MEM,  // Memory Class.
    ER_CLS_PROC, // Processor Class.
    ER_CLS_VRFY, // Verify Class.
    ER_CLS_OS,   // Operating System Class.
    ER_CLS_ENV,  // Environment Clss.
} EErCls;

typedef enum
{
    ER_MOD_GPIO, // Gpio module.
    ER_MOD_CLK,  // Clk module.
    ER_MOD_COM,  // Common module.
} EErMod;

typedef enum
{
    ER_SUB_DOM_ORDMCU,
    ER_SUB_DOM_ORDRTOS,
    ER_SUB_DOM_ORDBOT,
} EErSubDom;

typedef enum
{
    ER_DOM_ORD_BOT,
    ER_DOM_BAL_CAR,
} EErDom;

#ifdef __cplusplus
}
#endif

#endif // __ERR_H__
