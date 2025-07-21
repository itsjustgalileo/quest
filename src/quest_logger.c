#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
#include <windows.h>

static HANDLE hConsole;
#else
#include <unistd.h>
#endif /* _WIN32 */

#include <quest/quest_logger.h>

bool quest_logger_init(void) {
#ifdef _WIN32
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hConsole, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, dwMode);
#endif
    return true;
}

bool quest_set_color(quest_log_level_t level) {
    switch (level) {
    case QUEST_LOG_LEVEL_TRACE:
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
        fprintf(stdout, "\x1b[2;37m");
#endif /* _WIN32 */
        break;
    case QUEST_LOG_LEVEL_DEBUG:
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
#else
        fprintf(stdout, "\x1b[;34m");
#endif /* _WIN32 */
        break;
    case QUEST_LOG_LEVEL_INFO:
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
#else
        fprintf(stdout, "\x1b[;32m");
#endif /* _WIN32 */
        break;
    case QUEST_LOG_LEVEL_WARN:
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
#else
        fprintf(stderr, "\x1b[;33m");
#endif /* _WIN32 */
        break;
    case QUEST_LOG_LEVEL_ERROR:
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
#else
        fprintf(stderr, "\x1b[;31m");
#endif /* _WIN32 */
        break;
    case QUEST_LOG_LEVEL_FATAL:
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);        
#else
        fprintf(stderr, "\x1b[;41m");
#endif /* _WIN32 */
        break;
    case QUEST_LOG_LEVEL_TODO:
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
#else
        fprintf(stderr, "\x1b[1;91m");
#endif /* _WIN32 */
        break;
    case QUEST_LOG_LEVEL_RESET:
#ifdef QUEST_PLATFORM_WINDOWS
        /* This is yet to be done correctly */
        SetConsoleTextAttribute(hConsole, 0);
#else
        fprintf(stderr, "\x1b[;0m");
#endif /* QUEST_PLATFORM_WINDOWS */
        break;
    }
    return true;
}

int quest_log_trace(const char *file, const char *func, int line, const char *fmt, ...) {
    int length = 0;
    va_list ap;
    va_start(ap, fmt);
    quest_set_color(QUEST_LOG_LEVEL_TRACE);
    length += fprintf(stdout, "[QUEST TRACE - in file: %s | function: %s | line: %i]: ", file, func, line);
    length += vfprintf(stdout, fmt, ap);
    length += fprintf(stdout, "\n");
    quest_set_color(QUEST_LOG_LEVEL_RESET);
    va_end(ap);
    fflush(stdout);
    return length;    
}

int quest_log_debug(const char *file, const char *func, int line, const char *fmt, ...) {
    int length = 0;
    va_list ap;
    va_start(ap, fmt);
    quest_set_color(QUEST_LOG_LEVEL_DEBUG);
    length += fprintf(stdout, "[QUEST DEBUG - in file: %s | function: %s | line: %i]: ", file, func, line);
    length += vfprintf(stdout, fmt, ap);
    length += fprintf(stdout, "\n");
    quest_set_color(QUEST_LOG_LEVEL_RESET);
    va_end(ap);
    fflush(stdout);
    return length;        
}

int quest_log_info(const char *file, const char *func, int line, const char *fmt, ...) {
    int length = 0;
    va_list ap;
    va_start(ap, fmt);
    quest_set_color(QUEST_LOG_LEVEL_INFO);
    length += fprintf(stdout, "[QUEST INFO - in file: %s | function: %s | line: %i]: ", file, func, line);
    length += vfprintf(stdout, fmt, ap);
    length += fprintf(stdout, "\n");
    quest_set_color(QUEST_LOG_LEVEL_RESET);
    va_end(ap);
    fflush(stdout);
    return length;        
}

int quest_log_warn(const char *file, const char *func, int line, const char *fmt, ...) {
    int length = 0;
    va_list ap;
    va_start(ap, fmt);
    quest_set_color(QUEST_LOG_LEVEL_WARN);
    length += fprintf(stderr, "[QUEST WARNING - in file: %s | function: %s | line: %i]: ", file, func, line);
    length += vfprintf(stderr, fmt, ap);
    length += fprintf(stderr, "\n");
    quest_set_color(QUEST_LOG_LEVEL_RESET);
    va_end(ap);
    fflush(stderr);
    return length;        
}

int quest_log_error(const char *file, const char *func, int line, const char *fmt, ...) {
    int length = 0;
    va_list ap;
    va_start(ap, fmt);
    quest_set_color(QUEST_LOG_LEVEL_ERROR);
    length += fprintf(stderr, "[QUEST ERROR - in file: %s | function: %s | line: %i]: ", file, func, line);
    length += vfprintf(stderr, fmt, ap);
    length += fprintf(stderr, "\n");
    quest_set_color(QUEST_LOG_LEVEL_RESET);
    va_end(ap);
    fflush(stderr);
    return length;        
}

int quest_log_fatal(const char *file, const char *func, int line, const char *fmt, ...) {
    int length = 0;
    va_list ap;
    va_start(ap, fmt);
    quest_set_color(QUEST_LOG_LEVEL_FATAL);
    length += fprintf(stderr, "[QUEST FATAL - in file: %s | function: %s | line: %i]: ", file, func, line);
    length += vfprintf(stderr, fmt, ap);
    length += fprintf(stderr, "\n");
#ifdef QUEST_DEBUG
    quest_set_color(QUEST_LOG_LEVEL_RESET);
    va_end(ap);
    fflush(stderr);
    abort();
#else    
    quest_set_color(QUEST_LOG_LEVEL_RESET);
    va_end(ap);
    exit(1);
#endif /* QUEST_DEBUG */

    return length;    
}

int quest_log_todo(const char *file, const char *func, int line, const char *fmt, ...) {
    int length = 0;
    va_list ap;
    va_start(ap, fmt);
    quest_set_color(QUEST_LOG_LEVEL_FATAL);
    length += fprintf(stderr, "[QUEST TODO - in file: %s | function: %s | line: %i]: ", file, func, line);
    length += vfprintf(stderr, fmt, ap);
    length += fprintf(stderr, "\n");
    /* Can't allow user to release applications
       with an incomplete library. Totally tolerable
       in debug mode though as we need to know what
       is left to do. */
#ifdef QUEST_DEBUG
    quest_set_color(QUEST_LOG_LEVEL_RESET);
    va_end(ap);
    fflush(stderr);
    return length;    
#endif /* QUEST_DEBUG */
    quest_set_color(QUEST_LOG_LEVEL_RESET);
    va_end(ap);
    exit(1);
}
