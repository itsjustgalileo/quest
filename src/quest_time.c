#include <quest/quest_logger.h>
#include <quest/quest_time.h>

#ifdef _WIN32
#include <windows.h>

LARGE_INTEGER frequency;
LARGE_INTEGER counter;

#elif defined(QUEST_PLATFORM_UNIX) || defined(QUEST_PLATFORM_LINUX)
#include <time.h>
#include <unistd.h>
#endif /* _WIN32 */

uint32 quest_ticks_init(void) {
#ifdef QUEST_PLATOFORM_WINDOWS
    if (!QueryPerformanceFrequency(&frequency)) {
        return 1;
    }

    if (!QueryPerformanceCounter(&counter)) {
        return 2;
    }
#else

#endif /* _WIN32 */
    return 0;
}

void quest_ticks_shutdown(void) {
    return;
}

uint64 quest_get_ticks(void) {
#ifdef QUEST_PLATFORM_WINDOWS
    if (!QueryPerformanceCounter(&counter)) {
        /* technically, we need to throw an exception but... */
        return 0;
    }
    uint64 ticks = quest_static_cast(uint64, counter.QuadPart) * 1000 / quest_static_cast(uint64, frequency.QuadPart);
    return ticks;
#else
    return clock();
#endif /* _WIN32 */
}

void quest_sleep(uint64 time) {
#ifdef QUEST_PLATFORM_WINDOWS
    Sleep(time);
#else
    (void)time;
    QUEST_TODO("quest_sleep: Not Implemented");
#endif /* _WIN32 */
}
