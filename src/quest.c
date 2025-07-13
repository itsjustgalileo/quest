#include <quest/quest_init.h>

#include <quest/quest_todo.h>
#include <quest/quest_time.h>

static bool quest_is_init = false;

int32 quest_init(void) {
    if (quest_is_init) {
        /* Already initialized ? */
        return 0;
    }

    /* TODO */
    if (quest_ticks_init() != 0) {
        return 1;
    }
        
    quest_is_init = true;
    return 0;
}

void quest_shutdown(void) {
    /* TODO */
    quest_ticks_shutdown();
    quest_is_init = false;
    return;
}
