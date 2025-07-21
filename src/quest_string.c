#include <ctype.h>

#include <quest/quest_logger.h>

#include <quest/quest_string.h>

void *quest_memchr(const void *str, int c, size_t n) {
    assert(str);
    const int8 *c_str = quest_reinterpret_cast(const int8 *, str);
    size_t i;
    for (i = 0; i < n; ++i) {
        if (c_str[i] == quest_static_cast(int8, c)) {
            return quest_reinterpret_cast(void *, (c_str + i));
        }
    }
    return NULL;
}

int quest_memcmp(const void *dst, const void *src, size_t n) {
    assert(dst && src);
    const uint8 *c_dst;
    c_dst = quest_reinterpret_cast(const uint8 *, dst);
    const uint8 *c_src;
    c_src = quest_reinterpret_cast(const uint8 *, src);
    size_t i;
    for (i = 0; i < n; i++) {
        if (c_dst[i] != c_src[i]) {
            break;
        }
    }
    if (i == n) {
        return 0;
    }
    return quest_static_cast(int, c_dst[i]) - quest_static_cast(int, c_src[i]);
}

void *quest_memcpy(void *dst, const void *src, size_t n) {
    assert(dst && src);
    size_t s;
    int8 *c_dst = quest_reinterpret_cast(int8 *, dst);
    const int8 *c_src = quest_reinterpret_cast(const int8 *, src);
    for (s = 0; s < n; ++s) {
        c_dst[s] = c_src[s];
    }
    return dst;
}

void *quest_memmove(void *dst, const void *src, size_t n) {
    assert(dst && src);
    intptr_t s;
    int8 *c_dst = quest_reinterpret_cast(int8 *, dst);
    int8 *c_src = quest_reinterpret_cast(int8 *, src);
    if (n == 0) {
        return dst;
    }
    if (c_dst < c_src || c_dst >= c_src + n) {
        for (s = 0; s < (intptr_t)n; ++s)
            c_dst[s] = c_src[s];
    } else {
        for (s = (intptr_t)n - 1; s >= 0; --s)
            c_dst[s] = c_src[s];
    }
    return dst;    
}

void *quest_memset(void *m, int c, size_t n) {
    assert(m);
    uint8 *c_m = quest_reinterpret_cast(uint8 *, m);
    for (size_t s = 0; s < n; s++) {
        c_m[s] = quest_static_cast(uint8, c);
    }
    return m;
}

char *quest_strcpy(char *restrict dst, const char *restrict src) {
    assert(dst && src);
    char *ret = dst;
    while ((*dst++ = *src++));
    return ret;
}

char *quest_strncpy(char *restrict dst, const char *restrict src, size_t capacity) {
    assert(dst && src);
    size_t i = 0;
    for (; i < capacity && src[i]; ++i) {        
        dst[i] = src[i];
    }
    for (; i < capacity; ++i) {        
        dst[i] = '\0';
    }
    return dst;
}

char *quest_strcat(char *restrict dst, const char *restrict src) {
    assert(dst && src);
    char *p = dst;
    while (*p) p++;
    while ((*p++ = *src++));
    return dst;
}

int quest_strcmp(const char *restrict str1, const char *restrict str2) {
    assert(str1 && str2);
    while (*str1 && (*str1 == *str2)) {
        ++str1;
        ++str2;
    }
    return quest_static_cast(int, (uint8)(*str1)) - quest_static_cast(int, (uint8)(*str2));
}

int quest_strncmp(const char *restrict str1, const char *restrict str2, size_t n) {
    assert(str1 && str2);
    size_t i;
    for (i = 0; i < n; ++i) {
        if (str1[i] == '\0' || str1[i] != str2[i]) {
            return quest_static_cast(int, (uint8)str1[i]) - quest_static_cast(int, (uint8)str2[i]);            
        }
    }
    return 0;
}

int quest_strcoll(const char *restrict str1, const char *restrict str2) {
    assert(str1 && str2);
    QUEST_TODO("Not implemented!");
    return 0;
}

