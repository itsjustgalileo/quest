#include <quest/quest_init.h>

#include <quest/quest_time.h>
#include <quest/quest_logger.h>

#include <math/quest_mathlib.h>

static bool quest_is_init = false;

int32 quest_init(void) {
    if (quest_is_init) {
        /* Already initialized ? */
        return 0;
    }

    /* Calculate pi */
    QUEST_PI = quest_pi();
    quest_logger_init();    
    /* We kinda need to track the result from this.
       But if this fails, I think we have bigger probems!
    */
    quest_ticks_init();
    
    quest_is_init = true;
    return 0;
}

void quest_shutdown(void) {
    quest_ticks_shutdown();
    quest_is_init = false;
    return;
}
