#include <quest/quest_vector.h>

#include <quest/quest_logger.h>
#include <quest/quest_string.h>

struct quest_vector {
    void *value;
    size_t elem_size;
    uint32 elem_count;
    size_t capacity;
    void (*destructor)(void *);
};

quest_vector_t *quest_vector_init(const size_t capacity, const size_t elem_size, void (*destructor)(void *)) {
    quest_vector_t *vec = (quest_vector_t *)malloc(sizeof(struct quest_vector));
    if (NULL == vec) {
        QUEST_LOG_ERROR("Failed to malloc for quest_vector_t.");
        return NULL;
    }
    vec->capacity = capacity == 0 ? 1 : capacity;
    vec->elem_size = elem_size;
    vec->elem_count = 0;
    vec->value = malloc(vec->capacity * vec->elem_size);
    vec->destructor = destructor == NULL ? NULL : destructor;
    if (NULL == vec->value) {
        QUEST_LOG_ERROR("Failed to malloc for vector elements.");
        free(vec);
        return NULL;
    }
    return vec;
}

void quest_vector_cleanup(quest_vector_t *vec) {
    assert(vec);
    if (vec->destructor) {
        for (char *ptr = vec->value;
             ptr < (char *)vec->value + vec->elem_count * vec->elem_size;
             ptr += vec->elem_size) {
            vec->destructor(ptr);
        }
    }
    free(vec->value);
    free(vec);
    return;
}

void quest_vector_reset(quest_vector_t *vec) {
    assert(vec);
    vec->elem_count = 0;
    return;
}

void quest_vector_clear(quest_vector_t *vec) {
    assert(vec);
    if (vec->destructor) {
        for (char *ptr = vec->value;
             ptr < (char *)vec->value + vec->elem_count * vec->elem_size;
             ptr += vec->elem_size) {
            vec->destructor(ptr);
        }
    }
    quest_vector_reset(vec);
    return;
}

void *quest_vector_push_back(quest_vector_t *vec, void *elem) {
    assert(vec && elem);
    if (vec->elem_count >= vec->capacity) {
        size_t new_capacity = vec->capacity * 2;
        void *new_vec = realloc(vec->value, new_capacity * vec->elem_size);
        if (NULL == new_vec) {
            QUEST_LOG_ERROR("Failed to realloc vector.");
            return NULL;
        }
        vec->value = new_vec;
        vec->capacity = new_capacity;
    }
    quest_memcpy((char *)vec->value + vec->elem_count * vec->elem_size, elem, vec->elem_size);
    ++vec->elem_count;
    return ((char *)vec->value + ((vec->elem_count - 1) * vec->elem_size));
}

bool quest_vector_pop_back(quest_vector_t *vec, void **out_elem) {
    assert(vec && out_elem && vec->elem_count);
    --vec->elem_count;
    quest_memcpy(out_elem, ((char *)vec->value + (vec->elem_count * vec->elem_size)), vec->elem_size);
    return true;
}

void *quest_vector_at(const quest_vector_t *vec, const uint32 idx) {
    assert(vec);
    if (idx >= vec->elem_count) {
        QUEST_LOG_FATAL("Index out of bounds.");        
    }
    return ((char *)vec->value + (idx * vec->elem_size));
}

bool quest_vector_reserve(quest_vector_t *vec, const size_t capacity) {
    assert(vec);
    if (capacity <= vec->capacity) {
        QUEST_LOG_WARN("What's the point?");
        return false;
    }
    vec->capacity = capacity;
    void *res = realloc(vec->value, vec->capacity * vec->elem_size);
    if (NULL == res) {
        QUEST_LOG_ERROR("Failed to reserve memory for vector.");
        return false;
    }
    vec->value = res;
    return true;
}

bool quest_vector_shrink_to_fit(quest_vector_t *vec) {
    assert(vec);
    if (vec->elem_count < vec->capacity) {
        size_t new_capacity = vec->elem_count;
        void *res = realloc(vec->value, new_capacity * vec->elem_size);
        if (NULL == res) {
            QUEST_LOG_ERROR("Failed to realloc vector.");
            return false;
        }
        vec->value = res;
        vec->capacity = new_capacity;
        return true;
    }
    QUEST_LOG_WARN("What's the point?");
    return false;
}

bool quest_vector_insert(quest_vector_t *vec, const uint32 at, const void *src) {
    assert(vec && src && at < vec->elem_count);
    
    if (vec->elem_count >= vec->capacity) {
        if (!quest_vector_reserve(vec, vec->capacity * 2)) {
            QUEST_LOG_ERROR("Insert failed: reserve failed.");
            return false;
        }
    }

    quest_memmove(
        (char *)vec->value + (at + 1) * vec->elem_size,
        (char *)vec->value + at * vec->elem_size,
        (vec->elem_count - at) * vec->elem_size);

    quest_memcpy((char *)vec->value + at * vec->elem_size, src, vec->elem_size);
    ++vec->elem_count;
    return true;
}

bool quest_vector_erase(quest_vector_t *vec, const uint32 at) {
    assert(vec && at < vec->elem_count);
    if (vec->destructor) {
        vec->destructor((char *)vec->value + at * vec->elem_size);
    }

    quest_memmove(
        (char *)vec->value + at * vec->elem_size,
        (char *)vec->value + (at + 1) * vec->elem_size,
        (vec->elem_count - at - 1) * vec->elem_size);

    --vec->elem_count;

    return true;
}

void *quest_vector_begin(const quest_vector_t *vec) {
    assert(vec);
    return (char *)vec->value;
}

void *quest_vector_end(const quest_vector_t *vec) {
    assert(vec);
    return (char *)vec->value + (vec->elem_count * vec->elem_size);
}

size_t quest_vector_size(const quest_vector_t *vec) {
    assert(vec);
    return vec->elem_count;
}

size_t quest_vector_capacity(const quest_vector_t *vec) {
    assert(vec);
    return vec->capacity;
}

bool quest_vector_is_empty(const quest_vector_t *vec) {
    assert(vec);
    return vec->elem_count == 0;
}

void *quest_vector_front(const quest_vector_t *vec) {
    assert(vec);
    return (char *)vec->value;
}

void *quest_vector_back(const quest_vector_t *vec) {
    assert(vec && vec->elem_count > 0);
    return (char *)vec->value + ((vec->elem_count - 1) * vec->elem_size);
}