size_t quest_strspn(const char *restrict str, const char *restrict accept) {
    assert(str && accept);
    QUEST_TODO("Not implemented!");
    return 0;
}

size_t quest_strcspn(const char *restrict str, const char *restrict reject) {
    assert(str && reject);
    QUEST_TODO("Not implemented!");
    return 0;
}

char *quest_strerror(int errnum) {
    QUEST_TODO("Not implemented!");
    (void)errnum;
    return NULL;
}

size_t quest_strlen(const char *restrict str) {
    assert(str);
    size_t len = 0;
    for (; str[len] != '\0'; len++);
    return len;
}

char *quest_strpbrk(const char *restrict str1, const char *restrict str2) {
    assert(str1 && str2);
    QUEST_TODO("Not implemented!");
    return NULL;
}

char *quest_strchr(const char *str, int c) {
    assert(str);
    do {
        if (*str == (char)c)
            return (char *)str;
    } while (*str++);
    return NULL;
}

char *quest_strrchr(const char *str, int c) {
    assert(str);
    const char *last = NULL;
    do {
        if (*str == (char)c)
            last = str;
    } while (*str++);
    return (char *)last;
}

char *quest_strstr(const char *haystack, const char *needle) {
    assert(haystack && needle);
    size_t haystack_len = quest_strlen(haystack);
    size_t needle_len = quest_strlen(needle);
    if (needle_len == 0) {
        return quest_reinterpret_cast(char *, (haystack));
    }

    if (needle_len > haystack_len) {
        return NULL;
    }
    for (size_t i = 0; i <= haystack_len - needle_len; i++) {        
        size_t j = 0;
        while (j < needle_len && haystack[i + j] == needle[j]) {
            j++;
        }
        if (j == needle_len) {
            return quest_reinterpret_cast(char *, (haystack + i));
        }
    }
    return NULL;
}

char *quest_strtok(char *restrict str, const char *restrict delim) {
    assert(str && delim);
    QUEST_TODO("Not implemented!");
    return NULL;
}

size_t quest_strxfrm(char *restrict dst, const char *restrict src, size_t n) {
    assert(dst && src);
    (void)n;
    QUEST_TODO("Not implemented!");
    return 0;
}

/***************
 * STRING VIEW *
 ***************/

bool quest_string_view_from_cstr(quest_string_view_t *sv, const char *str) {
    assert(sv && str);
    sv->str = str;
    sv->len = quest_strlen(str);
    return true;
}

bool quest_string_view_from_range(quest_string_view_t *sv, const char *str, size_t len) {
    assert(sv && str);
    sv->str = str;
    sv->len = (size_t)len;
    return true;
}

bool quest_string_view_from_span(quest_string_view_t *sv, const char *start, const char *end) {
    assert(sv && start && end);
    if (start > end) {
        return false;
    }
    sv->str = start;
    sv->len = (size_t)(end - start);
    return true;
}

bool quest_string_view_equals(const quest_string_view_t *a, const quest_string_view_t *b) {
    assert(a && b);
    if (a->len != b->len) {
        return false;
    }
    return quest_strncmp(a->str, b->str, a->len) == 0;
}

bool quest_string_view_slice(const quest_string_view_t *sv, size_t start, size_t end, quest_string_view_t *out) {
    assert(sv && out);
    if (start > end || end > sv->len) return false;
    out->str = sv->str + start;
    out->len = end - start;
    return true;
}

bool quest_string_view_starts_with(const quest_string_view_t *sv, const char *prefix) {
    assert(sv && prefix);
    size_t prefix_len = quest_strlen(prefix);
    if (sv->len < prefix_len) {        
        return false;
    }
    return quest_memcmp(sv->str, prefix, prefix_len) == 0;
    
}

bool quest_string_view_ends_with(const quest_string_view_t *sv, const char *suffix) {
    assert(sv && suffix);
    size_t suffix_len = quest_strlen(suffix);
    if (suffix_len > sv->len) {        
        return false;
    }
    return quest_strncmp(sv->str + (sv->len - suffix_len), suffix, suffix_len) == 0;
}

