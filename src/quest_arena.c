#include <stdio.h>
#include <stddef.h>

#include <quest/quest_arena.h>
#include <quest/quest_string.h>

struct quest_arena {
    size_t capacity; /* Arena's total capacity */
    size_t used; /* Arena's used size */
    void *base; /* Arena's starting point */
    bool is_sub; /* Helps with free */
#ifndef NDEBUG
    const char *debug_name;
#endif /* NDEBUG */
};

quest_arena_t *quest_arena_init(size_t capacity, const char *name) {
    quest_arena_t *arena = (quest_arena_t *)malloc(sizeof(quest_arena_t));
    if (NULL == arena) {
        fprintf(stderr, "[arena_init]: Failed to allocate memory quest_arena_t\n");
        return NULL;
    }

    arena->is_sub = false;
    arena->capacity = capacity;
    arena->used = 0;
#ifndef NDEBUG
    arena->debug_name = name ? name : "unnamed_arena";
#endif
    
    arena->base = malloc(capacity);
    if (NULL == arena->base) {
        fprintf(stderr, "[arena_init]: Failed to allocate memory for base\n");
        free(arena);
        return NULL;
    }
    
    return arena;
}

/*
 * Frees an arena and its backing memory.
 * Do not call this on subarenas created via arena_create_subarena.
 * Use arena_rewind() or arena_reset() on the parent instead.
 */
void quest_arena_free(quest_arena_t *arena) {
    assert(arena);
    if (arena->is_sub) {
        fprintf(stderr, "[arena_free]: Did you mean to call arena_rewind or arena_reset instead?\nLet's not continue, just for safety\n");
        return;
    }
    free(arena->base);
    free(arena);
    return;
}

void *quest_arena_malloc(quest_arena_t *arena, size_t size) {
    assert(arena);
    
    if (0 == size) {
#ifndef NDEBUG
        fprintf(stderr, "[arena_malloc]: +1 size.\n");
        ++size;
#endif /* NDEBUG */
        return NULL;
    }
    
    if (arena->used + size > arena->capacity) {
        fprintf(stderr, "[arena_malloc]: Buffer overrun\n");
        return NULL;
    }

    void *ptr = (char *)arena->base + arena->used;
    arena->used += size;
#ifndef NDEBUG
    quest_memset(ptr, 0xAD, size);
#endif /* NDEBUG */
    
    return ptr;
}

void *quest_arena_aligned_malloc(quest_arena_t *arena, size_t size, size_t alignment) {
    assert(arena);

    if (0 == size) {
#ifndef NDEBUG
        fprintf(stderr, "[arena_aligned_malloc]: +1 size.\n");
        ++size;
#endif /* NDEBUG */
        return NULL;
    }

    assert((alignment & (alignment - 1)) == 0);

    uintptr_t current = (uintptr_t)arena->base + arena->used;
    uintptr_t aligned = (current + (alignment - 1)) & ~(alignment - 1);
    size_t padding = aligned - current;

    if (arena->used + size + padding > arena->capacity) {
        fprintf(stderr, "[arena_aligned_malloc]: Buffer overrun\n");
        return NULL;
    }
    
    void *ptr = (void *)aligned;
    arena->used += size + padding;
    return ptr;
}

void quest_arena_reset(quest_arena_t *arena) {
    assert(arena);
#ifndef NDEBUG
    quest_memset(arena->base, 0xDE, arena->used);
#endif /* NDEBUG */
    arena->used = 0;
    return;
}

int quest_arena_get_size(quest_arena_t *arena, size_t *size) {
    assert(arena && size);
    *size = arena->used;
    return 0;
}

int quest_arena_get_available(quest_arena_t *arena, size_t *size) {
    assert(arena && size);
    *size = arena->capacity - arena->used;
    return 0;
}

int quest_arena_get_capacity(quest_arena_t *arena, size_t *capacity) {
    assert(arena && capacity);
    *capacity = arena->capacity;
    return 0;
}
#ifndef NDEBUG
const char *quest_arena_get_name(quest_arena_t *arena) {
    assert(arena);
    return arena->debug_name;
}

void quest_arena_print(quest_arena_t *arena) {
    assert(arena);
    fprintf(stderr, "[quest_arena_t: %s] Used: %zu / %zu bytes\n",
            arena->debug_name ? arena->debug_name : "(unnamed)",
            arena->used, arena->capacity);
    return;
}
#endif /* NDEBUG */

int quest_arena_top(quest_arena_t *arena, void **top) {
    assert(arena && top);
    *top = (char *)arena->base + arena->used;
    return 0;
}

quest_arena_marker_t quest_arena_mark(quest_arena_t *arena) {
    assert(arena);
    return arena->used;
}

void quest_arena_rewind(quest_arena_t *arena, quest_arena_marker_t marker) {
    assert(arena);
    if (marker > arena->used || marker > arena->capacity) {
        fprintf(stderr, "[arena_rewind]: Invalid rewind marker: out of bounds\n");
        return;
    }
    arena->used = marker;
    return;
}

quest_arena_t *quest_arena_create_subarena(quest_arena_t *parent, size_t capacity, const char *name) {
    assert(parent);
    if (0 == capacity) {
#ifndef NDEBUG
        fprintf(stderr, "[arena_create_subarena]: +1 capacity.\n");
        ++capacity;
#endif /* NDEBUG */
        return NULL;
    }
        
    quest_arena_t *subarena = (quest_arena_t *)quest_arena_aligned_malloc(parent, sizeof(quest_arena_t), QUEST_ALIGNOF(quest_arena_t));
    if (NULL == subarena) {
        fprintf(stderr, "[arena_create_subarena]: Failed to malloc subarena\n");
        return NULL;
    }
    subarena->is_sub = true;
#ifndef NDEBUG
    subarena->debug_name = name ? name : "unnamed_subarena";
#endif /* NDEBUG */
    
    void *sub_base = quest_arena_aligned_malloc(parent, capacity, QUEST_ALIGNOF(QUEST_MAX_ALIGN));
    if (NULL == sub_base) {
        fprintf(stderr, "[arena_create_subarena]: Failed to malloc sub base\n");
        return NULL;
    }

    subarena->base = sub_base;
    subarena->used = 0;
    subarena->capacity = capacity;
    
    return subarena;
}
