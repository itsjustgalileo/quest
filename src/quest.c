#include <quest/quest_init.h>

static bool quest_is_init = false;

int32 quest_init(void) {
    if (quest_is_init) {
        /* Already initialized ? */
        return 0;
    }

    /* TODO */
    quest_todo("quest_init_ticks();");
        
    quest_is_init = true;
    return 0;
}

void quest_shutdown(void) {
    /* TODO */
    quest_todo("quest_shutdown_ticks();");
    quest_is_init = false;
    return;
}