bool quest_string_view_find(const quest_string_view_t *sv, char c, size_t *index) {
    assert(sv && index);
    for (*index = 0; *index < sv->len; ++(*index)) {
        if (sv->str[*index] == c) {
            return true;
        }
    }
    return false;
}

bool quest_string_view_trim_left(quest_string_view_t *sv) {
    assert(sv);
    size_t i = 0;
    while (i < sv->len && isspace((unsigned char)sv->str[i])) {
        i++;
    }
    sv->str += i;
    sv->len -= i;
    return true;
}

bool quest_string_view_trim_right(quest_string_view_t *sv) {
    assert(sv);
    while (sv->len > 0 && isspace((unsigned char)sv->str[sv->len - 1])) {
        sv->len--;
    }
    return true;
}

bool quest_string_view_trim(quest_string_view_t *sv) {
    return quest_string_view_trim_left(sv) && quest_string_view_trim_right(sv);
}


/******************
 * STRING BUILDER *
 ******************/

bool quest_string_builder_init(quest_string_builder_t *sb, size_t initial_capacity) {
    assert(sb);
    sb->length = 0;
    sb->capacity = initial_capacity;
    sb->data = malloc(sb->capacity);
    if (!sb->data) {
        QUEST_LOG_ERROR("Failed to allocate memory for string builder");
        return false;
    }
    sb->data[sb->length] = '\0';
    return true;
}

void quest_string_builder_cleanup(quest_string_builder_t *sb) {
    assert(sb);
    free(sb->data);
    sb->data = NULL;
    sb->length = 0;
    sb->capacity = 0;
}

void quest_string_builder_clear(quest_string_builder_t *sb) {
    assert(sb);
    sb->length = 0;
    return;
}

/* Helper: grow buffer if needed */
static bool quest_string_builder_ensure_capacity(quest_string_builder_t *sb, size_t needed) {
    assert(sb);
    if (needed <= sb->capacity) return true;

    size_t new_capacity = sb->capacity ? sb->capacity * 2 : 16;
    while (new_capacity < needed) {
        new_capacity *= 2;
    }

    char *new_data = realloc(sb->data, new_capacity);
    if (!new_data) {
        QUEST_LOG_ERROR("Failed to grow string builder buffer");
        return false;
    }

    sb->data = new_data;
    sb->capacity = new_capacity;
    return true;
}

bool quest_string_builder_append_char(quest_string_builder_t *sb, char c) {
    assert(sb);
    if (!quest_string_builder_ensure_capacity(sb, sb->length + 2)) {
        return false;
    }

    sb->data[sb->length] = c;
    sb->length++;
    sb->data[sb->length] = '\0';
    return true;
}

bool quest_string_builder_append_cstr(quest_string_builder_t *sb, const char *str) {
    assert(sb && str);
    size_t str_len = quest_strlen(str);
    if (!quest_string_builder_ensure_capacity(sb, sb->length + str_len + 1)) {
        return false;
    }
    quest_memcpy(sb->data + sb->length, str, str_len);
    sb->length += str_len;
    sb->data[sb->length] = '\0';
    return true;
}

bool quest_string_builder_append_view(quest_string_builder_t *sb, const quest_string_view_t *sv) {
    assert(sb && sv);
    if (!quest_string_builder_ensure_capacity(sb, sb->length + sv->len + 1)) {
        return false;
    }
    quest_memcpy(sb->data + sb->length, sv->str, sv->len);
    sb->length += sv->len;
    sb->data[sb->length] = '\0';
    return true;
}

const char *quest_string_builder_cstr(const quest_string_builder_t *sb) {
    assert(sb && sb->data);
    return (const char *)sb->data;
}

size_t quest_string_builder_length(const quest_string_builder_t *sb) {
    assert(sb);
    return sb->length;
}
