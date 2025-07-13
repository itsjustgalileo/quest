#ifdef QUEST_HEADER_H_
#error "Header file cannot be included twice"
#endif /* QUEST_HEADER_H_ */
#define QUEST_HEADER_H_

#ifndef QUEST_DECL
#if defined(_WIN32) && !defined(__GNUC__)
#define QUEST_DECL __cdecl
#else
#define QUEST_DECL
#endif /* QUEST_DECL */
#endif /* QUEST_DECL */

#ifndef QUEST_API
#ifdef QUEST_DLL
#if defined(_WIN32) && !defined(__GNUC__)
#define QUEST_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#define QUEST_API __attribute__((visibility("default")))
#else
#define QUEST_API
#endif /* export macro */
#else
#if defined(_WIN32) && !defined(__GNUC__)
#define QUEST_API __declspec(dllimport)
#else
#define QUEST_API
#endif /* import macro */
#endif /* QUEST_DLL */
#endif /* QUEST_API */

#ifndef QUEST_PACK_SIZE
#if defined(__x86_64__) || defined(__x86_64) || defined(__aarch64__)
#define QUEST_PACK_SIZE 8
#else
#define QUEST_PACK_SIZE 4
#endif /*  defined(_WIN32) && defined(_WIN64) */
#endif

#ifdef _MSC_VER
#pragma pack(push, QUEST_PACK_SIZE)
#endif /* _MSC_VER */

#ifndef QUEST_ALIGN
#if defined(_MSC_VER)
#define QUEST_ALIGN(alignment) __declspec(align(alignment))
#elif defined(__GNUC__) || defined(__clang__)
#define QUEST_ALIGN(alignment) __attribute__((aligned(alignment)))
#else
#error "QUEST_ALIGN: Unsupported compiler"
#endif /* align */
#endif /* QUEST_ALIGN */

#ifndef QUEST_ALIGNOF
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define QUEST_ALIGNOF(type) _Alignof(type)
#elif defined(_MSC_VER)
#define QUEST_ALIGNOF(type) __alignof(type)
#elif defined(__GNUC__) || defined(__clang__)
#define QUEST_ALIGNOF(type) __alignof__(type)
#else
#error "QUEST_ALIGNOF: Unsupported compiler"
#endif
#endif /* QUEST_ALIGNOF */

#define QUEST_MAX_ALIGN long double

#ifndef QUEST_INLINE
#if defined(_MSC_VER)
#define QUEST_INLINE __inline
#elif defined(__GNUC__) || defined(__clang__)
#define QUEST_INLINE inline
#else
#define QUEST_INLINE
#endif
#endif /* QUEST_INLINE */

#ifndef QUEST_FORCE_INLINE
#if defined(_MSC_VER)
#define QUEST_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define QUEST_FORCE_INLINE inline __attribute__((always_inline))
#else
#define QUEST_FORCE_INLINE QUEST_INLINE
#endif
#endif /* QUEST_FORCEINLINE */

#ifndef QUEST_DEBUG
#if (defined(NDEBUG) || defined(_NDEBUG)) && !defined(_DEBUG)
#define QUEST_DEBUG 0 /* Release mode */
#else
#define QUEST_DEBUG 1 /* Debug mode */
#endif
#endif

#ifndef QUEST_BREAKPOINT
#if defined(_WIN32) && !defined(__GNUC__)
#define QUEST_BREAKPOINT __debugbreak()
#elif defined(__linux__) || defined(__GNUC__) || defined(__clang__)
#define QUEST_BREAKPOINT __builtin_trap() /* is this really better than raise(SIGTRAP)??! */
#else
#error "QUEST_BREAKPOINT: Undefined platform"
#endif /* defined(_WIN32) && !defined(__GNUC__) */
#endif /* QUEST_BREAKPOINT */

#ifndef __MACH__
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif /* __cplusplus */
#endif /* NULL */
#endif /* __MACH__ */

#ifndef QUEST_NORETURN
#if defined(_MSC_VER)
#define QUEST_NORETURN __declspec(noreturn)
#elif defined(__GNUC__) || defined(__clang__)
#define QUEST_NORETURN __attribute__((noreturn))
#else
#define QUEST_NORETURN
#endif
#endif /* QUEST_NORETURN */
