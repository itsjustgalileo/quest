#include <stdio.h>

#include <quest/quest_logger.h>
#include <quest/quest_stack.h>
#include <quest/quest_string.h>

struct quest_stack {
    void *elems;
    size_t elem_size;
    size_t capacity; /* stack size */
    size_t size; /* technically, this is a stack pointer */
    /* bool dynamic; just a thought for later */
};

quest_stack_t *quest_stack_init(size_t size, size_t count) {
    quest_stack_t *s = (quest_stack_t *)malloc(sizeof(struct quest_stack));
    if (NULL == s) {
        QUEST_LOG_ERROR("Failed to allocate memory for stack");
        return NULL;
    }
    s->elem_size = size;
    s->capacity = count;
    s->elems = malloc(s->capacity * s->elem_size);
    if (NULL == s->elems) {
        QUEST_LOG_ERROR("Failed to allocate memory for stack elements");
        free(s);
        return NULL;
    }
    s->size = 0;
#ifndef NDEBUG
    quest_memset(s->elems, 0xAD, s->elem_size * s->capacity);
#endif /* NDEBUG */
    return s;
}

void quest_stack_cleanup(quest_stack_t *s) {
    assert(s);
    free(s->elems);
    free(s);
}

bool quest_stack_push(quest_stack_t *s, void *elem) {
    assert(s && elem);
    if (s->size >= s->capacity) {
        /*
        if (false == s->dynamic) {
            return false;
        }
        size_t new_cap = s->capacity ? s->capacity * 2 : 1;
        void *new_elems = realloc(s->elems, new_cap * s->elem_size);
        if (NULL == new_elems) return false;
        
        s->elems = new_elems;
        s->capacity = new_cap;
        */
        QUEST_LOG_FATAL("stack overflow");
    }

    void *dest = (char *)s->elems + s->size * s->elem_size;
    quest_memcpy(dest, elem, s->elem_size);
    ++s->size;
    return true;
}

bool quest_stack_pop(quest_stack_t *s, void *out_elem) {
    assert(s && s->size && out_elem);
    --s->size;
    void *src = (char *)s->elems + s->size * s->elem_size;
    quest_memcpy(out_elem, src, s->elem_size);
    return true;
}

size_t quest_stack_size(quest_stack_t *s) {
    assert(s);
    return s->size;
}

bool quest_stack_is_empty(quest_stack_t *s) {
    assert(s);
    return s->size == 0;
}

bool quest_stack_reset(quest_stack_t *s) {
    assert(s);
#ifndef NDEBUG
    quest_memset(s->elems, 0xDE, s->elem_size * s->capacity);
#endif /* NDEBUG */
    s->size = 0;
    return true;
}

void *quest_stack_top(quest_stack_t *s) {
    assert(s && s->size);
    return (char *)s->elems + (s->size - 1) * s->elem_size;
}
