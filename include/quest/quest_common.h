#ifndef QUEST_COMMON_H_
#define QUEST_COMMON_H_

#include <quest/quest_platforms.h>

#include <assert.h> /* Might implement mine later. */
#include <stdint.h>
#include <stdlib.h>
#include <float.h>

#ifndef __cplusplus
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L || \
    defined(_MSC_VER) && _MSC_VER >= 1910 ||                    \
    defined(QUEST_INCLUDE_STDBOOL_H)
#include <stdbool.h>
#elif !defined(__bool_true_and_false_are_defined)
#define bool unsigned char
#define true  1
#define false 0
#endif /* bool definition */
#endif /* __cplusplus */

#define QUEST_ARRAY_LENGTH(arr) (sizeof(arr) / sizeof((arr)[0]))
#define QUEST_STRINGIFY(arg) #arg

/* This is stolen from tsoding :) Thank you Alexey */
#define QUEST_UNHEX(a, b, c, d)                                         \
    ((quest_static_cast(uint32, quest_static_cast(uint8, (a))) << 0) |  \
     (quest_static_cast(uint32, quest_static_cast(uint8, (b))) << 8) |  \
     (quest_static_cast(uint32, quest_static_cast(uint8, (c))) << 16) | \
     (quest_static_cast(uint32, quest_static_cast(uint8, (d))) << 24))

#ifndef quest_static_assert
#ifdef __cplusplus
#define quest_static_assert(name, x) static_assert(x, #x)
#elif defined(__GNUC__) && __STDC_VERSION__ >= 201112L
#define quest_static_assert(name, x) _Static_assert(x, #x)
#else
#define quest_static_assert(name, x)            \
    typedef char quest_static_assert_ ## name[(x) ? 1 : -1]; \
    extern quest_static_assert_ ## name *quest_static_assert_ ## name ## _use
#endif /* __cplusplus */
#endif
quest_static_assert(two_s_complements, (int)~(int)0 == (int)-1);

#ifdef __cplusplus
#define quest_static_cast(type, val) static_cast<type>(val)
#define quest_reinterpret_cast(type, val) reinterpret_cast<type>(val)
#define quest_const_cast(type, val) const_cast<type>(val)
#else
#define quest_static_cast(type, val) ((type)(val))
#define quest_reinterpret_cast(type, val) ((type)(val))
#define quest_const_cast(type, val) ((type)(val))
#endif /* __cplusplus */

#if defined(_MSC_VER) && (_MSC_VER < 1310)
#define QUEST_NOLONGLONG 1
#endif /* defined(_MSC_VER) && (_MSC_VER < 1310) */

typedef int8_t int8;
#define QUEST_INT8_MIN ~((int8)(0x7f))
#define QUEST_INT8_MAX ((int8)(0x7f))
quest_static_assert(size_of_int8, sizeof(int8) == 1);

typedef uint8_t uint8;
#define QUEST_UINT8_MIN ((uint8)(0x00))
#define QUEST_UINT8_MAX ((uint8)(0xff))
quest_static_assert(size_of_uint8, sizeof(uint8) == 1);

typedef int16_t int16;
#define QUEST_INT16_MIN ~((int16)(0x7fff))
#define QUEST_INT16_MAX ((int16)(0x7fff))
quest_static_assert(size_of_int16, sizeof(int16) == 2);

typedef uint16_t uint16;
#define QUEST_UINT16_MIN ((uint16)(0x0000))
#define QUEST_UINT16_MAX ((uint16)(0xffff))
quest_static_assert(size_of_uint16, sizeof(uint16) == 2);

typedef int32_t int32;
#define QUEST_INT32_MIN ~((int32)(0x7fffffff))
#define QUEST_INT32_MAX ((int32)(0x7fffffff))
quest_static_assert(size_of_int32, sizeof(int32) == 4);

typedef uint32_t uint32;
#define QUEST_UINT32_MIN ((uint32)(0x00000000))
#define QUEST_UINT32_MAX ((uint32)(0xffffffff))
quest_static_assert(size_of_uint32, sizeof(uint32) == 4);

#ifndef QUEST_NOLONGLONG
typedef int64_t int64;
#define QUEST_INT64_MIN ~((int64)(0x7fffffffffffffffLL))
#define QUEST_INT64_MAX ((int64)(0x7fffffffffffffffLL))
quest_static_assert(size_of_int64, sizeof(int64) == 8);

typedef uint64_t uint64;
#define QUEST_UINT64_MIN ((uint64)(0x0000000000000000ULL))
#define QUEST_UINT64_MAX ((uint64)(0xffffffffffffffffULL))
quest_static_assert(size_of_uint64, sizeof(uint64) == 8);

typedef int64 quest_time;
#define QUEST_TIME_MIN QUEST_INT64_MIN
#define QUEST_TIME_MAX QUEST_INT64_MAX
quest_static_assert(size_of_quest_time, sizeof(quest_time) == 8);
#endif /* QUEST_NOLONGLONG */

#ifdef FLT_EPSILON
#define QUEST_FLT_EPSILON FLT_EPSILON
#else
#define QUEST_FLT_EPSILON 0.1920928955078125e-07f
#endif /* FLT_EPSILON */

#ifndef QUEST_SIZE_MAX
#ifdef SIZE_MAX
#define QUEST_SIZE_MAX SIZE_MAX
#else
#define QUEST_SIZE_MAX ((size_t)-1)
#endif /* SIZE_MAX */
#endif /* QUEST_SIZE_MAX */

typedef struct {
    int8 c;
    void *v;
} quest_test_struct;
quest_static_assert(size_of_quest_test_struct, sizeof(quest_test_struct) == (2 * sizeof(void *)));

typedef enum {
    QUEST_TEST_ENUM,
} quest_test_enum;
quest_static_assert(size_of_quest_test_enum, sizeof(quest_test_enum) == sizeof(int32));

#include <quest/quest_header.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    /* TODO quest stdlib functions */
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#include <quest/quest_footer.h>

#endif /* QUEST_COMMON_H_ */
