#ifndef QUEST_CONFIG_GENERIC_H_
#define QUEST_CONFIG_GENERIC_H_
#define QUEST_CONFIG_H_

#include <quest/quest_platforms.h>

#define HAVE_STDARG_H   1
#define HAVE_STDDEF_H   1

#if !defined(HAVE_STDINT_H) && !defined(_STDINT_H_)
/* Most everything except Visual Studio 2008 and earlier has stdint.h now */
#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef signed __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef signed __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef signed __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#ifndef _UINTPTR_T_DEFINED
#ifdef  _WIN64
typedef unsigned __int64 uintptr_t;
#else
typedef unsigned int uintptr_t;
#endif
#define _UINTPTR_T_DEFINED
#endif
#else
#define HAVE_STDINT_H 1
#endif /* Visual Studio 2008 */
#endif /* !_STDINT_H_ && !HAVE_STDINT_H */

#ifdef __GNUC__
#define HAVE_GCC_SYNC_LOCK_TEST_AND_SET 1
#endif

/* Enable the stub process support */
#define SDL_PROCESS_DUMMY 1

/* Enable the dummy shared object loader (src/loadso/dummy/\*.c) */
#define SDL_LOADSO_DUMMY 1

/* Enable the stub thread support (src/thread/generic/\*.c) */
#define SDL_THREADS_DISABLED    1

/* Enable the dummy filesystem driver (src/filesystem/dummy/\*.c) */
#define SDL_FILESYSTEM_DUMMY  1
#define SDL_FSOPS_DUMMY 1

#endif /* QUEST_CONFIG_GENERIC_H_ */