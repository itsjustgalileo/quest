#include <stdio.h>
#include <stddef.h>

#include <quest/quest_logger.h>
#include <quest/quest_arena.h>
#include <quest/quest_string.h>

struct quest_arena {
    size_t capacity; /* Arena's total capacity */
    size_t used; /* Arena's used size */
    void *base; /* Arena's starting point */
    bool is_sub; /* Helps with free */
#ifdef QUEST_DEBUG
    const char *debug_name;
#endif /* QUEST_DEBUG */
};

quest_arena_t *quest_arena_init(size_t capacity, const char *name) {
    quest_arena_t *arena = (quest_arena_t *)malloc(sizeof(struct quest_arena));
    if (NULL == arena) {
        QUEST_LOG_ERROR("Failed to allocate memory struct quest_arena.");
        return NULL;
    }

    arena->is_sub = false;
    arena->capacity = capacity;
    arena->used = 0;
#ifdef QUEST_DEBUG
    arena->debug_name = name ? name : "unnamed_arena";
#endif
    
    arena->base = malloc(capacity);
    if (NULL == arena->base) {
        QUEST_LOG_ERROR("Failed to allocate memory for base.");
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
        QUEST_LOG_FATAL("Did you mean to call arena_rewind or arena_reset instead?Let's not continue, just for safety.");        
    }
    free(arena->base);
    free(arena);
    return;
}

void *quest_arena_malloc(quest_arena_t *arena, size_t size) {
    assert(arena);
    
    if (0 == size) {
#ifdef QUEST_DEBUG
        QUEST_LOG_WARN("+1 size.");
        ++size;
#else        
        return NULL;
#endif /* QUEST_DEBUG */
    }
    
    if (arena->used + size > arena->capacity) {
        QUEST_LOG_ERROR("Buffer overrun.");
        return NULL;
    }

    void *ptr = (char *)arena->base + arena->used;
    arena->used += size;
#ifdef QUEST_DEBUG
    quest_memset(ptr, 0xAD, size);
#endif /* QUEST_DEBUG */
    
    return ptr;
}

void *quest_arena_aligned_malloc(quest_arena_t *arena, size_t size, size_t alignment) {
    assert(arena);

    if (0 == size) {
#ifdef QUEST_DEBUG
        QUEST_LOG_WARN("+1 size.");
        ++size;
#else        
        return NULL;
#endif /* QUEST_DEBUG */
    }

    assert((alignment & (alignment - 1)) == 0);

    uintptr_t current = (uintptr_t)arena->base + arena->used;
    uintptr_t aligned = (current + (alignment - 1)) & ~(alignment - 1);
    size_t padding = aligned - current;

    if (arena->used + size + padding > arena->capacity) {
        QUEST_LOG_ERROR("Buffer overrun.");
        return NULL;
    }
    
    void *ptr = (void *)aligned;
    arena->used += size + padding;
    return ptr;
}

void quest_arena_reset(quest_arena_t *arena) {
    assert(arena);
#ifdef QUEST_DEBUG
    quest_memset(arena->base, 0xDE, arena->used);
#endif /* QUEST_DEBUG */
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
#ifdef QUEST_DEBUG
const char *quest_arena_get_name(quest_arena_t *arena) {
    assert(arena);
    return arena->debug_name;
}

void quest_arena_print(quest_arena_t *arena) {
    assert(arena);
    QUEST_LOG_DEBUG("[quest_arena_t: %s] Used: %zu / %zu bytes",
            arena->debug_name ? arena->debug_name : "(unnamed)",
            arena->used, arena->capacity);
    return;
}
#endif /* QUEST_DEBUG */

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
        QUEST_LOG_ERROR("Invalid marker %zu (used: %zu, capacity: %zu)\n", marker, arena->used, arena->capacity);
        return;
    }
    arena->used = marker;
    return;
}

quest_arena_t *quest_arena_create_subarena(quest_arena_t *parent, size_t capacity, const char *name) {
    assert(parent);
    if (0 == capacity) {
#ifdef QUEST_DEBUG
        QUEST_LOG_WARN("+1 capacity.");
        ++capacity;
#else        
        return NULL;
#endif /* QUEST_DEBUG */
    }
        
    quest_arena_t *subarena = (quest_arena_t *)quest_arena_aligned_malloc(parent, sizeof(quest_arena_t), QUEST_ALIGNOF(quest_arena_t));
    if (NULL == subarena) {
        QUEST_LOG_ERROR("Failed to malloc subarena.");
        return NULL;
    }
#ifdef QUEST_DEBUG
    subarena->debug_name = name ? name : "unnamed_subarena";
#endif /* QUEST_DEBUG */
    
    void *sub_base = quest_arena_aligned_malloc(parent, capacity, QUEST_ALIGNOF(QUEST_MAX_ALIGN));
    if (NULL == sub_base) {
        QUEST_LOG_ERROR("Failed to malloc sub base.");
        return NULL;
    }

    subarena->is_sub = true;
    subarena->base = sub_base;
    subarena->used = 0;
    subarena->capacity = capacity;
    
    return subarena;
}
