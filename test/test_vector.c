#include <stdio.h>
#include <quest/quest.h>

typedef struct {
    int32 id;
    char name[32];
} thing_t;

void thing_destructor(void *ptr) {
    thing_t *thing = (thing_t *)ptr;
    QUEST_LOG_DEBUG("Destroyed thing: id = %d", thing->id);
}

int main(void) {
    quest_vector_t *vec = quest_vector_init(2, sizeof(thing_t), thing_destructor);
    if (!vec) {
        QUEST_LOG_FATAL("Could not initialize vector.");
        return 1;
    }

    thing_t a = {1, "apple"};
    thing_t b = {2, "banana"};
    thing_t c = {3, "cherry"};

    quest_vector_push_back(vec, &a);
    quest_vector_push_back(vec, &b);
    quest_vector_push_back(vec, &c);

    QUEST_LOG_INFO("After pushing:");
    quest_vector_foreach(thing_t, it, vec) {
        printf("thing[%d] = %s\n", it->id, it->name);
    }

    thing_t d = {42, "dragonfruit"};
    quest_vector_insert(vec, 1, &d);

    QUEST_LOG_INFO("After inserting:");
    quest_vector_foreach(thing_t, it, vec) {
        printf("thing[%d] = %s\n", it->id, it->name);
    }

    quest_vector_erase(vec, 0);

    QUEST_LOG_INFO("After erasing first element:");
    quest_vector_foreach(thing_t, it, vec) {
        printf("thing[%d] = %s\n", it->id, it->name);
    }

    thing_t out;
    quest_vector_pop_back(vec, (void **)&out);
    QUEST_LOG_INFO("Popped: id = %d, name = %s", out.id, out.name);

    QUEST_LOG_INFO("Final contents:");
    quest_vector_foreach(thing_t, it, vec) {
        printf("thing[%d] = %s\n", it->id, it->name);
    }

    quest_vector_cleanup(vec);
    return 0;
}
