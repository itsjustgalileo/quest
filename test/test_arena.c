#include <quest/quest.h>
#include <stdio.h>

int main(void) {
    quest_arena_t *arena = quest_arena_init(1024, "test_arena");
    if (!arena) return 1;

    void *ptr = quest_arena_malloc(arena, 64);
    if (!ptr) return 2;

    void *aligned = quest_arena_aligned_malloc(arena, 128, 16);
    if (!aligned || ((uintptr_t)aligned % 16) != 0) return 3;

    size_t used = 0;
    if (quest_arena_get_size(arena, &used) != 0 || used == 0) return 4;

    quest_arena_marker_t mark = quest_arena_mark(arena);
    quest_arena_malloc(arena, 32);
    quest_arena_rewind(arena, mark);

    quest_arena_reset(arena);

    size_t available = 0;
    quest_arena_get_available(arena, &available);
    if (available != 1024) return 5;

    quest_arena_free(arena);
    return 0;
}
