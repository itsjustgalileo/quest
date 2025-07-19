#ifndef QUEST_VECTOR_H_
#define QUEST_VECTOR_H_

#include <quest/quest_common.h>

#include <quest/quest_header.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct quest_vector quest_vector_t;
    
#define quest_vector_foreach(type, ptr, vec)            \
    for (type *ptr = (type *)quest_vector_begin(vec);   \
         (char *)ptr < (char *)quest_vector_end(vec);   \
         ++ptr)

    // Lifecycle
    quest_vector_t *quest_vector_init(size_t capacity, size_t elem_size, void (*destructor)(void *));
    void quest_vector_cleanup(quest_vector_t *vec);
    void quest_vector_reset(quest_vector_t *vec);
    void quest_vector_clear(quest_vector_t *vec);

    // Element Access
    void *quest_vector_push_back(quest_vector_t *vec, void *elem);
    bool quest_vector_pop_back(quest_vector_t *vec, void **out_elem);
    void *quest_vector_at(const quest_vector_t *vec, uint32 idx);
    void *quest_vector_front(const quest_vector_t *vec);
    void *quest_vector_back(const quest_vector_t *vec);

    // Capacity
    bool quest_vector_reserve(quest_vector_t *vec, size_t capacity);
    bool quest_vector_shrink_to_fit(quest_vector_t *vec);
    size_t quest_vector_size(const quest_vector_t *vec);
    size_t quest_vector_capacity(const quest_vector_t *vec);
    bool quest_vector_is_empty(const quest_vector_t *vec);

    // Modifiers
    bool quest_vector_insert(quest_vector_t *vec, uint32 at, const void *src);
    bool quest_vector_erase(quest_vector_t *vec, uint32 at);

    // Iterators
    void *quest_vector_begin(const quest_vector_t *vec);
    void *quest_vector_end(const quest_vector_t *vec);

#ifdef __cplusplus
}
#endif

#include <quest/quest_footer.h>

#endif /* QUEST_VECTOR_H_ */
