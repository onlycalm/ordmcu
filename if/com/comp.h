#ifndef __COMP_H__
#define __COMP_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* 编译器检测 */
#define COMP_UNKN         0
#define COMP_GCC_OR_CLANG 1
#define COMP_ARM          2
#define COMP_MSVC         3

#if defined(__GNUC__) || defined(__clang__)
#define COMP COMP_GCC_OR_CLANG
#elif defined(__ICCARM__) || defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define COMP COMP_ARM
#elif defined(_MSC_VER)
#define COMP COMP_MSVC
#else
#define COMP COMP_UNKN
#warning Unknown compilation environment.
#endif

// Define inline.
#if COMP == COMP_GCC_OR_CLANG
#define FORCE_INLINE static inline __attribute__((always_inline))
#define INLINE       static inline
#elif COMP == COMP_ARM
#define FORCE_INLINE static __forceinline
#define INLINE       static inline
#elif COMP == COMP_MSVC
#define FORCE_INLINE static __forceinline
#define INLINE       static inline
#elif COMP == COMP_UNKN
#define FORCE_INLINE static inline
#define INLINE       static inline
#endif // COMP

// Define weak.
#if COMP == COMP_GCC_OR_CLANG
#define WEAK __attribute__((weak))
#elif COMP == COMP_ARM
#define WEAK __weak
#elif COMP == COMP_MSVC
#define WEAK
#elif COMP == COMP_UNKN
#define WEAK
#endif // COMP

#ifdef __cplusplus
}
#endif

#endif // __COMP_H__
