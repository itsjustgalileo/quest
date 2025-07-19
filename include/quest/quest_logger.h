#ifndef QUEST_LOGGER_H_
#define QUEST_LOGGER_H_

#include <quest/quest_common.h>

#include <quest/quest_header.h>

#define QUEST_LOG_TRACE(...) quest_log_trace(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define QUEST_LOG_DEBUG(...) quest_log_debug(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define QUEST_LOG_INFO(...) quest_log_info(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define QUEST_LOG_WARN(...) quest_log_warn(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define QUEST_LOG_ERROR(...) quest_log_error(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define QUEST_LOG_FATAL(...) quest_log_fatal(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define QUEST_TODO(...) quest_log_todo(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
    typedef enum {
        QUEST_LOG_LEVEL_TRACE = 0x00,
        QUEST_LOG_LEVEL_DEBUG,
        QUEST_LOG_LEVEL_INFO,
        QUEST_LOG_LEVEL_WARN,
        QUEST_LOG_LEVEL_ERROR,
        QUEST_LOG_LEVEL_FATAL,
        QUEST_LOG_LEVEL_TODO,
        QUEST_LOG_LEVEL_RESET = 0x7fff,
    } quest_log_level_t;

    extern QUEST_API bool QUEST_DECL quest_logger_init(void);

    extern QUEST_API bool QUEST_DECL quest_set_color(quest_log_level_t level);

    extern QUEST_API int QUEST_DECL quest_log_trace(const char *file, const char *func, int line, const char *fmt, ...);
    extern QUEST_API int QUEST_DECL quest_log_debug(const char *file, const char *func, int line, const char *fmt, ...);
    extern QUEST_API int QUEST_DECL quest_log_info(const char *file, const char *func, int line, const char *fmt, ...);
    extern QUEST_API int QUEST_DECL quest_log_warn(const char *file, const char *func, int line, const char *fmt, ...);
    extern QUEST_API int QUEST_DECL quest_log_error(const char *file, const char *func, int line, const char *fmt, ...);
    extern QUEST_API int QUEST_DECL quest_log_fatal(const char *file, const char *func, int line, const char *fmt, ...);

    extern QUEST_API int QUEST_DECL quest_log_todo(const char *file, const char *func, int line, const char *fmt, ...);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#include <quest/quest_footer.h>

#endif /* QUEST_LOGGER_H_ */
