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
extern "C" {
#endif

#define GetArrSz(Arr) (sizeof(Arr) / sizeof((Arr)[0]))
#define GetByNum(Var) (sizeof(Var))

#ifdef __cplusplus
}
#endif

#endif // __COM_H__
