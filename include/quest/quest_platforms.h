#ifndef QUEST_PLATFORMS_H_
#define QUEST_PLATFORMS_H_

#if defined(__unix__) || defined(__unix) || defined(unix)
#define QUEST_PLATFORM_UNIX 1
#endif /* Unix */

#if defined(__linux__) || defined(__linux) || defined(linux)
#define QUEST_PLATFORM_LINUX 1
#endif /* Linux */

#if defined(__MINGW32__) || defined(__MINGW64__)
#define QUEST_PLATFORM_MINGW32 1
#endif /* MinGW */

#if defined(_WIN32) || defined(QUEST_PLATFORM_MINGW32)
#define QUEST_PLATFORM_WINDOWS 1
#if 0 /* Placeholder for WinRT */
#else
#define QUEST_PLATFORM_WIN32 1
#endif /* WinRT/GDK */
#endif /* Windows */

#ifdef __EMSCRIPTEN__
#define QUEST_PLATFORM_EMSCRIPTEN 1
#endif /* Emscripten */

#endif /* QUEST_PLATFORMS_H_ */
