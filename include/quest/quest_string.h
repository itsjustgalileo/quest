#ifndef QUEST_STRING_H_
#define QUEST_STRING_H_

#include <quest/quest_common.h>

#include <quest/quest_header.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    extern QUEST_API void *QUEST_DECL quest_memchr(const void *str, int c, size_t n);
    extern QUEST_API int QUEST_DECL quest_memcmp(const void *dst, const void *src, size_t n);
    extern QUEST_API void *QUEST_DECL quest_memcpy(void *dst, const void *src, size_t n);
    extern QUEST_API void *QUEST_DECL quest_memmove(void *dst, const void *src, size_t n);
    extern QUEST_API void *QUEST_DECL quest_memset(void *m, int c, size_t n);
    
    extern QUEST_API char *QUEST_DECL quest_strcat(char *restrict dst, const char *restrict src);
    extern QUEST_API char *QUEST_DECL quest_strncat(char *restrict dst, const char *restrict src, size_t n);
    extern QUEST_API int QUEST_DECL quest_strcmp(const char *restrict str1, const char *restrict str2);
    extern QUEST_API int QUEST_DECL quest_strncmp(const char *restrict str1, const char *restrict str2, size_t n);
    extern QUEST_API int QUEST_DECL quest_strcoll(const char *restrict str1, const char *restrict str2);
    extern QUEST_API char *QUEST_DECL quest_strcpy(char *restrict dst, const char *restrict src);
    extern QUEST_API char *QUEST_DECL quest_strncpy(char *restrict dst, const char *restrict src, size_t capacity);
    extern QUEST_API size_t QUEST_DECL quest_strspn(const char *restrict str, const char *restrict accept);
    extern QUEST_API size_t QUEST_DECL quest_strcspn(const char *restrict str, const char *restrict reject);
    extern QUEST_API char *QUEST_DECL quest_strerror(int errnum);
    extern QUEST_API size_t QUEST_DECL quest_strlen(const char *restrict str);
    extern QUEST_API char *QUEST_DECL quest_strpbrk(const char *restrict str1, const char *restrict str2);
    extern QUEST_API char *QUEST_DECL quest_strchr(const char *str, int c);
    extern QUEST_API char *QUEST_DECL quest_strrchr(const char *str, int c);
    extern QUEST_API size_t QUEST_DECL quest_strspn(const char *restrict str1, const char *restrict str2);
    extern QUEST_API char *QUEST_DECL quest_strstr(const char *haystack, const char *needle);
    extern QUEST_API char *QUEST_DECL quest_strtok(char *restrict str, const char *restrict delim);
    extern QUEST_API size_t QUEST_DECL quest_strxfrm(char *restrict dst, const char *restrict src, size_t n);

    typedef struct {
        const char *str;
        size_t len;
        bool null_fin;
    } string_view_t;

    extern QUEST_API bool QUEST_DECL string_view_from_cstr(string_view_t sv, const char *str);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#include <quest/quest_footer.h>

#endif /* QUEST_STRING_H_ */
